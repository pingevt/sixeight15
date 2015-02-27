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
  $view->name = 'latest_church_events';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'church_event';
  $view->human_name = 'Latest Church Events';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Latest Church Events';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Field: Event: Event ID */
  $handler->display->display_options['fields']['church_event_id']['id'] = 'church_event_id';
  $handler->display->display_options['fields']['church_event_id']['table'] = 'church_event';
  $handler->display->display_options['fields']['church_event_id']['field'] = 'church_event_id';
  /* Field: Event: Date */
  $handler->display->display_options['fields']['date']['id'] = 'date';
  $handler->display->display_options['fields']['date']['table'] = 'church_event';
  $handler->display->display_options['fields']['date']['field'] = 'date';
  /* Field: Event: Adults */
  $handler->display->display_options['fields']['field_adult_count']['id'] = 'field_adult_count';
  $handler->display->display_options['fields']['field_adult_count']['table'] = 'field_data_field_adult_count';
  $handler->display->display_options['fields']['field_adult_count']['field'] = 'field_adult_count';
  $handler->display->display_options['fields']['field_adult_count']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_adult_count']['settings'] = array(
    'thousand_separator' => ' ',
    'prefix_suffix' => 1,
  );
  /* Field: Event: Kids */
  $handler->display->display_options['fields']['field_kids_count']['id'] = 'field_kids_count';
  $handler->display->display_options['fields']['field_kids_count']['table'] = 'field_data_field_kids_count';
  $handler->display->display_options['fields']['field_kids_count']['field'] = 'field_kids_count';
  $handler->display->display_options['fields']['field_kids_count']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_kids_count']['settings'] = array(
    'thousand_separator' => ' ',
    'prefix_suffix' => 1,
  );
  /* Field: Event: Nursery & PreK */
  $handler->display->display_options['fields']['field_nursery_prek_count']['id'] = 'field_nursery_prek_count';
  $handler->display->display_options['fields']['field_nursery_prek_count']['table'] = 'field_data_field_nursery_prek_count';
  $handler->display->display_options['fields']['field_nursery_prek_count']['field'] = 'field_nursery_prek_count';
  $handler->display->display_options['fields']['field_nursery_prek_count']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_nursery_prek_count']['settings'] = array(
    'thousand_separator' => ' ',
    'prefix_suffix' => 1,
  );
  /* Field: Global: Math expression */
  $handler->display->display_options['fields']['expression']['id'] = 'expression';
  $handler->display->display_options['fields']['expression']['table'] = 'views';
  $handler->display->display_options['fields']['expression']['field'] = 'expression';
  $handler->display->display_options['fields']['expression']['label'] = 'Attendance';
  $handler->display->display_options['fields']['expression']['precision'] = '0';
  $handler->display->display_options['fields']['expression']['expression'] = '[field_adult_count] + [field_kids_count] + [field_nursery_prek_count]';
  /* Field: Event: General Fund */
  $handler->display->display_options['fields']['field_general_fund_amt']['id'] = 'field_general_fund_amt';
  $handler->display->display_options['fields']['field_general_fund_amt']['table'] = 'field_data_field_general_fund_amt';
  $handler->display->display_options['fields']['field_general_fund_amt']['field'] = 'field_general_fund_amt';
  $handler->display->display_options['fields']['field_general_fund_amt']['settings'] = array(
    'thousand_separator' => ',',
    'decimal_separator' => '.',
    'scale' => '2',
    'prefix_suffix' => 1,
  );
  /* Field: Event: Operations links */
  $handler->display->display_options['fields']['operations']['id'] = 'operations';
  $handler->display->display_options['fields']['operations']['table'] = 'church_event';
  $handler->display->display_options['fields']['operations']['field'] = 'operations';
  /* Sort criterion: Event: Date */
  $handler->display->display_options['sorts']['date']['id'] = 'date';
  $handler->display->display_options['sorts']['date']['table'] = 'church_event';
  $handler->display->display_options['sorts']['date']['field'] = 'date';
  $handler->display->display_options['sorts']['date']['order'] = 'DESC';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');

  $views['latest_church_events'] = $view;

  return $views;
}
