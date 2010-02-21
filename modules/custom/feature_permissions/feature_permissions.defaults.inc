<?php

/**
 * Helper to implementation of hook_user_default_permissions().
 */
function _feature_permissions_user_default_permissions() {
  $permissions = array();

  // Exported permission: Use PHP input for field settings (dangerous - grant with care)
  $permissions[] = array(
    'name' => 'Use PHP input for field settings (dangerous - grant with care)',
    'roles' => array(
      '0' => 'admin',
    ),
  );

  // Exported permission: access administration pages
  $permissions[] = array(
    'name' => 'access administration pages',
    'roles' => array(
      '0' => 'admin',
    ),
  );

  // Exported permission: access all views
  $permissions[] = array(
    'name' => 'access all views',
    'roles' => array(
      '0' => 'admin',
    ),
  );

  // Exported permission: access comments
  $permissions[] = array(
    'name' => 'access comments',
    'roles' => array(
      '0' => 'admin',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: access content
  $permissions[] = array(
    'name' => 'access content',
    'roles' => array(
      '0' => 'admin',
      '1' => 'anonymous user',
      '2' => 'authenticated user',
    ),
  );

  // Exported permission: access site reports
  $permissions[] = array(
    'name' => 'access site reports',
    'roles' => array(
      '0' => 'admin',
    ),
  );

  // Exported permission: access user profiles
  $permissions[] = array(
    'name' => 'access user profiles',
    'roles' => array(
      '0' => 'admin',
    ),
  );

  // Exported permission: administer actions
  $permissions[] = array(
    'name' => 'administer actions',
    'roles' => array(
      '0' => 'admin',
    ),
  );

  // Exported permission: administer blocks
  $permissions[] = array(
    'name' => 'administer blocks',
    'roles' => array(
      '0' => 'admin',
    ),
  );

  // Exported permission: administer comments
  $permissions[] = array(
    'name' => 'administer comments',
    'roles' => array(
      '0' => 'admin',
    ),
  );

  // Exported permission: administer content types
  $permissions[] = array(
    'name' => 'administer content types',
    'roles' => array(
      '0' => 'admin',
    ),
  );

  // Exported permission: administer features
  $permissions[] = array(
    'name' => 'administer features',
    'roles' => array(
      '0' => 'admin',
    ),
  );

  // Exported permission: administer files
  $permissions[] = array(
    'name' => 'administer files',
    'roles' => array(
      '0' => 'admin',
    ),
  );

  // Exported permission: administer filters
  $permissions[] = array(
    'name' => 'administer filters',
    'roles' => array(
      '0' => 'admin',
    ),
  );

  // Exported permission: administer imageapi
  $permissions[] = array(
    'name' => 'administer imageapi',
    'roles' => array(
      '0' => 'admin',
    ),
  );

  // Exported permission: administer imagecache
  $permissions[] = array(
    'name' => 'administer imagecache',
    'roles' => array(
      '0' => 'admin',
    ),
  );

  // Exported permission: administer menu
  $permissions[] = array(
    'name' => 'administer menu',
    'roles' => array(
      '0' => 'admin',
    ),
  );

  // Exported permission: administer nodes
  $permissions[] = array(
    'name' => 'administer nodes',
    'roles' => array(
      '0' => 'admin',
    ),
  );

  // Exported permission: administer permissions
  $permissions[] = array(
    'name' => 'administer permissions',
    'roles' => array(
      '0' => 'admin',
    ),
  );

  // Exported permission: administer site configuration
  $permissions[] = array(
    'name' => 'administer site configuration',
    'roles' => array(
      '0' => 'admin',
    ),
  );

  // Exported permission: administer taxonomy
  $permissions[] = array(
    'name' => 'administer taxonomy',
    'roles' => array(
      '0' => 'admin',
    ),
  );

  // Exported permission: administer url aliases
  $permissions[] = array(
    'name' => 'administer url aliases',
    'roles' => array(
      '0' => 'admin',
    ),
  );

  // Exported permission: administer users
  $permissions[] = array(
    'name' => 'administer users',
    'roles' => array(
      '0' => 'admin',
    ),
  );

  // Exported permission: administer views
  $permissions[] = array(
    'name' => 'administer views',
    'roles' => array(
      '0' => 'admin',
    ),
  );

  // Exported permission: change own username
  $permissions[] = array(
    'name' => 'change own username',
    'roles' => array(
      '0' => 'admin',
    ),
  );

  // Exported permission: create url aliases
  $permissions[] = array(
    'name' => 'create url aliases',
    'roles' => array(
      '0' => 'admin',
    ),
  );

  // Exported permission: delete revisions
  $permissions[] = array(
    'name' => 'delete revisions',
    'roles' => array(
      '0' => 'admin',
    ),
  );

  // Exported permission: flush imagecache
  $permissions[] = array(
    'name' => 'flush imagecache',
    'roles' => array(
      '0' => 'admin',
    ),
  );

  // Exported permission: manage features
  $permissions[] = array(
    'name' => 'manage features',
    'roles' => array(
      '0' => 'admin',
    ),
  );

  // Exported permission: post comments
  $permissions[] = array(
    'name' => 'post comments',
    'roles' => array(
      '0' => 'admin',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: post comments without approval
  $permissions[] = array(
    'name' => 'post comments without approval',
    'roles' => array(
      '0' => 'admin',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: revert revisions
  $permissions[] = array(
    'name' => 'revert revisions',
    'roles' => array(
      '0' => 'admin',
    ),
  );

  // Exported permission: select different theme
  $permissions[] = array(
    'name' => 'select different theme',
    'roles' => array(
      '0' => 'admin',
    ),
  );

  // Exported permission: use PHP for block visibility
  $permissions[] = array(
    'name' => 'use PHP for block visibility',
    'roles' => array(
      '0' => 'admin',
    ),
  );

  // Exported permission: view revisions
  $permissions[] = array(
    'name' => 'view revisions',
    'roles' => array(
      '0' => 'admin',
    ),
  );

  return $permissions;
}
