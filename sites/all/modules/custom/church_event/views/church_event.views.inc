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

$view = new view();
$view->name = 'church_event';
$view->description = 'A list of all church_event';
$view->tag = 'church_event';
$view->base_table = 'church_event';
$view->human_name = 'Church Events';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['title'] = 'Church Events';
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['access']['type'] = 'perm';
$handler->display->display_options['access']['perm'] = 'create any church_event type';
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['pager']['type'] = 'full';
$handler->display->display_options['pager']['options']['items_per_page'] = '30';
$handler->display->display_options['pager']['options']['offset'] = '0';
$handler->display->display_options['pager']['options']['id'] = '0';
$handler->display->display_options['pager']['options']['quantity'] = '9';
$handler->display->display_options['style_plugin'] = 'table';
$handler->display->display_options['style_options']['columns'] = array(
  'church_event_id' => 'church_event_id',
  'date' => 'date',
  'link_church_event' => 'link_church_event',
  'operations' => 'operations',
);
$handler->display->display_options['style_options']['default'] = '-1';
$handler->display->display_options['style_options']['info'] = array(
  'church_event_id' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'date' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'link_church_event' => array(
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'operations' => array(
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
);
/* No results behavior: Global: Text area */
$handler->display->display_options['empty']['area']['id'] = 'area';
$handler->display->display_options['empty']['area']['table'] = 'views';
$handler->display->display_options['empty']['area']['field'] = 'area';
$handler->display->display_options['empty']['area']['label'] = 'Empty ';
$handler->display->display_options['empty']['area']['content'] = 'No church_events have been created yet';
/* Field: Event: Event ID */
$handler->display->display_options['fields']['church_event_id']['id'] = 'church_event_id';
$handler->display->display_options['fields']['church_event_id']['table'] = 'church_event';
$handler->display->display_options['fields']['church_event_id']['field'] = 'church_event_id';
$handler->display->display_options['fields']['church_event_id']['separator'] = '';
/* Field: Event: Type */
$handler->display->display_options['fields']['type']['id'] = 'type';
$handler->display->display_options['fields']['type']['table'] = 'church_event';
$handler->display->display_options['fields']['type']['field'] = 'type';
/* Field: Event: Date */
$handler->display->display_options['fields']['date']['id'] = 'date';
$handler->display->display_options['fields']['date']['table'] = 'church_event';
$handler->display->display_options['fields']['date']['field'] = 'date';
/* Field: Event: Link */
$handler->display->display_options['fields']['link_church_event']['id'] = 'link_church_event';
$handler->display->display_options['fields']['link_church_event']['table'] = 'church_event';
$handler->display->display_options['fields']['link_church_event']['field'] = 'link_church_event';
$handler->display->display_options['fields']['link_church_event']['label'] = 'View';
/* Field: Event: Operations links */
$handler->display->display_options['fields']['operations']['id'] = 'operations';
$handler->display->display_options['fields']['operations']['table'] = 'church_event';
$handler->display->display_options['fields']['operations']['field'] = 'operations';

/* Display: Page */
$handler = $view->new_display('page', 'Page', 'church_event_admin_page');
$handler->display->display_options['path'] = 'admin/content/church_event/list';
$handler->display->display_options['menu']['type'] = 'default tab';
$handler->display->display_options['menu']['title'] = 'List';
$handler->display->display_options['menu']['weight'] = '-10';
$handler->display->display_options['menu']['context'] = 0;
$handler->display->display_options['menu']['context_only_inline'] = 0;
$handler->display->display_options['tab_options']['type'] = 'tab';
$handler->display->display_options['tab_options']['title'] = 'Church Events';
$handler->display->display_options['tab_options']['description'] = 'Manage Church Events';
$handler->display->display_options['tab_options']['weight'] = '0';
$handler->display->display_options['tab_options']['name'] = 'management';

  $views['church_event'] = $view;
  return $views;

}
