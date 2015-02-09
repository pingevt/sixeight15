<?php

/**
 * @file
 * church_events editing UI.
 *
 * We make very little use of the EntityAPI interface for this - preferring instead to use
 * views. That offers more flexibility to change a UI that will, more often than not,
 * be end-user facing.
 */

/**
 * UI controller.
 */
class ChurchEventsUIController extends EntityDefaultUIController {

  /**
   * Overrides hook_menu() defaults. Main reason for doing this is that
   * parent class hook_menu() is optimized for entity type administration.
   */
  public function hook_menu() {

    $items = array();
    $id_count = count(explode('/', $this->path));
    $wildcard = isset($this->entityInfo['admin ui']['menu wildcard']) ? $this->entityInfo['admin ui']['menu wildcard'] : '%' . $this->entityType;

    $items[$this->path] = array(
      'title' => 'Church events',
      'description' => 'Add edit and update church_events.',
      'page callback' => 'system_admin_menu_block_page',
      'access arguments' => array('access administration pages'),
      'file path' => drupal_get_path('module', 'system'),
      'file' => 'system.admin.inc',
    );

    // Change the overview menu type for the list of church_events.
    $items[$this->path]['type'] = MENU_LOCAL_TASK;

    // Change the add page menu to multiple types of entities
    $items[$this->path . '/add'] = array(
      'title' => 'Add a church event',
      'description' => 'Add a new church event',
      'page callback'  => 'church_events_add_page',
      'access callback'  => 'church_events_access',
      'access arguments' => array('edit'),
      'type' => MENU_NORMAL_ITEM,
      'weight' => 20,
      'file' => 'church_events.admin.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module'])

    );

    // Add menu items to add each different type of entity.
    foreach (church_events_get_types() as $type) {
      $items[$this->path . '/add/' . $type->type] = array(
        'title' => 'Add ' . $type->label,
        'page callback' => 'church_events_form_wrapper',
        'page arguments' => array(church_events_create(array('type' => $type->type))),
        'access callback' => 'church_events_access',
        'access arguments' => array('edit', 'edit ' . $type->type),
        'file' => 'church_events.admin.inc',
        'file path' => drupal_get_path('module', $this->entityInfo['module'])
      );
    }

    // Loading and editing church_events entities
    $items[$this->path . '/church_events/' . $wildcard] = array(
      'page callback' => 'church_events_form_wrapper',
      'page arguments' => array($id_count + 1),
      'access callback' => 'church_events_access',
      'access arguments' => array('edit', $id_count + 1),
      'weight' => 0,
      'context' => MENU_CONTEXT_PAGE | MENU_CONTEXT_INLINE,
      'file' => 'church_events.admin.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module'])
    );
    $items[$this->path . '/church_events/' . $wildcard . '/edit'] = array(
      'title' => 'Edit',
      'type' => MENU_DEFAULT_LOCAL_TASK,
      'weight' => -10,
      'context' => MENU_CONTEXT_PAGE | MENU_CONTEXT_INLINE,
    );

    $items[$this->path . '/church_events/' . $wildcard . '/delete'] = array(
      'title' => 'Delete',
      'page callback' => 'church_events_delete_form_wrapper',
      'page arguments' => array($id_count + 1),
      'access callback' => 'church_events_access',
      'access arguments' => array('edit', $id_count + 1),
      'type' => MENU_LOCAL_TASK,
      'context' => MENU_CONTEXT_INLINE,
      'weight' => 10,
      'file' => 'church_events.admin.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module'])
    );

    // Menu item for viewing church_events
    $items['church_events/' . $wildcard] = array(
      //'title' => 'Title',
      'title callback' => 'church_events_page_title',
      'title arguments' => array(1),
      'page callback' => 'church_events_page_view',
      'page arguments' => array(1),
      'access callback' => 'church_events_access',
      'access arguments' => array('view', 1),
      'type' => MENU_CALLBACK,
    );
    return $items;
  }


  /**
   * Create the markup for the add church_events Entities page within the class
   * so it can easily be extended/overriden.
   */
  public function addPage() {
    $item = menu_get_item();
    $content = system_admin_menu_block($item);

    if (count($content) == 1) {
      $item = array_shift($content);
      drupal_goto($item['href']);
    }

    return theme('church_events_add_list', array('content' => $content));
  }

}


/**
 * Form callback wrapper: create or edit a church_events.
 *
 * @param $church_events
 *   The church_events object being edited by this form.
 *
 * @see church_events_edit_form()
 */
function church_events_form_wrapper($church_events) {
  // Add the breadcrumb for the form's location.
  church_events_set_breadcrumb();
  return drupal_get_form('church_events_edit_form', $church_events);
}


/**
 * Form callback wrapper: delete a church_events.
 *
 * @param $church_events
 *   The church_events object being edited by this form.
 *
 * @see church_events_edit_form()
 */
function church_events_delete_form_wrapper($church_events) {
  // Add the breadcrumb for the form's location.
  //church_events_set_breadcrumb();
  return drupal_get_form('church_events_delete_form', $church_events);
}


/**
 * Form callback: create or edit a church_events.
 *
 * @param $church_events
 *   The church_events object to edit or for a create form an empty church_events object
 *     with only a church_events type defined.
 */
function church_events_edit_form($form, &$form_state, ChurchEvents $church_events) {
  // Add the default field elements.
  $form['date'] = array(
    '#type' => 'date',
    '#title' => t('Date of the church_events'),
    '#default_value' => isset($church_events->date) ? $church_events->date : '',
    '#maxlength' => 255,
    '#required' => TRUE,
    '#weight' => -5,
  );

  $form['data']['#tree'] = TRUE;

  // Add the field related form elements.
  $form_state['church_events'] = $church_events;
  field_attach_form('church_events', $church_events, $form, $form_state);

  $form['actions'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('form-actions')),
    '#weight' => 400,
  );

  // We add the form's #submit array to this button along with the actual submit
  // handler to preserve any submit handlers added by a form callback_wrapper.
  $submit = array();

  if (!empty($form['#submit'])) {
    $submit += $form['#submit'];
  }

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save church_events'),
    '#submit' => $submit + array('church_events_edit_form_submit'),
  );

  if (!empty($church_events->date)) {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete church_events'),
      '#suffix' => l(t('Cancel'), 'admin/content/church_events'),
      '#submit' => $submit + array('church_events_form_submit_delete'),
      '#weight' => 45,
    );
  }

  // We append the validate handler to #validate in case a form callback_wrapper
  // is used to add validate handlers earlier.
  $form['#validate'][] = 'church_events_edit_form_validate';
  return $form;
}


/**
 * Form API validate callback for the church_events form
 */
function church_events_edit_form_validate(&$form, &$form_state) {
  $church_events = $form_state['church_events'];

  // Notify field widgets to validate their data.
  field_attach_form_validate('church_events', $church_events, $form, $form_state);
}


/**
 * Form API submit callback for the church_events form.
 *
 * @todo remove hard-coded link
 */
function church_events_edit_form_submit(&$form, &$form_state) {

  $church_events = entity_ui_controller('church_events')->entityFormSubmitBuildEntity($form, $form_state);
  // Save the church_events and go back to the list of church_events

  // Add in created and changed times.
  if ($church_events->is_new = isset($church_events->is_new) ? $church_events->is_new : 0){
    $church_events->created = time();
  }

  if(is_array($church_events->date)) {
    $church_events->date = mktime(0, 0, 0, $church_events->date['month'], $church_events->date['day'], $church_events->date['year']);
  }

  $church_events->changed = time();

  $church_events->save();
  $form_state['redirect'] = 'admin/content/church_events';
}

/**
 * Form API submit callback for the delete button.
 *
 * @todo Remove hard-coded path
 */
function church_events_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/content/church_events/church_events/' . $form_state['church_events']->church_events_id . '/delete';
}


/**
 * Form callback: confirmation form for deleting a church_events.
 *
 * @param $church_events
 *   The church_events to delete
 *
 * @see confirm_form()
 */
function church_events_delete_form($form, &$form_state, $church_events) {
  $form_state['church_events'] = $church_events;

  $form['#submit'][] = 'church_events_delete_form_submit';

  $form = confirm_form($form,
    t('Are you sure you want to delete church_events %date?', array('%date' => $church_events->date)),
    'admin/content/church_events/church_events',
    '<p>' . t('This action cannot be undone.') . '</p>',
    t('Delete'),
    t('Cancel'),
    'confirm'
  );

  return $form;
}

/**
 * Submit callback for church_events_delete_form
 */
function church_events_delete_form_submit($form, &$form_state) {
  $church_events = $form_state['church_events'];

  church_events_delete($church_events);

  drupal_set_message(t('The church_events %date has been deleted.', array('%date' => $church_events->date)));
  watchdog('church_events', 'Deleted church_events %date.', array('%date' => $church_events->date));

  $form_state['redirect'] = 'admin/content/church_events';
}



/**
 * Page to add church_events Entities.
 *
 * @todo Pass this through a proper theme function
 */
function church_events_add_page() {
  $controller = entity_ui_controller('church_events');
  return $controller->addPage();
}


/**
 * Displays the list of available church_events types for church_events creation.
 *
 * @ingroup themeable
 */
function theme_church_events_add_list($variables) {
  $content = $variables['content'];
  $output = '';
  if ($content) {
    $output = '<dl class="church-events-type-list">';
    foreach ($content as $item) {
      $output .= '<dt>' . l($item['title'], $item['href']) . '</dt>';
      $output .= '<dd>' . filter_xss_admin($item['description']) . '</dd>';
    }
    $output .= '</dl>';
  }
  else {
    if (user_access('administer church_events types')) {
      $output = '<p>' . t('church_events Entities cannot be added because you have not created any church_events types yet. Go to the <a href="@create-church-events-type">church_events type creation page</a> to add a new church_events type.', array('@create-church-events-type' => url('admin/structure/church_events_types/add'))) . '</p>';
    }
    else {
      $output = '<p>' . t('No church_events types have been created yet for you to use.') . '</p>';
    }
  }

  return $output;
}





/**
 * Sets the breadcrumb for administrative church_events pages.
 */
function church_events_set_breadcrumb() {
  $breadcrumb = array(
    l(t('Home'), '<front>'),
    l(t('Administration'), 'admin'),
    l(t('Content'), 'admin/content'),
    l(t('Church Event'), 'admin/content/church_events'),
  );

  drupal_set_breadcrumb($breadcrumb);
}



