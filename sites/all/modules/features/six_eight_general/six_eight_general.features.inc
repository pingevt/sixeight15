<?php
/**
 * @file
 * six_eight_general.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function six_eight_general_ctools_plugin_api($module = NULL, $api = NULL) {
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
function six_eight_general_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function six_eight_general_image_default_styles() {
  $styles = array();

  // Exported image style: community_group_full.
  $styles['community_group_full'] = array(
    'name' => 'community_group_full',
    'label' => 'Community Group Full',
    'effects' => array(
      1 => array(
        'label' => 'Manual Crop: Crop and scale',
        'help' => 'Crop and scale a user-selected area, respecting the ratio of the destination width and height.',
        'effect callback' => 'manualcrop_crop_and_scale_effect',
        'form callback' => 'manualcrop_crop_and_scale_form',
        'summary theme' => 'manualcrop_crop_and_scale_summary',
        'module' => 'manualcrop',
        'name' => 'manualcrop_crop_and_scale',
        'data' => array(
          'width' => 350,
          'height' => 197,
          'upscale' => 0,
          'respectminimum' => 1,
          'onlyscaleifcrop' => 0,
          'style_name' => 'community_group_full',
        ),
        'weight' => 0,
      ),
      2 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 350,
          'height' => 197,
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
function six_eight_general_node_info() {
  $items = array(
    'community_group' => array(
      'name' => t('Community Group'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'page' => array(
      'name' => t('Page'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'person' => array(
      'name' => t('Person'),
      'base' => 'node_content',
      'description' => t('People who need to be displayed in different areas of the website.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'system' => array(
      'name' => t('System'),
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
