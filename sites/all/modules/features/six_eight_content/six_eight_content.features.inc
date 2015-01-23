<?php
/**
 * @file
 * six_eight_content.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function six_eight_content_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
