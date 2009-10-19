<?php
// $Id$

/**
 * Implementation of hook_drush_help().
 */
function phpinfo_drush_help($section) {
  switch ($section) {
    case 'drush:phpinfo':
      return dt('Display phpinfo.');
  }
}

/**
 * Implementation of hook_drush_command().
 */
function phpinfo_drush_command() {
  $items = array();
  $items['phpinfo'] = array(
    'description' => 'Display phpinfo.',
  );
  return $items;
}

/**
 * Command callback.
 */
function drush_phpinfo_phpinfo() {
  phpinfo();
}

