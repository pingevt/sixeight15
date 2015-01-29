<?php
/**
 * @file
 * six_eight_sermons.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function six_eight_sermons_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function six_eight_sermons_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function six_eight_sermons_node_info() {
  $items = array(
    'sermon' => array(
      'name' => t('Sermon'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'sermon_series' => array(
      'name' => t('Sermon Series'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
