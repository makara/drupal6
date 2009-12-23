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
 * Basic settings, for Drupal core and modules in hook_profile_modules().
 */
function _profile_settings_basic() {
  // Performance
  variable_set('cache', CACHE_NORMAL);
  variable_set('block_cache', CACHE_NORMAL);
  // Imageapi
  variable_set('imageapi_jpeg_quality', 90);
  // Site information
  // ...
}

/**
 * Other modules (contrib, custom, features...).
 */
function _profile_other_modules() {
  return array(
    // Strongarm
    'strongarm',
    // CCK
    'content', 'optionwidgets', 'text', 'number', 'nodereference', 'userreference',
    // Date
    'date_api', 'date_timezone', 'date',
    // UIs
    'views_ui', 'context_ui', 'imagecache_ui',
    // Others
    'diff', 'jquery_ui', 'date_popup',
    // Development
    'devel', 'devel_generate', 'admin_menu',
    // Custom features
    'feature_permissions', 'feature_page',
    // Custom modules
    // ...
  );
}

/**
 * Extra settings.
 */
function _profile_settings_extra() {
  // Date
  variable_set('date_default_timezone_name', 'Asia/Shanghai');

  // Date format: date only
  $date_format_type = array('is_new'  => TRUE, 'type' => 'date_only', 'title' => 'Date only', 'locked' => 1);
  date_format_type_save($date_format_type);
  $formats = array(
    array('format' => 'Y-m-d', 'default' => TRUE),
    array('format' => 'm/d/Y'),
    array('format' => 'd/m/Y'),
    array('format' => 'Y/m/d'),
  );
  _profile_save_date_formats($formats, 'date_only');

  // Date format: time only
  $date_format_type = array('is_new'  => TRUE, 'type' => 'time_only', 'title' => 'Time only', 'locked' => 1);
  date_format_type_save($date_format_type);
  $formats = array(
    array('format' => 'H:i', 'default' => TRUE),
    array('format' => 'g:ia'),
    array('format' => 'G:i'),
  );
  _profile_save_date_formats($formats, 'time_only');
}

/**
 * Flush caches.
 */
function _profile_finalize() {
  module_rebuild_cache();
  drupal_get_schema(NULL, TRUE); // Clear schema DB cache
  drupal_flush_all_caches();
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
