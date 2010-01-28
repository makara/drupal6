<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function feature_settings_ctools_plugin_api() {
  module_load_include('inc', 'feature_settings', 'feature_settings.defaults');
  $args = func_get_args();
  return call_user_func_array('_feature_settings_ctools_plugin_api', $args);
}

/**
 * Implementation of hook_strongarm().
 */
function feature_settings_strongarm() {
  module_load_include('inc', 'feature_settings', 'feature_settings.defaults');
  $args = func_get_args();
  return call_user_func_array('_feature_settings_strongarm', $args);
}
