<?php
/**
 * @file
 * six_eight_sermons.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function six_eight_sermons_taxonomy_default_vocabularies() {
  return array(
    'sermon_topics' => array(
      'name' => 'Sermon Topics',
      'machine_name' => 'sermon_topics',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
