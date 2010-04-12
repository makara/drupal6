<?php

/**
 * Implementation of hook_user_default_permissions().
 */
function feature_permissions_user_default_permissions() {
  module_load_include('inc', 'feature_permissions', 'feature_permissions.defaults');
  $args = func_get_args();
  return call_user_func_array('_feature_permissions_user_default_permissions', $args);
}
