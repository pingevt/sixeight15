<?php
/**
 * @file
 * resources_features.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function resources_features_taxonomy_default_vocabularies() {
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
