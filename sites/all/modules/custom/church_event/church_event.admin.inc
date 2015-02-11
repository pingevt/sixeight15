<?php

/**
 * @file
 * church_event editing UI.
 *
 * We make very little use of the EntityAPI interface for this - preferring instead to use
 * views. That offers more flexibility to change a UI that will, more often than not,
 * be end-user facing.
 */

/**
 * UI controller.
 */
class ChurchEventUIController extends EntityBundleableUIController {

  /**
   * Overrides hook_menu() defaults. Main reason for doing this is that
   * parent class hook_menu() is optimized for entity type administration.
   */
  public function hook_menu() {

    $items = parent::hook_menu();
    $id_count = count(explode('/', $this->path));
    $wildcard = isset($this->entityInfo['admin ui']['menu wildcard']) ? $this->entityInfo['admin ui']['menu wildcard'] : '%' . $this->entityType;
    $plural_label = isset($this->entityInfo['plural label']) ? $this->entityInfo['plural label'] : $this->entityInfo['label'] . 's';

    $items[$this->path] = array(
      'title' => $plural_label,
      'page callback' => 'drupal_get_form',
      'page arguments' => array($this->entityType . '_overview_form', $this->entityType),
      'description' => 'Manage ' . $plural_label . '.',
      'access callback' => 'entity_access',
      'access arguments' => array('view', $this->entityType),
      'file' => 'includes/entity.ui.inc',
    );

    // Change the add page menu to multiple types of entities
    $items[$this->path . '/add'] = array(
      'title' => 'Add a church event',
      'description' => 'Add a new church event',
      'page callback'  => 'church_event_add_page',
      'access callback'  => 'church_event_access',
      'access arguments' => array('edit'),
      'type' => MENU_NORMAL_ITEM,
      'weight' => 20,
      'file' => 'church_event.admin.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module'])

    );

    // Add menu items to add each different type of entity.
    foreach (church_event_get_types() as $type) {
      $items[$this->path . '/add/' . $type->type] = array(
        'title' => 'Add ' . $type->label,
        'page callback' => 'church_event_form_wrapper',
        'page arguments' => array(church_event_create(array('type' => $type->type))),
        'access callback' => 'church_event_access',
        'access arguments' => array('edit', 'edit ' . $type->type),
        'file' => 'church_event.admin.inc',
        'file path' => drupal_get_path('module', $this->entityInfo['module'])
      );
    }

    // Loading and editing church_event entities
    $items[$this->path . '/church_event/' . $wildcard] = array(
      'page callback' => 'church_event_form_wrapper',
      'page arguments' => array($id_count + 1),
      'access callback' => 'church_event_access',
      'access arguments' => array('edit', $id_count + 1),
      'weight' => 0,
      'context' => MENU_CONTEXT_PAGE | MENU_CONTEXT_INLINE,
      'file' => 'church_event.admin.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module'])
    );
    $items[$this->path . '/church_event/' . $wildcard . '/edit'] = array(
      'title' => 'Edit',
      'type' => MENU_DEFAULT_LOCAL_TASK,
      'weight' => -10,
      'context' => MENU_CONTEXT_PAGE | MENU_CONTEXT_INLINE,
    );

    $items[$this->path . '/church_event/' . $wildcard . '/delete'] = array(
      'title' => 'Delete',
      'page callback' => 'church_event_delete_form_wrapper',
      'page arguments' => array($id_count + 1),
      'access callback' => 'church_event_access',
      'access arguments' => array('edit', $id_count + 1),
      'type' => MENU_LOCAL_TASK,
      'context' => MENU_CONTEXT_INLINE,
      'weight' => 10,
      'file' => 'church_event.admin.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module'])
    );

    // Menu item for viewing church_event
    $items['church_event/' . $wildcard] = array(
      //'title' => 'Title',
      'title callback' => 'church_event_page_title',
      'title arguments' => array(1),
      'page callback' => 'church_event_page_view',
      'page arguments' => array(1),
      'access callback' => 'church_event_access',
      'access arguments' => array('view', 1),
      'type' => MENU_CALLBACK,
    );
    return $items;
  }

  /**
   * Create the markup for the add church_event Entities page within the class
   * so it can easily be extended/overriden.
   */
  public function addPage() {
    $item = menu_get_item();
    $content = system_admin_menu_block($item);

    if (count($content) == 1) {
      $item = array_shift($content);
      drupal_goto($item['href']);
    }

    return theme('church_event_add_list', array('content' => $content));
  }


  /**
   * Builds the entity overview form.
   */
  public function overviewForm($form, &$form_state) {
    // By default just show a simple overview for all entities.
    $form['table'] = $this->overviewTable();
    $form['pager'] = array('#theme' => 'pager');
    return $form;
  }

  /**
   * Overview form validation callback.
   *
   * @param $form
   *   The form array of the overview form.
   * @param $form_state
   *   The overview form state which will be used for validating.
   */
  public function overviewFormValidate($form, &$form_state) {}

  /**
   * Overview form submit callback.
   *
   * @param $form
   *   The form array of the overview form.
   * @param $form_state
   *   The overview form state which will be used for submitting.
   */
  public function overviewFormSubmit($form, &$form_state) {}


  /**
   * Generates the render array for a overview table for arbitrary entities
   * matching the given conditions.
   *
   * @param $conditions
   *   An array of conditions as needed by entity_load().

   * @return Array
   *   A renderable array.
   */
  public function overviewTable($conditions = array()) {

    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', $this->entityType);

    // Add all conditions to query.
    foreach ($conditions as $key => $value) {
      $query->propertyCondition($key, $value);
    }

    if ($this->overviewPagerLimit) {
      $query->pager($this->overviewPagerLimit);
    }

    //$query->propertyOrderBy('date', 'DESC');

    $headers = array(
      'date' => array(
        'data' => 'date',
        'type' => 'property',
        'specifier' => 'date',
        'sort' => 'DESC',
      ),
    );
    $query->tableSort($headers);

    $results = $query->execute();

    $ids = isset($results[$this->entityType]) ? array_keys($results[$this->entityType]) : array();
    $entities = $ids ? entity_load($this->entityType, $ids) : array();
    //ksort($entities);

    $rows = array();
    foreach ($entities as $entity) {
      $rows[] = $this->overviewTableRow($conditions, entity_id($this->entityType, $entity), $entity);
    }

    $render = array(
      '#theme' => 'table',
      '#header' => $headers + $this->overviewTableHeaders($conditions, $rows),
      '#rows' => $rows,
      '#empty' => t('None.'),
    );
    return $render;
  }

  /**
   * Generates the table headers for the overview table.
   */
  protected function overviewTableHeaders($conditions, $rows, $additional_header = array()) {
    $header = $additional_header;
    //array_unshift($header, t('Label'));
    if (!empty($this->entityInfo['exportable'])) {
      $header[] = t('Status');
    }
    // Add operations with the right colspan.
    $header[] = array('data' => t('Operations'), 'colspan' => $this->operationCount());
    return $header;
  }

  /**
   * Returns the operation count for calculating colspans.
   */
  protected function operationCount() {
    $count = 3;
    $count += !empty($this->entityInfo['bundle of']) && entity_type_is_fieldable($this->entityInfo['bundle of']) && module_exists('field_ui') ? 2 : 0;
    $count += !empty($this->entityInfo['exportable']) ? 1 : 0;
    $count += !empty($this->entityInfo['i18n controller class']) ? 1 : 0;
    return $count;
  }

  /**
   * Generates the row for the passed entity and may be overridden in order to
   * customize the rows.
   *
   * @param $additional_cols
   *   Additional columns to be added after the entity label column.
   */
  protected function overviewTableRow($conditions, $id, $entity, $additional_cols = array()) {
    $entity_uri = entity_uri($this->entityType, $entity);

    $row[] = array('data' => array(
      '#theme' => 'entity_ui_overview_item',
      '#label' => entity_label($this->entityType, $entity),
      '#name' => !empty($this->entityInfo['exportable']) ? entity_id($this->entityType, $entity) : FALSE,
      '#url' => $entity_uri ? $entity_uri : FALSE,
      '#entity_type' => $this->entityType),
    );

    // Add in any passed additional cols.
    foreach ($additional_cols as $col) {
      $row[] = $col;
    }

    // Add a row for the exportable status.
    if (!empty($this->entityInfo['exportable'])) {
      $row[] = array('data' => array(
        '#theme' => 'entity_status',
        '#status' => $entity->{$this->statusKey},
      ));
    }
    // In case this is a bundle, we add links to the field ui tabs.
    $field_ui = !empty($this->entityInfo['bundle of']) && entity_type_is_fieldable($this->entityInfo['bundle of']) && module_exists('field_ui');
    // For exportable entities we add an export link.
    $exportable = !empty($this->entityInfo['exportable']);
    // If i18n integration is enabled, add a link to the translate tab.
    $i18n = !empty($this->entityInfo['i18n controller class']);

    // Add operations depending on the status.
    if (entity_has_status($this->entityType, $entity, ENTITY_FIXED)) {
      $row[] = array('data' => l(t('clone'), $this->path . '/manage/' . $id . '/clone'), 'colspan' => $this->operationCount());
    }
    else {
      $row[] = l(t('edit'), $this->path . '/manage/' . $id);

      if ($field_ui) {
        $row[] = l(t('manage fields'), $this->path . '/manage/' . $id . '/fields');
        $row[] = l(t('manage display'), $this->path . '/manage/' . $id . '/display');
      }
      if ($i18n) {
        $row[] = l(t('translate'), $this->path . '/manage/' . $id . '/translate');
      }
      if ($exportable) {
        $row[] = l(t('clone'), $this->path . '/manage/' . $id . '/clone');
      }

      if (empty($this->entityInfo['exportable']) || !entity_has_status($this->entityType, $entity, ENTITY_IN_CODE)) {
        $row[] = l(t('delete'), $this->path . '/manage/' . $id . '/delete', array('query' => drupal_get_destination()));
      }
      elseif (entity_has_status($this->entityType, $entity, ENTITY_OVERRIDDEN)) {
        $row[] = l(t('revert'), $this->path . '/manage/' . $id . '/revert', array('query' => drupal_get_destination()));
      }
      else {
        $row[] = '';
      }
    }
    if ($exportable) {
      $row[] = l(t('export'), $this->path . '/manage/' . $id . '/export');
    }
    return $row;
  }

}


/**
 * Form callback wrapper: create or edit a church_event.
 *
 * @param $church_event
 *   The church_event object being edited by this form.
 *
 * @see church_event_edit_form()
 */
function church_event_form_wrapper($church_event) {
  // Add the breadcrumb for the form's location.
  church_event_set_breadcrumb();
  return drupal_get_form('church_event_edit_form', $church_event);
}


/**
 * Form callback wrapper: delete a church_event.
 *
 * @param $church_event
 *   The church_event object being edited by this form.
 *
 * @see church_event_edit_form()
 */
function church_event_delete_form_wrapper($church_event) {
  // Add the breadcrumb for the form's location.
  //church_event_set_breadcrumb();
  return drupal_get_form('church_event_delete_form', $church_event);
}


/**
 * Form callback: create or edit a church_event.
 *
 * @param $church_event
 *   The church_event object to edit or for a create form an empty church_event object
 *     with only a church_event type defined.
 */
function church_event_edit_form($form, &$form_state, ChurchEvent $church_event) {
  // Add the default field elements.
  $form['date'] = array(
    '#type' => 'date',
    '#title' => t('Date of the church_event'),
    '#default_value' => isset($church_event->date) ? array('year' => date('Y', $church_event->date), 'month' => date('M', $church_event->date), 'day' => date('d', $church_event->date)) : '',
    '#required' => TRUE,
    '#weight' => -5,
  );

  $form['data']['#tree'] = TRUE;

  // Add the field related form elements.
  $form_state['church_event'] = $church_event;
  field_attach_form('church_event', $church_event, $form, $form_state);

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
    '#value' => t('Save church_event'),
    '#submit' => $submit + array('church_event_edit_form_submit'),
  );

  if (!empty($church_event->date)) {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete church_event'),
      '#suffix' => l(t('Cancel'), 'admin/content/church_event'),
      '#submit' => $submit + array('church_event_form_submit_delete'),
      '#weight' => 45,
    );
  }

  // We append the validate handler to #validate in case a form callback_wrapper
  // is used to add validate handlers earlier.
  $form['#validate'][] = 'church_event_edit_form_validate';
  return $form;
}


/**
 * Form API validate callback for the church_event form
 */
function church_event_edit_form_validate(&$form, &$form_state) {
  $church_event = $form_state['church_event'];

  // Notify field widgets to validate their data.
  field_attach_form_validate('church_event', $church_event, $form, $form_state);
}


/**
 * Form API submit callback for the church_event form.
 *
 * @todo remove hard-coded link
 */
function church_event_edit_form_submit(&$form, &$form_state) {

  $church_event = entity_ui_controller('church_event')->entityFormSubmitBuildEntity($form, $form_state);
  // Save the church_event and go back to the list of church_event

  // Add in created and changed times.
  if ($church_event->is_new = isset($church_event->is_new) ? $church_event->is_new : 0){
    $church_event->created = time();
  }

  if(is_array($church_event->date)) {
    $church_event->date = mktime(0, 0, 0, $church_event->date['month'], $church_event->date['day'], $church_event->date['year']);
  }

  $church_event->changed = time();

  $church_event->save();
  $form_state['redirect'] = 'admin/content/church_event';
}

/**
 * Form API submit callback for the delete button.
 *
 * @todo Remove hard-coded path
 */
function church_event_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/content/church_event/church_event/' . $form_state['church_event']->church_event_id . '/delete';
}


/**
 * Form callback: confirmation form for deleting a church_event.
 *
 * @param $church_event
 *   The church_event to delete
 *
 * @see confirm_form()
 */
function church_event_delete_form($form, &$form_state, $church_event) {
  $form_state['church_event'] = $church_event;

  $form['#submit'][] = 'church_event_delete_form_submit';

  $form = confirm_form($form,
    t('Are you sure you want to delete church_event %date?', array('%date' => $church_event->date)),
    'admin/content/church_event/church_event',
    '<p>' . t('This action cannot be undone.') . '</p>',
    t('Delete'),
    t('Cancel'),
    'confirm'
  );

  return $form;
}

/**
 * Submit callback for church_event_delete_form
 */
function church_event_delete_form_submit($form, &$form_state) {
  $church_event = $form_state['church_event'];

  church_event_delete($church_event);

  drupal_set_message(t('The church_event %date has been deleted.', array('%date' => $church_event->date)));
  watchdog('church_event', 'Deleted church_event %date.', array('%date' => $church_event->date));

  $form_state['redirect'] = 'admin/content/church_event';
}



/**
 * Page to add church_event Entities.
 *
 * @todo Pass this through a proper theme function
 */
function church_event_add_page() {
  $controller = entity_ui_controller('church_event');
  return $controller->addPage();
}


/**
 * Displays the list of available church_event types for church_event creation.
 *
 * @ingroup themeable
 */
function theme_church_event_add_list($variables) {
  $content = $variables['content'];
  $output = '';
  if ($content) {
    $output = '<dl class="church-event-type-list">';
    foreach ($content as $item) {
      $output .= '<dt>' . l($item['title'], $item['href']) . '</dt>';
      $output .= '<dd>' . filter_xss_admin($item['description']) . '</dd>';
    }
    $output .= '</dl>';
  }
  else {
    if (user_access('administer church_event types')) {
      $output = '<p>' . t('church_event Entities cannot be added because you have not created any church_event types yet. Go to the <a href="@create-church-event-type">church_event type creation page</a> to add a new church_event type.', array('@create-church-event-type' => url('admin/structure/church_event_types/add'))) . '</p>';
    }
    else {
      $output = '<p>' . t('No church_event types have been created yet for you to use.') . '</p>';
    }
  }

  return $output;
}





/**
 * Sets the breadcrumb for administrative church_event pages.
 */
function church_event_set_breadcrumb() {
  $breadcrumb = array(
    l(t('Home'), '<front>'),
    l(t('Administration'), 'admin'),
    l(t('Content'), 'admin/content'),
    l(t('Church Event'), 'admin/content/church_event'),
  );

  drupal_set_breadcrumb($breadcrumb);
}



