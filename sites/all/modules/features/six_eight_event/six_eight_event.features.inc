<?php
/**
 * @file
 * six_eight_event.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function six_eight_event_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function six_eight_event_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function six_eight_event_image_default_styles() {
  $styles = array();

  // Exported image style: event_full.
  $styles['event_full'] = array(
    'label' => 'Event Full',
    'effects' => array(
      2 => array(
        'name' => 'manualcrop_crop',
        'data' => array(
          'width' => 740,
          'height' => '',
          'keepproportions' => 0,
          'reuse_crop_style' => '',
          'style_name' => 'event_full',
        ),
        'weight' => 0,
      ),
      3 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 740,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 2,
      ),
    ),
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function six_eight_event_node_info() {
  $items = array(
    'event' => array(
      'name' => t('Event'),
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
