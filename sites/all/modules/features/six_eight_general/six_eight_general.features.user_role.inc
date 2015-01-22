<?php
/**
 * @file
 * six_eight_general.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function six_eight_general_user_default_roles() {
  $roles = array();

  // Exported role: admin.
  $roles['admin'] = array(
    'name' => 'admin',
    'weight' => 2,
  );

  return $roles;
}
