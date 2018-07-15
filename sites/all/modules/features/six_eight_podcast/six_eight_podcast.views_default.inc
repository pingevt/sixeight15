<?php
/**
 * @file
 * six_eight_podcast.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function six_eight_podcast_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'podcast_feed';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Podcast Feed';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Content: Audio (field_sermon_audio:fid) */
  $handler->display->display_options['relationships']['field_sermon_audio_fid']['id'] = 'field_sermon_audio_fid';
  $handler->display->display_options['relationships']['field_sermon_audio_fid']['table'] = 'field_data_field_sermon_audio';
  $handler->display->display_options['relationships']['field_sermon_audio_fid']['field'] = 'field_sermon_audio_fid';
  $handler->display->display_options['relationships']['field_sermon_audio_fid']['required'] = TRUE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = TRUE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Content: Description */
  $handler->display->display_options['fields']['field_sermon_description']['id'] = 'field_sermon_description';
  $handler->display->display_options['fields']['field_sermon_description']['table'] = 'field_data_field_sermon_description';
  $handler->display->display_options['fields']['field_sermon_description']['field'] = 'field_sermon_description';
  $handler->display->display_options['fields']['field_sermon_description']['label'] = '';
  $handler->display->display_options['fields']['field_sermon_description']['alter']['trim_whitespace'] = TRUE;
  $handler->display->display_options['fields']['field_sermon_description']['alter']['strip_tags'] = TRUE;
  $handler->display->display_options['fields']['field_sermon_description']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_sermon_description']['type'] = 'text_plain';
  /* Field: Content: Path */
  $handler->display->display_options['fields']['path']['id'] = 'path';
  $handler->display->display_options['fields']['path']['table'] = 'node';
  $handler->display->display_options['fields']['path']['field'] = 'path';
  $handler->display->display_options['fields']['path']['label'] = '';
  $handler->display->display_options['fields']['path']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['path']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['path']['absolute'] = TRUE;
  /* Field: Content: Audio (enclosure) */
  $handler->display->display_options['fields']['field_sermon_audio']['id'] = 'field_sermon_audio';
  $handler->display->display_options['fields']['field_sermon_audio']['table'] = 'field_data_field_sermon_audio';
  $handler->display->display_options['fields']['field_sermon_audio']['field'] = 'field_sermon_audio';
  $handler->display->display_options['fields']['field_sermon_audio']['ui_name'] = 'Content: Audio (enclosure)';
  $handler->display->display_options['fields']['field_sermon_audio']['label'] = '';
  $handler->display->display_options['fields']['field_sermon_audio']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_sermon_audio']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_sermon_audio']['type'] = 'enclosure';
  /* Field: Content: Audio (duration) */
  $handler->display->display_options['fields']['field_sermon_audio_1']['id'] = 'field_sermon_audio_1';
  $handler->display->display_options['fields']['field_sermon_audio_1']['table'] = 'field_data_field_sermon_audio';
  $handler->display->display_options['fields']['field_sermon_audio_1']['field'] = 'field_sermon_audio';
  $handler->display->display_options['fields']['field_sermon_audio_1']['ui_name'] = 'Content: Audio (duration)';
  $handler->display->display_options['fields']['field_sermon_audio_1']['label'] = '';
  $handler->display->display_options['fields']['field_sermon_audio_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_sermon_audio_1']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_sermon_audio_1']['type'] = 'itunes:duration';
  /* Field: Content: Audio (guid) */
  $handler->display->display_options['fields']['field_sermon_audio_2']['id'] = 'field_sermon_audio_2';
  $handler->display->display_options['fields']['field_sermon_audio_2']['table'] = 'field_data_field_sermon_audio';
  $handler->display->display_options['fields']['field_sermon_audio_2']['field'] = 'field_sermon_audio';
  $handler->display->display_options['fields']['field_sermon_audio_2']['ui_name'] = 'Content: Audio (guid)';
  $handler->display->display_options['fields']['field_sermon_audio_2']['label'] = '';
  $handler->display->display_options['fields']['field_sermon_audio_2']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_sermon_audio_2']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_sermon_audio_2']['type'] = 'file_url_plain';
  /* Field: Content: Image */
  $handler->display->display_options['fields']['field_sermon_image']['id'] = 'field_sermon_image';
  $handler->display->display_options['fields']['field_sermon_image']['table'] = 'field_data_field_sermon_image';
  $handler->display->display_options['fields']['field_sermon_image']['field'] = 'field_sermon_image';
  $handler->display->display_options['fields']['field_sermon_image']['label'] = '';
  $handler->display->display_options['fields']['field_sermon_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_sermon_image']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_sermon_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_sermon_image']['type'] = 'image_url';
  $handler->display->display_options['fields']['field_sermon_image']['settings'] = array(
    'url_type' => '0',
    'image_style' => 'rss_images',
    'image_link' => '',
  );
  /* Field: Content: Speaker */
  $handler->display->display_options['fields']['field_speaker']['id'] = 'field_speaker';
  $handler->display->display_options['fields']['field_speaker']['table'] = 'field_data_field_speaker';
  $handler->display->display_options['fields']['field_speaker']['field'] = 'field_speaker';
  $handler->display->display_options['fields']['field_speaker']['label'] = '';
  $handler->display->display_options['fields']['field_speaker']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_speaker']['settings'] = array(
    'bypass_access' => 0,
    'link' => 0,
  );
  /* Field: Content: Date */
  $handler->display->display_options['fields']['field_sermon_date']['id'] = 'field_sermon_date';
  $handler->display->display_options['fields']['field_sermon_date']['table'] = 'field_data_field_sermon_date';
  $handler->display->display_options['fields']['field_sermon_date']['field'] = 'field_sermon_date';
  $handler->display->display_options['fields']['field_sermon_date']['label'] = '';
  $handler->display->display_options['fields']['field_sermon_date']['alter']['trim_whitespace'] = TRUE;
  $handler->display->display_options['fields']['field_sermon_date']['alter']['strip_tags'] = TRUE;
  $handler->display->display_options['fields']['field_sermon_date']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_sermon_date']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_sermon_date']['settings'] = array(
    'format_type' => 'rfc_822',
    'custom_date_format' => '',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_remaining_days' => 0,
  );
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
    'sermon' => 'sermon',
  );

  /* Display: Feed */
  $handler = $view->new_display('feed', 'Feed', 'feed_1');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '52';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'rss_fields';
  $handler->display->display_options['style_options']['channel'] = array(
    'core' => array(
      'views_rss_core' => array(
        'description' => 'Sermons from Six:Eight Vineyard Church',
        'language' => 'en-US',
        'category' => '',
        'image' => '',
        'copyright' => '',
        'managingEditor' => '',
        'webMaster' => '',
        'generator' => '',
        'docs' => '',
        'cloud' => '',
        'ttl' => '',
        'skipHours' => '',
        'skipDays' => '',
      ),
    ),
    'itunes' => array(
      'views_rss_itunes' => array(
        'subtitle' => 'Sermons from Six:Eight Vineyard Church',
        'summary' => 'Sermons from Six:Eight Vineyard Church',
        'category' => array(
          1012 => '1012',
        ),
        'keywords' => '',
        'image' => '',
        'author' => '',
        'explicit' => 'no',
        'block' => '',
        'complete' => '',
        'new-feed-url' => '',
        'owner' => '',
      ),
    ),
  );
  $handler->display->display_options['style_options']['item'] = array(
    'core' => array(
      'views_rss_core' => array(
        'title' => 'title',
        'link' => 'path',
        'description' => 'field_sermon_description',
        'author' => '',
        'category' => '',
        'comments' => '',
        'enclosure' => 'field_sermon_audio',
        'guid' => 'field_sermon_audio_2',
        'pubDate' => 'field_sermon_date',
      ),
    ),
    'itunes' => array(
      'views_rss_itunes' => array(
        'subtitle' => 'field_sermon_description',
        'summary' => 'field_sermon_description',
        'duration' => 'field_sermon_audio_1',
        'keywords' => '',
        'image' => 'field_sermon_image',
        'author' => 'field_speaker',
        'isClosedCaptioned' => '',
        'explicit' => '',
        'block' => '',
        'order' => '',
      ),
    ),
  );
  $handler->display->display_options['style_options']['feed_settings'] = array(
    'absolute_paths' => 1,
    'feed_in_links' => 0,
  );
  $handler->display->display_options['path'] = 'podcast.rss';
  $export['podcast_feed'] = $view;

  return $export;
}
