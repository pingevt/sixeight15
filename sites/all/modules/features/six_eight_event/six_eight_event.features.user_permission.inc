<?php
/**
 * @file
 * six_eight_event.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function six_eight_event_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'sync sixeight events'.
  $permissions['sync sixeight events'] = array(
    'name' => 'sync sixeight events',
    'roles' => array(
      'admin' => 'admin',
      'editor' => 'editor',
    ),
    'module' => 'sixeight_events',
  );

  return $permissions;
}
