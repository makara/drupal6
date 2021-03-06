<?php
/**
 * @file.
 */
require_once './sites/all/libraries/profiler/profiler.inc';
require_once './sites/all/libraries/profiler/profiler_api.inc';
require_once './sites/all/libraries/profile_helper/profile_helper.inc';

define('PROFILE_KEY', 'drupal6_profiler');

/**
 * Implements hook_profile_details().
 */
function drupal6_profiler_profile_details() {
  return profiler_v2_load_config(PROFILE_KEY);
}

/**
 * Implements hook_profile_modules().
 */
function drupal6_profiler_profile_modules() {
  return profiler_profile_modules(profiler_v2_load_config(PROFILE_KEY));
}

/**
 * Implements hook_profile_task_list().
 */
function drupal6_profiler_profile_task_list() {
  $tasks = profiler_profile_task_list(profiler_v2_load_config(PROFILE_KEY));
  return $tasks + _profile_batch_tasks();
}

/**
 * Implements hook_profile_tasks().
 */
function drupal6_profiler_profile_tasks(&$task, $url) {
  // The output, returns in the end.
  $output = '';

  // Run batch tasks.
  $batch_tasks = _profile_batch_tasks();
  if (array_key_exists($task, $batch_tasks)) {
    include_once 'includes/batch.inc';
    include_once 'includes/locale.inc';
    $output = _batch_page();
  }

  // Basic settings.
  if ($task == 'profile') {
    // Other configurations - a batch process.
    $batch = _install_custom_configure($url);

    // Process
    batch_set($batch);
    batch_process($url, $url);

    // In case.
    return;
  }

  return $output;
}

/**
 * Implements hook_form_alter().
 */
function drupal6_profiler_form_alter(&$form, $form_state, $form_id) {
  return profiler_form_alter(profiler_v2_load_config(PROFILE_KEY), $form, $form_state, $form_id);
}

/**
 * Implementation of hook_install().
 */
function drupal6_profiler_install() {
}

/**
 * Private.
 */

/**
 * The batch tasks.
 */
function _profile_batch_tasks() {
  $tasks = array();
  $tasks['install_custom_configure'] = st('Other configurations');
  return $tasks;
}

/**
 * Batch finished callback.
 */
function _profile_batch_task_finished($success = TRUE, $results = array(), $operations = array()) {
  _profile_set_current_task(TRUE);
}

/**
 * Task callback.
 */
function _install_custom_configure($url) {
  $batch = array();
  $batch['title'] = st('Configuring @drupal', array('@drupal' => drupal_install_profile_name()));

  // Invoke profiler.
  $batch['operations'][] = array('profile_helper_invoke_profiler', array(PROFILE_KEY, 'profile', $url));
  $batch['operations'][] = array('profile_helper_flush_cache', array());

  // Enable admin theme.
  $batch['operations'][] = array('profile_helper_enable_admin_theme', array('rubik', TRUE));
  $batch['operations'][] = array('profile_helper_disable_all_blocks', array());
  $batch['operations'][] = array('profile_helper_flush_cache', array());

  // Next - the batch task.
  variable_set('install_task', 'install_custom_configure');

  $batch['error_message'] = st('The configuration has encountered an error.');
  $batch['finished'] = '_install_custom_configure_finished';
  return $batch;
}

/**
 * Batch finished callback.
 */
function _install_custom_configure_finished($success, $results, $operations) {
  variable_set('atrium_install', 1);

  // Next.
  variable_set('install_task', 'profile-finished');
}
