<?php

/**
 * @file
 * Providing extra functionality for the church_event UI via views.
 */


/**
 * Implements hook_views_data()
 */
function church_event_views_data_alter(&$data) {
  $data['church_event']['date']['field']['handler'] = 'church_event_handler_date_field';

  $data['church_event']['link_church_event'] = array(
    'field' => array(
      'title' => t('Link'),
      'help' => t('Provide a link to the church_event.'),
      'handler' => 'church_event_handler_link_field',
    ),
  );
  $data['church_event']['edit_church_event'] = array(
    'field' => array(
      'title' => t('Edit Link'),
      'help' => t('Provide a link to the edit form for the church_event.'),
      'handler' => 'church_event_handler_edit_link_field',
    ),
  );
  $data['church_event']['delete_church_event'] = array(
    'field' => array(
      'title' => t('Delete Link'),
      'help' => t('Provide a link to delete the church_event.'),
      'handler' => 'church_event_handler_delete_link_field',
    ),
  );
  // This content of this field are decided based on the menu structure that
  // follows church_event/church_event/%church_event_id/op
  $data['church_event']['operations'] = array(
    'field' => array(
      'title' => t('Operations links'),
      'help' => t('Display all operations available for this church_event.'),
      'handler' => 'church_event_handler_church_event_operations_field',
    ),
  );
}


/**
 * Implements hook_views_default_views().
 */
function church_event_views_default_views() {
  $views = array();

  return $views;
}
