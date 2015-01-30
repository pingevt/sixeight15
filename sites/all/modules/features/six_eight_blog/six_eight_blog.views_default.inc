<?php
/**
 * @file
 * six_eight_blog.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function six_eight_blog_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'blog';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Blog';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Blog';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['autosubmit'] = TRUE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'node';
  $handler->display->display_options['row_options']['links'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'blog' => 'blog',
  );
  /* Filter criterion: Content: Topics (field_blog_topics) */
  $handler->display->display_options['filters']['field_blog_topics_tid']['id'] = 'field_blog_topics_tid';
  $handler->display->display_options['filters']['field_blog_topics_tid']['table'] = 'field_data_field_blog_topics';
  $handler->display->display_options['filters']['field_blog_topics_tid']['field'] = 'field_blog_topics_tid';
  $handler->display->display_options['filters']['field_blog_topics_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_blog_topics_tid']['expose']['operator_id'] = 'field_blog_topics_tid_op';
  $handler->display->display_options['filters']['field_blog_topics_tid']['expose']['label'] = 'Topics';
  $handler->display->display_options['filters']['field_blog_topics_tid']['expose']['operator'] = 'field_blog_topics_tid_op';
  $handler->display->display_options['filters']['field_blog_topics_tid']['expose']['identifier'] = 'field_blog_topics_tid';
  $handler->display->display_options['filters']['field_blog_topics_tid']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_blog_topics_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  $handler->display->display_options['filters']['field_blog_topics_tid']['reduce_duplicates'] = TRUE;
  $handler->display->display_options['filters']['field_blog_topics_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_blog_topics_tid']['vocabulary'] = 'blog_categories';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'resources/blog';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Blog';
  $handler->display->display_options['menu']['name'] = 'main-menu';
  $export['blog'] = $view;

  return $export;
}
