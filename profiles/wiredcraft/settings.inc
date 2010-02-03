<?php

/**
 * Basic modules, install before configure form.
 */
function _profile_settings_modules_basic() {
  return array(
    // Drupal core
    'color', 'comment', 'help', 'menu', 'taxonomy', 'dblog',
    // Admin
    'admin',
    // CTools
    'ctools',
    // Views
    'views',
    // Context
    'context',
    // Features
    'features',
    // Image
    'imageapi', 'imageapi_gd', 'imagecache',
  );
}

/**
 * Other modules (contrib, custom, features...).
 *
 * Install before settings.
 */
function _profile_settings_modules_extra() {
  return array(
    // Strongarm
    'strongarm',
    // CCK
    'content', 'optionwidgets', 'text', 'number', 'nodereference', 'userreference',
    // Imagefield
    'filefield', 'imagefield',
    // Date
    'date_api', 'date_timezone', 'date',
    // UIs
    'views_ui', 'context_ui', 'imagecache_ui',
    // Others
    'diff', 'jquery_ui', 'date_popup',
    // Custom features
    'feature_permissions', 'feature_page', 'feature_settings',
    // Custom modules
    // ...
    // Development
    'devel', 'devel_generate',
  );
}

/**
 * Enable these themes.
 */
function _profile_settings_themes() {
  return array('garland', 'rubik', 'cube', 'ninesixty');
}

/**
 * Default to this theme.
 */
function _profile_settings_theme_default() {
  return 'garland';
}

/**
 * Basic settings, for Drupal core and modules in hook_profile_modules().
 */
function _profile_settings_basic() {
}

/**
 * Extra settings.
 */
function _profile_settings_extra() {
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
