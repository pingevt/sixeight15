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
  if ($module == "linkit" && $api == "linkit_profiles") {
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

  // Exported image style: front_page_block.
  $styles['front_page_block'] = array(
    'label' => 'Front Page block',
    'effects' => array(
      16 => array(
        'name' => 'manualcrop_crop_and_scale',
        'data' => array(
          'width' => 350,
          'height' => 260,
          'upscale' => 0,
          'respectminimum' => 1,
          'onlyscaleifcrop' => 0,
          'style_name' => 'front_page_block',
        ),
        'weight' => 0,
      ),
      17 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 350,
          'height' => 260,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: front_page_block_preview.
  $styles['front_page_block_preview'] = array(
    'label' => 'Front Page block preview',
    'effects' => array(
      18 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 116,
          'height' => 87,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: home_page_carousel.
  $styles['home_page_carousel'] = array(
    'label' => 'Home Page Carousel',
    'effects' => array(
      13 => array(
        'name' => 'manualcrop_crop_and_scale',
        'data' => array(
          'width' => 1170,
          'height' => 418,
          'upscale' => 0,
          'respectminimum' => 1,
          'onlyscaleifcrop' => 0,
          'style_name' => 'home_page_carousel',
        ),
        'weight' => 0,
      ),
      14 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 1170,
          'height' => 418,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: home_page_carousel_preview.
  $styles['home_page_carousel_preview'] = array(
    'label' => 'Home Page Carousel Preview',
    'effects' => array(
      15 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 117,
          'height' => 42,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: person_.
  $styles['person_'] = array(
    'label' => 'Person Full',
    'effects' => array(
      20 => array(
        'name' => 'manualcrop_crop_and_scale',
        'data' => array(
          'width' => 250,
          'height' => 166,
          'upscale' => 0,
          'respectminimum' => 1,
          'onlyscaleifcrop' => 0,
          'style_name' => 'person_',
        ),
        'weight' => 0,
      ),
      21 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 250,
          'height' => 166,
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
