<?php
// $Id$

if (is_string($profile)) {
  include_once './profiles/'. $profile .'/functions.inc';
}

/**
 * Implementation of hook_profile_details().
 */
function wiredcraft_profile_details() {
  return array(
    'name' => 'Wiredcraft Basic',
    'description' => 'The basic profile, on which we build other profiles.'
  );
}

/**
 * Implementation of hook_profile_modules().
 */
function wiredcraft_profile_modules() {
  $modules = array(
    // Drupal core
    'color', 'comment', 'help', 'menu', 'taxonomy', 'dblog',
    // Admin
    'admin',
    // CTools
    'ctools',
    // Views
    'views',
    // Context
    'context', 'context_contrib',
    // Features
    'features',
    // Image
    'imageapi', 'imageapi_gd', 'imagecache',
  );
  return $modules;
}

/**
 * Implementation of hook_profile_task_list().
 */
function wiredcraft_profile_task_list() {
  $tasks = array();
  return $tasks + _profile_batch_tasks();
}

/**
 * Implementation of hook_profile_tasks().
 */
function wiredcraft_profile_tasks(&$task, $url) {
  // The output, returns in the end.
  $output = '';

  // The batch tasks.
  $batch_tasks = _profile_batch_tasks();
  if (in_array($task, array_keys($batch_tasks))) {
    include_once 'includes/batch.inc';
    $output = _batch_page();
  }

  // Basic settings, for Drupal core and modules in hook_profile_modules().
  if ($task == 'profile') {
    _profile_settings_basic();
    // Next
    $task = 'install-modules';
  }

  // Install other modules.
  if ($task == 'install-modules') {
    $modules = _profile_other_modules();
    $modules = _profile_check_module_dependencies($modules);
    $files = module_rebuild_cache();
    // Create batch.
    foreach ($modules as $module) {
      $batch['operations'][] = array('_install_module_batch', array($module, $files[$module]->info['name']));
    }
    $batch['finished'] = '_profile_install_modules_finished';
    $batch['title'] = st('Installing other modules');
    $batch['error_message'] = st('The installation has encountered an error.');
    variable_set('install_task', 'install-modules-batch');
    batch_set($batch);
    batch_process($url, $url);
    // For CLI
    return;
  }

  // Additional configurations.
  if ($task == 'install-configure') {
    $batch['title'] = st('Configuring @drupal', array('@drupal' => drupal_install_profile_name()));
    $batch['operations'][] = array('_profile_settings_extra', array());
    $batch['operations'][] = array('_profile_finalize', array());
    $batch['operations'][] = array('drupal_cron_run', array());
    $batch['finished'] = '_profile_configure_finished';
    variable_set('install_task', 'install-configure-batch');
    batch_set($batch);
    batch_process($url, $url);
    // For CLI
    return;
  }

  return $output;
}

/**
 * Implementation of hook_form_alter().
 */
function wiredcraft_form_alter(&$form, $form_state, $form_id) {
  if ($form_id == 'install_configure') {
    // Set default for site name field.
    $form['site_information']['site_name']['#default_value'] = 'Wiredcraft Basic';
  }
}
