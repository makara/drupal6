<?php
// $Id$

/**
 * Implementation of hook_drush_help().
 */
function newpm_drush_help($section) {
  switch ($section) {
    case 'drush:update-allcode':
      return dt('Update code of all modules, including not installed.');
  }
}

/**
 * Implementation of hook_drush_command().
 */
function newpm_drush_command() {
  $items = array();
  $items['update-allcode'] = array(
    'drupal dependencies' => array('update'),
    'description' => 'Update code of all modules, including not installed.',
    'aliases' => array('upall'),
  );
  return $items;
}

/**
 * My callback.
 */
function drush_newpm_update_allcode() {
  // Refresh
  drush_print(dt("Refreshing update status information ..."));
  $status = drush_newpm_refresh();
  if (empty($status)) {
    // TODO
  }

  $args = func_get_args();
  array_unshift($args, 'pm-updatecode');
  call_user_func_array('drush_invoke', $args);
}

/**
 * Replace update_refresh().
 */
function drush_newpm_refresh() {
  global $base_url;
  module_load_include('inc', 'update', 'update.fetch');
  module_load_include('inc', 'update', 'update.compare');

  update_invalidate_cache();

  $available = array();
  $data = array();
  $site_key = md5($base_url . drupal_get_private_key());

  // A fake/wrong/hack cache
  $module_array = module_rebuild_cache();
  foreach($module_array as $module) {
    // Don't check things in cvs workspace
    if (strpos($module->filename, 'cvs_workspace')) {
      $module->status = 0;
    }
    else {
      $module->status = 1;
    }
  }
  _update_process_info_list($projects, $module_array, 'module');
  _update_cache_set('update_project_projects', $projects, time() + 600);

  foreach ($projects as $key => $project) {
    $url = _update_build_fetch_url($project, $site_key);
    $xml = drupal_http_request($url);
    if (isset($xml->data)) {
      $data[] = $xml->data;
    }
  }

  if ($data) {
    $parser = new update_xml_parser;
    $available = $parser->parse($data);
  }
  if (!empty($available) && is_array($available)) {
    // update.module changed to 'update_available_releases', drush still 'update_info'...
    _update_cache_set('update_available_releases', $available, time() + 600);
    _update_cache_set('update_info', $available, time() + 600);
    variable_set('update_last_check', time());
  }
  else {
    return FALSE;
  }
  return $available;
}
