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
/**
 * DEV Purposes only. Remove on live
 */
//if ($_SERVER['SERVER_PORT'] == '8080') dpm('LIVE SERVER');
//if ($_SERVER['SERVER_PORT'] == '8085') dpm('STAGING SERVER');
/**
 * END DEV
 */


  drupal_add_library('system', 'effects');

  // Facebook Link.
  $vars['facebook'] = l('<i class="fa fa-fw fa-facebook-square"></i>', 'https://www.facebook.com/SixEightVineyardChurch/', array('html' => TRUE, 'attributes' => array('target' => '_blank')));

  // Twitter Link.
  $vars['twitter'] = l('<i class="fa fa-fw fa-twitter-square"></i>', 'https://twitter.com/68Vineyard', array('html' => TRUE, 'attributes' => array('target' => '_blank')));

  // Vimeo Link.
  $vars['vimeo'] = l('<i class="fa fa-fw fa-vimeo-square"></i>', 'https://vimeo.com/sixeightchurch', array('html' => TRUE, 'attributes' => array('target' => '_blank')));

  // Vineyard network link.
  $vusa_img_path = $base_path . drupal_get_path('theme', 'sixeight15_theme') . '/imgs/vineyard-usa.png';
  $vars['vineyard_footer_link'] = 'proud member of: ';
  $vars['vineyard_footer_link'] .= l('<img src="' . $vusa_img_path . '" alt="Vineyard USA" title="" />', 'https://vineyardusa.org/welcome/', array('html' => TRUE, 'attributes' => array('target' => '_blank')));

  // Add in search form.
  $search = drupal_get_form('search_form');
  $vars['search'] = render($search);

  // Build primary and secondary flyin menus
  $primary_menu_tree = array();
  $secondary_render = array(
    '#theme' => 'sixeight_flyin_menu_wrapper',
  );

  // get main menu 2 levels deep.
  $mobile_nav = $tree = menu_tree_page_data(variable_get('menu_main_links_source', 'main-menu'), 2, FALSE);

  // Rename so we can use templates for mobile nav only.
  _rename_menu_items($mobile_nav, 'mobile-nav');

  $vars['mobile_nav'] = menu_tree_output($mobile_nav);

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

  $vars['primary_nav'] = menu_tree_output($primary_menu_tree);
  $vars['primary_nav']['#theme_wrappers'] = array('menu_tree__primary');

  $vars['secondary_nav'] = $secondary_render;

  //Helper variables
  $path_to_theme = DRUPAL_ROOT . '/' . path_to_theme();
  $path_to_includes = $path_to_theme . '/theme/includes/';

  $vars['uri'] = request_uri();

  //Includes
  $vars['inc_header'] = $path_to_includes . 'header.php';
  $vars['inc_footer'] = $path_to_includes . 'footer.php';
}

/**
 * Implements hook_preprocess_node().
 */
function sixeight15_theme_preprocess_node(&$vars) {
  $vars['theme_hook_suggestions'][] = 'node__' . $vars['node']->type . '__' . $vars['view_mode'];

  // Add view mode to classes array.
  if (!$vars['teaser']) {
    $vars['classes_array'][] = 'node-' . drupal_html_class($vars['view_mode']);
  }

  $vars['menu'] = array(
    'menu' => array(
      '#markup' => theme('links__system_main_menu', array(
        'links' => menu_navigation_links('main-menu', 1),
        'attributes' => array(
          'class' => array('links', 'secondary-menu'),
        ),
        'heading' => array(
          'text' => t('Secondary menu'),
          'level' => 'h3',
          'class' => array('element-invisible'),
        ),
      )),
      '#prefix' => '<div id="side-menu" class="hidden-xs">',
      '#suffix' => '</div>',
    ),
  );

  if (!empty($vars['node_url']) && $vars['node']->type == 'page') {
    $node_url_exp = explode('/', $vars['node_url']);
    $slug = str_replace('-', '_', end($node_url_exp));
    $vars['theme_hook_suggestions'][] = 'node__page__' . $slug;

    $vars['classes_array'][] = 'page-' . str_replace('_', '-', end($node_url_exp));

    switch($slug) {
    case 'what_we_believe':

      drupal_add_js(drupal_get_path('theme', 'sixeight15_theme') . '/js/wwb.js');

      break;
    case 'contact':

      module_load_include('inc', 'contact', 'contact.pages');
      $vars['contact_form'] = drupal_get_form('contact_site_form');

      break;
    case 'community_groups':

      $vars['community_group_view'] = views_embed_view('community_groups', 'block');

      break;
    case 'systems':

      $vars['system_view'] = views_embed_view('systems', 'block');

      break;
    case 'calendar':
      drupal_add_js(drupal_get_path('theme', 'sixeight15_theme') . '/js/moment.js');
      drupal_add_js(drupal_get_path('theme', 'sixeight15_theme') . '/js/underscore.js');
      drupal_add_js(drupal_get_path('theme', 'sixeight15_theme') . '/js/clndr.min.js');
      drupal_add_js(drupal_get_path('theme', 'sixeight15_theme') . '/js/calendar.js');

      // Build the legend.
      $legend = sixeight_events_build_legend();
      $vars['legend'] = render($legend);

      break;
    case 'people':
      $vars['people'] = views_embed_view('people', 'block');
      break;
    case 'pastor':

      $q = new EntityFieldQuery();
      $q->entityCondition('entity_type', 'node')
        ->entityCondition('bundle', 'person')
        ->propertyCondition('title', 'Jason Guynes');

      $result = $q->execute();

      if (isset($result['node'])) {
        $pastor = node_load(current($result['node'])->nid);
        $build = node_view($pastor, 'full');

        $vars['pastor'] = render($build);
      }

      break;

    case 'home':

      $results = views_get_view_result('home_page_carousel', 'block');

      $carousel = array(
        '#theme' => 'sixeight_bootstrap_carousel',
        '#items' => array(),
        '#id' => 'front-page-carousel',
      );

      foreach ($results as $r) {
        $node = node_load($r->nid);

        $link_mode = '';
        if (isset($node->field_front_ad_no_link [LANGUAGE_NONE][0]['value']) && $node->field_front_ad_no_link [LANGUAGE_NONE][0]['value']) {
          $link_mode = 'nothing';
        }
        elseif (empty($node->field_front_ad_link)) {
          $link_mode = 'content';
        }
        else {
          $link_mode = 'link_field';
        }

        $img = field_view_field('node', $node, 'field_front_ad_image', array(
          'label' => 'hidden',
          'type' => 'image',
          'settings' => array(
            'image_style' => 'home_page_carousel',
            'image_link' => ($link_mode == 'content')? 'content' : '',
          ),
        ));

        $content = ($link_mode != 'link_field')? render($img) : l(render($img), $node->field_front_ad_link[LANGUAGE_NONE][0]['url'], array('html' => true, 'attributes' => $node->field_front_ad_link[LANGUAGE_NONE][0]['attributes']));

        $carousel['#items'][] = array(
          'img' => $content,
        );
      }

      $vars['content']['home_page_carousel'] = render($carousel); // = views_embed_view('home_page_carousel', 'block');
      $vars['content']['home_page_blocks'] = views_embed_view('front_page_block', 'block');

      break;
    }

  }

  if ($vars['node']->type == 'blog') {
    $vars['submitted'] = t('<span>Posted by:</span> !username', array(
      '!username' => $vars['name'],
    ));

    $vars['date'] = '<span class="month">' . date('M', $vars['created']) . '</span>';
    $vars['date'] .= '<span class="day">' . date('d', $vars['created']) . '</span>';
    $vars['date'] .= '<span class="year">' . date('Y', $vars['created']) . '</span>';
  }

  if ($vars['type'] == 'resource' && $vars['view_mode'] == 'full') {
    $node = $vars['node'];

    // Get format.
    $format = '';

    $val = $node->field_resource_type[LANGUAGE_NONE][0]['value'];

    switch ($val) {
    case 'image':

      // TODO: Figure out this bug!!
      if (isset($node->field_resource_image[LANGUAGE_NONE])) {
        $list = $node->field_resource_image[LANGUAGE_NONE];
      }
      else {
        $list = $node->field_resource_image;
      }

      foreach ($list as $i => $img) {
        $purl = parse_url($img['uri']);
        $pi = pathinfo($purl['path']);
        if ($i != 0) $format .= ', ';
        $format .= '.' . $pi['extension'];
      }

      break;
    case 'url':
      $format = 'url';
      break;
    case 'file':
      if (isset($node->field_resource_file[LANGUAGE_NONE])) {
        $purl = parse_url($node->field_resource_file[LANGUAGE_NONE][0]['uri']);
      }
      else {
        $purl = parse_url($node->field_resource_file[0]['uri']);
      }

      $pi = pathinfo($purl['path']);
      $format = '.' . $pi['extension'];
      break;
    case 'video':
      $format = 'video';
      break;
    }

    $vars['format'] = $format;
  }

  if ($vars['view_mode'] == 'sixeight_admin_front_page_block') {
    $vars['title_attributes_array']['class'][] = 'hidden';
  }

  if ($vars['type'] == 'sermon' && $vars['view_mode'] == 'teaser') {
    drupal_add_js(drupal_get_path('theme', 'sixeight15_theme') . '/js/sermon.js');
  }
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
    'sixeight_bootstrap_carousel' => array(
      'render element' => 'carousel',
    ),
    // Override item list to add new variable.
    'item_list' => array(
      'variables' => array('items' => array(), 'title' => NULL, 'title_prefix' => '', 'title_suffix' => '', 'type' => 'ul', 'attributes' => array(), 'list_wrapper' => NULL, 'list_wrapper_attributes' => array()),
    ),
  );

  // Removed .
  //bootstrap_hook_theme_complete($hook_theme, $theme, $path . '/theme');

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



/**
 * Bootstrap theme wrapper function for the mobile nav menu links.
 */
function sixeight15_theme_menu_tree__mobile_nav(&$variables) {
  return '<ul class="menu nav navbar-nav mobile-nav">' . $variables['tree'] . '</ul>';
}

/**
 * Overrides theme_menu_link().
 */
function sixeight15_theme_menu_link__mobile_nav(array $variables) {
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
      $sub_menu = '<ul class="menu nav navbar-nav">' . drupal_render($element['#below']) . '</ul>';
      // Generate as standard dropdown.
      //$element['#title'] .= ' <span class="caret"></span>';
      //$element['#attributes']['class'][] = 'dropdown';
      $element['#localized_options']['html'] = TRUE;

      // Set dropdown trigger element to # to prevent inadvertant page loading
      // when a submenu link is clicked.
      //$element['#localized_options']['attributes']['data-target'] = '#';
      //$element['#localized_options']['attributes']['class'][] = 'dropdown-toggle';
      //$element['#localized_options']['attributes']['data-toggle'] = 'dropdown';
    }
  }
  // On primary navigation menu, class 'active' is not set on active menu item.
  // @see https://drupal.org/node/1896674
  if (($element['#href'] == $_GET['q'] || ($element['#href'] == '<front>' && drupal_is_front_page())) && (empty($element['#localized_options']['language']))) {
    $element['#attributes']['class'][] = 'active';
  }
  $output = l($element['#title'], $element['#href'], $element['#localized_options']);
  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}

/**
 * Implements hook_preprocess_media_vimeo_video().
 */
function sixeight15_theme_preprocess_media_vimeo_video(&$variables) {
  //dpm($variables);
}

function sixeight15_theme_preprocess_views_view(&$vars) {
  $view = $vars['view'];

  $vars['menu'] = theme('links__system_main_menu', array(
    'links' => menu_navigation_links('main-menu', 1),
    'attributes' => array(
      'class' => array('links', 'secondary-menu'),
    ),
    'heading' => array(
      'text' => t('Secondary menu'),
      'level' => 'h3',
      'class' => array('element-invisible'),
    )
  ));

  $vars['menu'] = array(
    '#markup' => theme('links__system_main_menu', array(
      'links' => menu_navigation_links('main-menu', 1),
      'attributes' => array(
        'class' => array('links', 'secondary-menu'),
      ),
      'heading' => array(
        'text' => t('Secondary menu'),
        'level' => 'h3',
        'class' => array('element-invisible'),
      ),
    )),
    '#prefix' => '<div id="side-menu" class="hidden-xs">',
    '#suffix' => '</div>',
  );

  switch ($view->name) {
  case 'sermons':
    $vars['title'] = 'Sermons';
    break;
  case 'blog':
    $vars['title'] = 'Blog<span>Rants, Raves, and maybe some Wisdom';
    break;
  case 'resources_by_term':
    $vars['title'] = 'Other Resources';
    break;

  }

}

/**
 * Rename menu items so they use a different hook.
 */
function _rename_menu_items(&$menu_items, $new_name) {
  foreach ($menu_items as &$item) {
    if (isset($item['link']['menu_name'])) {
      $item['link']['menu_name'] = $new_name;

      if (isset($item['below']) && count($item['below']) > 0) {
        _rename_menu_items($item['below'], $new_name);
      }
    }
  }
}


/**
 * Overrides theme_item_list().
 */
function sixeight15_theme_item_list($variables) {
  $items = $variables['items'];
  $title = $variables['title'];
  $type = $variables['type'];
  $attributes = $variables['attributes'];
  $list_wrapper = $variables['list_wrapper'];
  $list_wrapper_attributes = $variables['list_wrapper_attributes'];
  $output = '';


  if (isset($variables['title_prefix'])) {
    $output .= $variables['title_prefix'];
  }

  if (isset($title)) {
    $output .= '<h3>' . $title . '</h3>';
  }

  if (isset($variables['title_suffix'])) {
    $output .= $variables['title_suffix'];
  }

  if (!is_null($list_wrapper)) {
    $output .= "<$list_wrapper" . drupal_attributes($list_wrapper_attributes) . '>';
  }

  if (!empty($items)) {
    $output .= "<$type" . drupal_attributes($attributes) . '>';
    $num_items = count($items);
    $i = 0;
    foreach ($items as $item) {
      $attributes = array();
      $children = array();
      $data = '';
      $i++;
      if (is_array($item)) {
        foreach ($item as $key => $value) {
          if ($key == 'data') {
            $data = $value;
          }
          elseif ($key == 'children') {
            $children = $value;
          }
          else {
            $attributes[$key] = $value;
          }
        }
      }
      else {
        $data = $item;
      }
      if (count($children) > 0) {
        // Render nested list.
        $data .= theme('item_list', array(
          'items' => $children,
          'title' => NULL,
          'type' => $type,
          'attributes' => $attributes,
        ));
      }
      if ($i == 1) {
        $attributes['class'][] = 'first';
      }
      if ($i == $num_items) {
        $attributes['class'][] = 'last';
      }
      $output .= '<li' . drupal_attributes($attributes) . '>' . $data . "</li>\n";
    }
    $output .= "</$type>";
  }

  if (!is_null($list_wrapper)) {
    $output .= "</$list_wrapper>";
  }

  return $output;
}
