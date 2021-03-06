<?php
/**
 * @file
 * resources_features.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function resources_features_ctools_plugin_api($module = NULL, $api = NULL) {
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
function resources_features_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function resources_features_image_default_styles() {
  $styles = array();

  // Exported image style: resource_thumbnail.
  $styles['resource_thumbnail'] = array(
    'label' => 'Resource thumbnail',
    'effects' => array(
      11 => array(
        'name' => 'manualcrop_crop_and_scale',
        'data' => array(
          'width' => 120,
          'height' => 120,
          'upscale' => 0,
          'respectminimum' => 1,
          'onlyscaleifcrop' => 0,
          'style_name' => 'resource_thumbnail',
        ),
        'weight' => 0,
      ),
      12 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 120,
          'height' => 120,
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
function resources_features_node_info() {
  $items = array(
    'resource' => array(
      'name' => t('Resource'),
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
