<?php

/**
 * @file
 * Providing extra functionality for the Cevents UI via views.
 */


/**
 * Implements hook_views_data()
 */
function cevents_views_data_alter(&$data) {
//print '<pre>';
//print_r($data['cevents']);
//die();

  $data['cevents']['date']['field']['handler'] = 'cevents_handler_date_field';

  $data['cevents']['link_cevents'] = array(
    'field' => array(
      'title' => t('Link'),
      'help' => t('Provide a link to the cevents.'),
      'handler' => 'cevents_handler_link_field',
    ),
  );
  $data['cevents']['edit_cevents'] = array(
    'field' => array(
      'title' => t('Edit Link'),
      'help' => t('Provide a link to the edit form for the cevents.'),
      'handler' => 'cevents_handler_edit_link_field',
    ),
  );
  $data['cevents']['delete_cevents'] = array(
    'field' => array(
      'title' => t('Delete Link'),
      'help' => t('Provide a link to delete the cevents.'),
      'handler' => 'cevents_handler_delete_link_field',
    ),
  );
  // This content of this field are decided based on the menu structure that
  // follows ceventss/cevents/%cevents_id/op
  $data['cevents']['operations'] = array(
    'field' => array(
      'title' => t('Operations links'),
      'help' => t('Display all operations available for this cevents.'),
      'handler' => 'cevents_handler_cevents_operations_field',
    ),
  );
}


/**
 * Implements hook_views_default_views().
 */
function cevents_views_default_views() {
  $views = array();

  $view = new view;
  $view->name = 'cevents';
  $view->description = 'A list of all ceventss';
  $view->tag = 'cevents';
  $view->base_table = 'cevents';
  $view->human_name = 'Cevents';
  $view->core = 7;
  $view->api_version = '3.0-alpha1';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Cevents';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'create any cevents type';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'name' => 'name',
    'cevents_id' => 'cevents_id',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'cevents_id' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  $handler->display->display_options['style_options']['empty_table'] = 0;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['label'] = 'Empty ';
  $handler->display->display_options['empty']['area']['empty'] = FALSE;
  $handler->display->display_options['empty']['area']['content'] = 'No cevents have been created yet';
  /* Field: Cevents: Cevents ID */
  $handler->display->display_options['fields']['cevents_id']['id'] = 'cevents_id';
  $handler->display->display_options['fields']['cevents_id']['table'] = 'cevents';
  $handler->display->display_options['fields']['cevents_id']['field'] = 'cevents_id';
  $handler->display->display_options['fields']['cevents_id']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['cevents_id']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['cevents_id']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['cevents_id']['alter']['external'] = 0;
  $handler->display->display_options['fields']['cevents_id']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['cevents_id']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['cevents_id']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['cevents_id']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['cevents_id']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['cevents_id']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['cevents_id']['alter']['html'] = 0;
  $handler->display->display_options['fields']['cevents_id']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['cevents_id']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['cevents_id']['hide_empty'] = 0;
  $handler->display->display_options['fields']['cevents_id']['empty_zero'] = 0;
  /* Field: Cevents: Name */
  $handler->display->display_options['fields']['date']['id'] = 'date';
  $handler->display->display_options['fields']['date']['table'] = 'cevents';
  $handler->display->display_options['fields']['date']['field'] = 'date';
  $handler->display->display_options['fields']['date']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['date']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['date']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['date']['alter']['external'] = 0;
  $handler->display->display_options['fields']['date']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['date']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['date']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['date']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['date']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['date']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['date']['alter']['html'] = 0;
  $handler->display->display_options['fields']['date']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['date']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['date']['hide_empty'] = 0;
  $handler->display->display_options['fields']['date']['empty_zero'] = 0;
  /* Field: Cevents: Link */
  $handler->display->display_options['fields']['link_cevents']['id'] = 'link_cevents';
  $handler->display->display_options['fields']['link_cevents']['table'] = 'cevents';
  $handler->display->display_options['fields']['link_cevents']['field'] = 'link_cevents';
  $handler->display->display_options['fields']['link_cevents']['label'] = 'View';
  $handler->display->display_options['fields']['link_cevents']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['link_cevents']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['link_cevents']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['link_cevents']['alter']['external'] = 0;
  $handler->display->display_options['fields']['link_cevents']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['link_cevents']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['link_cevents']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['link_cevents']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['link_cevents']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['link_cevents']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['link_cevents']['alter']['html'] = 0;
  $handler->display->display_options['fields']['link_cevents']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['link_cevents']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['link_cevents']['hide_empty'] = 0;
  $handler->display->display_options['fields']['link_cevents']['empty_zero'] = 0;
  /* Field: Cevents: Operations links */
  $handler->display->display_options['fields']['operations']['id'] = 'operations';
  $handler->display->display_options['fields']['operations']['table'] = 'cevents';
  $handler->display->display_options['fields']['operations']['field'] = 'operations';
  $handler->display->display_options['fields']['operations']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['external'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['operations']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['operations']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['html'] = 0;
  $handler->display->display_options['fields']['operations']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['operations']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['operations']['hide_empty'] = 0;
  $handler->display->display_options['fields']['operations']['empty_zero'] = 0;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'ceventss_admin_page');
  $handler->display->display_options['path'] = 'admin/content/ceventss/list';
  $handler->display->display_options['menu']['type'] = 'default tab';
  $handler->display->display_options['menu']['title'] = 'List';
  $handler->display->display_options['menu']['weight'] = '-10';
  $handler->display->display_options['tab_options']['type'] = 'tab';
  $handler->display->display_options['tab_options']['title'] = 'Ceventss';
  $handler->display->display_options['tab_options']['description'] = 'Manage ceventss';
  $handler->display->display_options['tab_options']['weight'] = '0';
  $handler->display->display_options['tab_options']['name'] = 'management';
  $translatables['ceventss'] = array(
    t('Master'),
    t('Ceventss'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('Empty '),
    t('No ceventss have been created yet'),
    t('Cevents ID'),
    t('.'),
    t(','),
    t('Name'),
    t('View'),
    t('Operations links'),
    t('Page'),
  );
  $views['cevents'] = $view;
  return $views;

}
