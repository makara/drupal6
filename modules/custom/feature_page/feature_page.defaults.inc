<?php

/**
 * Helper to implementation of hook_user_default_permissions().
 */
function _feature_page_user_default_permissions() {
  $permissions = array();

  // Exported permission: create page content
  $permissions[] = array(
    'name' => 'create page content',
    'roles' => array(
      '0' => 'admin',
    ),
  );

  // Exported permission: delete any page content
  $permissions[] = array(
    'name' => 'delete any page content',
    'roles' => array(
      '0' => 'admin',
    ),
  );

  // Exported permission: delete own page content
  $permissions[] = array(
    'name' => 'delete own page content',
    'roles' => array(
      '0' => 'admin',
    ),
  );

  // Exported permission: edit any page content
  $permissions[] = array(
    'name' => 'edit any page content',
    'roles' => array(
      '0' => 'admin',
    ),
  );

  // Exported permission: edit own page content
  $permissions[] = array(
    'name' => 'edit own page content',
    'roles' => array(
      '0' => 'admin',
    ),
  );

  return $permissions;
}
