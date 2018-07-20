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
      3 => array(
        'name' => 'manualcrop_crop_and_scale',
        'data' => array(
          'width' => 1450,
          'height' => 1450,
          'upscale' => 1,
          'respectminimum' => 1,
          'onlyscaleifcrop' => 0,
          'style_name' => 'rss_images',
        ),
        'weight' => 0,
      ),
    ),
  );

  return $styles;
}
