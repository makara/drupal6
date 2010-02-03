<?php

/**
 * The batch tasks.
 */
function _profile_batch_tasks() {
  $tasks = array();
  $tasks['install-modules-batch'] = st('Install other modules');
  $tasks['install-configure-batch'] = st('Other configurations');
  return $tasks;
}

/**
 * Set batch.
 */
function _profile_batch_install_modules($url) {
  $modules = _profile_settings_modules_extra();
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

  return;
}

/**
 * Set batch.
 */
function _profile_batch_install_configure($url) {
  $batch['title'] = st('Configuring @drupal', array('@drupal' => drupal_install_profile_name()));
  $batch['operations'][] = array('_profile_settings_extra', array());
  $batch['operations'][] = array('_profile_flush_cache', array());
  $batch['operations'][] = array('_profile_init_blocks', array());
  $batch['finished'] = '_profile_configure_finished';
  variable_set('install_task', 'install-configure-batch');
  batch_set($batch);
  batch_process($url, $url);

  return;
}

/**
 * Flush caches.
 */
function _profile_flush_cache() {
  module_rebuild_cache();
  drupal_get_schema(NULL, TRUE); // Clear schema DB cache
  drupal_flush_all_caches();
}

/**
 * Init blocks.
 */
function _profile_init_blocks() {
	global $custom_theme, $theme_key;
	$backup_custom_theme = $custom_theme;
	$backup_theme_key = $theme_key;

  // Enable themes.
  foreach (_profile_settings_themes() as $key) {
    $custom_theme = $theme_key = $key;
    db_query("UPDATE {system} SET status = 1 WHERE type = 'theme' and name = '%s'", $key);
    _block_rehash();
    // Set default theme.
    if (_profile_settings_theme_default() == $key) {
      variable_set('theme_default', $key);
      $backup_custom_theme = $backup_theme_key = $key;
    }
  }
  // Disable all the blocks.
  db_query("UPDATE {blocks} SET status = 0, weight = 0, region = ''");

  $custom_theme = $backup_custom_theme;
  $theme_key = $backup_theme_key;
}

/**
 * Finished callback.
 */
function _profile_install_modules_finished($success, $results) {
  variable_set('install_task', 'install-configure');
}

/**
 * Finished callback.
 */
function _profile_configure_finished($success, $results) {
  variable_set('install_task', 'profile-finished');
}

/**
 * Copied from drupal_install_modules().
 */
function _profile_check_module_dependencies($module_list) {
  $files = module_rebuild_cache();
  $module_list = array_flip(array_values($module_list));
  do {
    $moved = FALSE;
    foreach ($module_list as $module => $weight) {
      $file = $files[$module];
      if (isset($file->info['dependencies']) && is_array($file->info['dependencies'])) {
        foreach ($file->info['dependencies'] as $dependency) {
          if (isset($module_list[$dependency]) && $module_list[$module] < $module_list[$dependency] +1) {
            $module_list[$module] = $module_list[$dependency] +1;
            $moved = TRUE;
          }
        }
      }
    }
  } while ($moved);
  asort($module_list);
  $module_list = array_keys($module_list);

  return $module_list;
}

/**
 * Save date formats.
 *
 * NOTE & TODO: there is a limitation in date_format_save(), which doesn't save locales before enable the language.
 */
function _profile_save_date_formats($formats, $type = 'short', $langcode = 'en') {
  $default_format = array(
    'is_new'  => TRUE,
    'type'    => $type,
    'format'  => '',
    'locked'  => 1,
    'locales' => array($langcode),
  );
  foreach ($formats as $format) {
    $date_format = array_merge($default_format, $format);
    date_format_save($date_format);
    if (!empty($date_format['default'])) {
      variable_set('date_format_'. $type, (string)$date_format['format']);
    }
  }
}
