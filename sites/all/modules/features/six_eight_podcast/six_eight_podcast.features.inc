<?php
/**
 * @file
 * six_eight_podcast.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function six_eight_podcast_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function six_eight_podcast_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function six_eight_podcast_image_default_styles() {
  $styles = array();

  // Exported image style: rss_images.
  $styles['rss_images'] = array(
    'label' => 'RSS Images',
    'effects' => array(
      4 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => '',
          'height' => 1450,
          'upscale' => 1,
        ),
        'weight' => 1,
      ),
    ),
  );

  return $styles;
}
