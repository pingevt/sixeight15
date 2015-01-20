<?php

/**
 * @file
 * template.php
 */


/**
 * Implements hook_preprocess_page().
 */
function sixeight15_theme_preprocess_page(&$vars) {
  // Add in search form.
  $search = drupal_get_form('search_form');
  $vars['search'] = render($search);

}

function sixeight15_theme_bootstrap_search_form_wrapper($variables) {
  $output = '<div class="input-group">';
  $output .= $variables['element']['#children'];
  $output .= '<span class="input-group-btn">';
  $output .= '<button type="submit" class="btn btn-default">';

  $output .= '<i class="fa fa-search"></i>';
  $output .= '</button>';
  $output .= '</span>';
  $output .= '</div>';
  return $output;
}
