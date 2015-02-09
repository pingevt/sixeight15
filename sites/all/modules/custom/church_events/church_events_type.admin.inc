<?php

/**
 * @file
 * church_events type editing UI.
 */

/**
 * UI controller.
 */
class ChurchEventsTypeUIController extends EntityDefaultUIController {

  /**
   * Overrides hook_menu() defaults.
   */
  public function hook_menu() {
    $items = parent::hook_menu();
		$items[$this->path]['description'] = 'Manage church_events entity types, including adding and removing fields and the display of fields.';
    return $items;
  }
}

/**
 * Generates the church_events type editing form.
 */
function church_events_type_form($form, &$form_state, $church_events_type, $op = 'edit') {

  if ($op == 'clone') {
    $church_events_type->label .= ' (cloned)';
    $church_events_type->type = '';
  }

  $form['label'] = array(
    '#title' => t('Label'),
    '#type' => 'textfield',
    '#default_value' => $church_events_type->label,
    '#description' => t('The human-readable name of this church_events type.'),
    '#required' => TRUE,
    '#size' => 30,
  );
  // Machine-readable type name.
  $form['type'] = array(
    '#type' => 'machine_name',
    '#default_value' => isset($church_events_type->type) ? $church_events_type->type : '',
    '#maxlength' => 32,
//    '#disabled' => $church_events_type->isLocked() && $op != 'clone',
    '#machine_name' => array(
      'exists' => 'church_events_get_types',
      'source' => array('label'),
    ),
    '#description' => t('A unique machine-readable name for this church_events type. It must only contain lowercase letters, numbers, and underscores.'),
  );

  $form['data']['#tree'] = TRUE;

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save church event type'),
    '#weight' => 40,
  );

  //Locking not supported yet
  /*if (!$church_events_type->isLocked() && $op != 'add') {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete church_events type'),
      '#weight' => 45,
      '#limit_validation_errors' => array(),
      '#submit' => array('church_events_type_form_submit_delete')
    );
  }*/
  return $form;
}

/**
 * Form API submit callback for the type form.
 */
function church_events_type_form_submit(&$form, &$form_state) {
  $church_events_type = entity_ui_form_submit_build_entity($form, $form_state);
  $church_events_type->save();
  $form_state['redirect'] = 'admin/structure/church_events_types';
}

/**
 * Form API submit callback for the delete button.
 */
function church_events_type_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/structure/church_events_types/manage/' . $form_state['church_events_type']->type . '/delete';
}
