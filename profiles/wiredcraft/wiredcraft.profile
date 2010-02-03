<?php
// $Id$

if (is_string($profile)) {
  include_once './profiles/'. $profile .'/functions.inc';
  include_once './profiles/'. $profile .'/settings.inc';
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
  return _profile_settings_modules_basic();
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
    _profile_batch_install_modules();
    // For CLI
    return;
  }

  // Additional configurations.
  if ($task == 'install-configure') {
    _profile_batch_install_configure();
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
