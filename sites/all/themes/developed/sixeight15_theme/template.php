<?php

/**
 * @file
 * template.php
 */


/**
 * Implements hook_preprocess_page().
 */
function sixeight15_theme_preprocess_page(&$vars) {
  global $base_path;

  drupal_add_library('system', 'effects');

  // Facebook Link.
  $vars['facebook'] = l('<i class="fa fa-fw fa-facebook-square"></i>', 'https://www.facebook.com/pages/SixEight-Community-Of-Faith/156876004356216', array('html' => TRUE, 'attributes' => array('target' => '_blank')));

  // Twitter Link.
  $vars['twitter'] = l('<i class="fa fa-fw fa-twitter-square"></i>', 'https://twitter.com/68Ardmore', array('html' => TRUE, 'attributes' => array('target' => '_blank')));

  // Vimeo Link.
  $vars['vimeo'] = l('<i class="fa fa-fw fa-vimeo-square"></i>', 'https://vimeo.com/sixeightchurch', array('html' => TRUE, 'attributes' => array('target' => '_blank')));

  // Vineyard network link.
  $vusa_img_path = $base_path . drupal_get_path('theme', 'sixeight15_theme') . '/imgs/vineyard-usa.png';
  $vars['vineyard_footer_link'] = 'proud member of: ';
  $vars['vineyard_footer_link'] .= l('<img src="' . $vusa_img_path . '" alt="Vineyard USA" title="" />', 'http://www.vineyardusa.org', array('html' => TRUE, 'attributes' => array('target' => '_blank')));

  // Add in search form.
  $search = drupal_get_form('search_form');
  $vars['search'] = render($search);

  // Build primary and secondary flyin menus
  $primary_menu_tree = array();
  $secondary_render = array(
    '#theme' => 'sixeight_flyin_menu_wrapper',
  );

  // get main menu 2 levels deep.
  $tree = menu_tree_all_data(variable_get('menu_main_links_source', 'main-menu'), NULL, 2);

  foreach ($tree as $i => $parent) {
    $menu = menu_tree_output($parent['below']);

    if (count($parent['below']) > 0) {
      $menu = menu_tree_output($parent['below']);
      $menu['#theme_wrappers'] = array('menu_tree__main_menu__flyin');

      foreach (element_children($menu) as $child_key) {
        $menu[$child_key]['#theme'] = 'menu_link__main_menu__flyin';
      }

      $flyin = array(
        '#theme' => 'sixeight_flyin_menu',
        'menu' => $menu,
        '#title' => isset($parent['link']['options']['attributes']['title'])? $parent['link']['options']['attributes']['title'] : '',
        '#flyin-id' => $parent['link']['mlid'] . '-flyin-menu',
      );
      $secondary_render[] = $flyin;

      // Add class and data for flyin parent
      $parent['link']['localized_options']['attributes']['class'] = array('flyin-trigger');
      $parent['link']['localized_options']['attributes']['data-target'] = $parent['link']['mlid'] . '-flyin-menu';
    }

    $parent['below'] = array();
    $primary_menu_tree[$i] = $parent;
  }

//dpm($primary_menu_tree);
  $vars['primary_nav'] = menu_tree_output($primary_menu_tree);
  $vars['primary_nav']['#theme_wrappers'] = array('menu_tree__primary');
//dpm($secondary_render);
  $vars['secondary_nav'] = $secondary_render;
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

/**
 * Implements hook_theme().
 */
function sixeight15_theme_theme(&$existing, $type, $theme, $path) {
  $hook_theme = array(
    'sixeight_flyin_menu_wrapper' => array(
      'render element' => 'item',
    ),
    'sixeight_flyin_menu' => array(
      'render element' => 'item',
    ),
  );

  bootstrap_hook_theme_complete($hook_theme, $theme, $path . '/theme');

  return $hook_theme;
}

function sixeight15_theme_menu_tree__main_menu__flyin(&$variables) {
  return '<div class="menu">' . $variables['tree'] . '</div>';
}

function sixeight15_theme_menu_link__main_menu__flyin(&$variables) {
  $element = $variables['element'];
  $sub_menu = '';

  if ($element['#below']) {
    // Prevent dropdown functions from being added to management menu so it
    // does not affect the navbar module.
    if (($element['#original_link']['menu_name'] == 'management') && (module_exists('navbar'))) {
      $sub_menu = drupal_render($element['#below']);
    }
    elseif ((!empty($element['#original_link']['depth'])) && ($element['#original_link']['depth'] == 1)) {
      // Add our own wrapper.
      unset($element['#below']['#theme_wrappers']);
      $sub_menu = '<ul class="dropdown-menu">' . drupal_render($element['#below']) . '</ul>';
      // Generate as standard dropdown.
      $element['#title'] .= ' <span class="caret"></span>';
      $element['#attributes']['class'][] = 'dropdown';
      $element['#localized_options']['html'] = TRUE;

      // Set dropdown trigger element to # to prevent inadvertant page loading
      // when a submenu link is clicked.
      $element['#localized_options']['attributes']['data-target'] = '#';
      $element['#localized_options']['attributes']['class'][] = 'dropdown-toggle';
      $element['#localized_options']['attributes']['data-toggle'] = 'dropdown';
    }
  }
  // On primary navigation menu, class 'active' is not set on active menu item.
  // @see https://drupal.org/node/1896674
  if (($element['#href'] == $_GET['q'] || ($element['#href'] == '<front>' && drupal_is_front_page())) && (empty($element['#localized_options']['language']))) {
    $element['#attributes']['class'][] = 'active';
  }
  $element['#attributes']['class'][] = 'col-md-4';
  $output = l($element['#title'], $element['#href'], $element['#localized_options']);
  return '<div' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</div>\n";
}
