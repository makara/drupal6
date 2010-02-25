<?php
// $Id$



/**
 * Back-ported from Drupal 7.
 */

/**
 * Render and print an element.
 *
 * This function renders an element using drupal_render(). The top level
 * element is always rendered even if hide() had been previously used on it.
 *
 * Any nested elements are only rendered if they haven't been rendered before
 * or if they have been re-enabled with show().
 *
 * @see drupal_render()
 * @see show()
 * @see hide()
 */
function render(&$element) {
  if (is_array($element)) {
    show($element);
    return drupal_render($element);
  }
  else {
    // Safe-guard for inappropriate use of render() on flat variables: return
    // the variable as-is.
    return $element;
  }
}

/**
 * Hide an element from later rendering.
 *
 * @see render()
 * @see show()
 */
function hide(&$element) {
  $element['#printed'] = TRUE;
  return $element;
}

/**
 * Show a hidden or already printed element from later rendering.
 *
 * Alternatively, render($element) could be used which automatically shows the
 * element while rendering it.
 *
 * @see render()
 * @see hide()
 */
function show(&$element) {
  // Changed to NULL from FALSE.
  $element['#printed'] = NULL;
  return $element;
}
