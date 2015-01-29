<?php
/**
 * @file
 * six_eight_sermons.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function six_eight_sermons_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'sermons';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Sermons';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Sermons';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['autosubmit_hide'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'mini';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'node';
  $handler->display->display_options['row_options']['links'] = FALSE;
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['empty'] = TRUE;
  $handler->display->display_options['header']['area']['content'] = 'Below are past sermons listed by title, series, speaker & passage. There is also a brief description of each for your convenience. Sermons are posted by the end of the day on the Wednesday following each Sunday. We provide audio & written files along with a pdf of the slides used. Each sermon is color coded in the text to correspond to slide changes. Enjoy!';
  $handler->display->display_options['header']['area']['format'] = 'full_html';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Sort criterion: Content: Date (field_sermon_date) */
  $handler->display->display_options['sorts']['field_sermon_date_value']['id'] = 'field_sermon_date_value';
  $handler->display->display_options['sorts']['field_sermon_date_value']['table'] = 'field_data_field_sermon_date';
  $handler->display->display_options['sorts']['field_sermon_date_value']['field'] = 'field_sermon_date_value';
  $handler->display->display_options['sorts']['field_sermon_date_value']['expose']['label'] = 'Date (field_sermon_date)';
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
    'sermon' => 'sermon',
  );
  /* Filter criterion: Content: Date (field_sermon_date) */
  $handler->display->display_options['filters']['field_sermon_date_value']['id'] = 'field_sermon_date_value';
  $handler->display->display_options['filters']['field_sermon_date_value']['table'] = 'field_data_field_sermon_date';
  $handler->display->display_options['filters']['field_sermon_date_value']['field'] = 'field_sermon_date_value';
  $handler->display->display_options['filters']['field_sermon_date_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_sermon_date_value']['expose']['operator_id'] = 'field_sermon_date_value_op';
  $handler->display->display_options['filters']['field_sermon_date_value']['expose']['label'] = 'Date';
  $handler->display->display_options['filters']['field_sermon_date_value']['expose']['operator'] = 'field_sermon_date_value_op';
  $handler->display->display_options['filters']['field_sermon_date_value']['expose']['identifier'] = 'field_sermon_date_value';
  $handler->display->display_options['filters']['field_sermon_date_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  $handler->display->display_options['filters']['field_sermon_date_value']['granularity'] = 'month';
  $handler->display->display_options['filters']['field_sermon_date_value']['year_range'] = '2012:+0';
  /* Filter criterion: Content: Scripture Passage (field_sermon_scripture_passage:book_name) */
  $handler->display->display_options['filters']['field_sermon_scripture_passage_book_name']['id'] = 'field_sermon_scripture_passage_book_name';
  $handler->display->display_options['filters']['field_sermon_scripture_passage_book_name']['table'] = 'field_data_field_sermon_scripture_passage';
  $handler->display->display_options['filters']['field_sermon_scripture_passage_book_name']['field'] = 'field_sermon_scripture_passage_book_name';
  $handler->display->display_options['filters']['field_sermon_scripture_passage_book_name']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_sermon_scripture_passage_book_name']['expose']['operator_id'] = 'field_sermon_scripture_passage_book_name_op';
  $handler->display->display_options['filters']['field_sermon_scripture_passage_book_name']['expose']['label'] = 'Scripture Passage';
  $handler->display->display_options['filters']['field_sermon_scripture_passage_book_name']['expose']['operator'] = 'field_sermon_scripture_passage_book_name_op';
  $handler->display->display_options['filters']['field_sermon_scripture_passage_book_name']['expose']['identifier'] = 'field_sermon_scripture_passage_book_name';
  $handler->display->display_options['filters']['field_sermon_scripture_passage_book_name']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['field_sermon_scripture_passage_book_name']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  /* Filter criterion: Content: Speaker (field_speaker) */
  $handler->display->display_options['filters']['field_speaker_target_id']['id'] = 'field_speaker_target_id';
  $handler->display->display_options['filters']['field_speaker_target_id']['table'] = 'field_data_field_speaker';
  $handler->display->display_options['filters']['field_speaker_target_id']['field'] = 'field_speaker_target_id';
  $handler->display->display_options['filters']['field_speaker_target_id']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_speaker_target_id']['expose']['operator_id'] = 'field_speaker_target_id_op';
  $handler->display->display_options['filters']['field_speaker_target_id']['expose']['label'] = 'Speaker';
  $handler->display->display_options['filters']['field_speaker_target_id']['expose']['operator'] = 'field_speaker_target_id_op';
  $handler->display->display_options['filters']['field_speaker_target_id']['expose']['identifier'] = 'field_speaker_target_id';
  $handler->display->display_options['filters']['field_speaker_target_id']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['field_speaker_target_id']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  $handler->display->display_options['filters']['field_speaker_target_id']['group_info']['label'] = 'Speaker (field_speaker)';
  $handler->display->display_options['filters']['field_speaker_target_id']['group_info']['identifier'] = 'field_speaker_target_id';
  $handler->display->display_options['filters']['field_speaker_target_id']['group_info']['remember'] = FALSE;
  $handler->display->display_options['filters']['field_speaker_target_id']['group_info']['group_items'] = array(
    1 => array(),
    2 => array(),
    3 => array(),
  );
  /* Filter criterion: Content: Topics (field_sermon_topics) */
  $handler->display->display_options['filters']['field_sermon_topics_tid']['id'] = 'field_sermon_topics_tid';
  $handler->display->display_options['filters']['field_sermon_topics_tid']['table'] = 'field_data_field_sermon_topics';
  $handler->display->display_options['filters']['field_sermon_topics_tid']['field'] = 'field_sermon_topics_tid';
  $handler->display->display_options['filters']['field_sermon_topics_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_sermon_topics_tid']['expose']['operator_id'] = 'field_sermon_topics_tid_op';
  $handler->display->display_options['filters']['field_sermon_topics_tid']['expose']['label'] = 'Topics';
  $handler->display->display_options['filters']['field_sermon_topics_tid']['expose']['operator'] = 'field_sermon_topics_tid_op';
  $handler->display->display_options['filters']['field_sermon_topics_tid']['expose']['identifier'] = 'field_sermon_topics_tid';
  $handler->display->display_options['filters']['field_sermon_topics_tid']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['field_sermon_topics_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  $handler->display->display_options['filters']['field_sermon_topics_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_sermon_topics_tid']['vocabulary'] = 'sermon_topics';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->display->display_options['path'] = 'resources/sermons';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Sermons';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'main-menu';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $export['sermons'] = $view;

  return $export;
}
