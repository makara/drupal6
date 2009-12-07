<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function feature_page_ctools_plugin_api() {
  module_load_include('inc', 'feature_page', 'feature_page.defaults');
  $args = func_get_args();
  return call_user_func_array('_feature_page_ctools_plugin_api', $args);
}

/**
 * Implementation of hook_node_info().
 */
function feature_page_node_info() {
  module_load_include('inc', 'feature_page', 'feature_page.features.node');
  $args = func_get_args();
  return call_user_func_array('_feature_page_node_info', $args);
}

/**
 * Implementation of hook_user_default_permissions().
 */
function feature_page_user_default_permissions() {
  module_load_include('inc', 'feature_page', 'feature_page.defaults');
  $args = func_get_args();
  return call_user_func_array('_feature_page_user_default_permissions', $args);
}

/**
 * Implementation of hook_strongarm().
 */
function feature_page_strongarm() {
  module_load_include('inc', 'feature_page', 'feature_page.defaults');
  $args = func_get_args();
  return call_user_func_array('_feature_page_strongarm', $args);
}
