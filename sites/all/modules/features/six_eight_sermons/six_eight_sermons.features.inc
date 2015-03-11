<?php
/**
 * @file
 * six_eight_sermons.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function six_eight_sermons_ctools_plugin_api($module = NULL, $api = NULL) {
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
function six_eight_sermons_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function six_eight_sermons_image_default_styles() {
  $styles = array();

  // Exported image style: sermon_teaser.
  $styles['sermon_teaser'] = array(
    'label' => 'Sermon Teaser',
    'effects' => array(
      5 => array(
        'name' => 'manualcrop_crop_and_scale',
        'data' => array(
          'width' => 740,
          'height' => 566,
          'upscale' => 0,
          'respectminimum' => 1,
          'onlyscaleifcrop' => 0,
          'style_name' => 'sermon_teaser',
        ),
        'weight' => 0,
      ),
      6 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 740,
          'height' => 566,
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
