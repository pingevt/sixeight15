<?php
/**
 * @file
 * six_eight_blog.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function six_eight_blog_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_blog_front_page_block|node|blog|form';
  $field_group->group_name = 'group_blog_front_page_block';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'blog';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Front Page Blocks',
    'weight' => '6',
    'children' => array(
      0 => 'field_front_block_image',
      1 => 'field_front_blocks',
      2 => 'field_front_block_duration',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-blog-front-page-block field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_blog_front_page_block|node|blog|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_front_page_ad_4|node|blog|form';
  $field_group->group_name = 'group_front_page_ad_4';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'blog';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Front Page Ad',
    'weight' => '5',
    'children' => array(
      0 => 'field_front_ad',
      1 => 'field_front_ad_duration',
      2 => 'field_front_ad_image',
      3 => 'field_front_ad_link',
      4 => 'field_front_ad_no_link',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-front-page-ad-4 field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_front_page_ad_4|node|blog|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Front Page Ad');
  t('Front Page Blocks');

  return $field_groups;
}
