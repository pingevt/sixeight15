<?php
/**
 * @file
 * six_eight_general.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function six_eight_general_taxonomy_default_vocabularies() {
  return array(
    'resource_categories' => array(
      'name' => 'Resource categories',
      'machine_name' => 'resource_categories',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
