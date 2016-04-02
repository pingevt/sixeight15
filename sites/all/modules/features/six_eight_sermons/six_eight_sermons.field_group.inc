<?php
/**
 * @file
 * six_eight_sermons.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function six_eight_sermons_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_front_page_ad2|node|sermon|form';
  $field_group->group_name = 'group_front_page_ad2';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'sermon';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Front Page Ad',
    'weight' => '7',
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
        'classes' => 'group-front-page-ad2 field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_front_page_ad2|node|sermon|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_front_page_ad_3|node|sermon_series|form';
  $field_group->group_name = 'group_front_page_ad_3';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'sermon_series';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Front Page Ad',
    'weight' => '4',
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
        'classes' => 'group-front-page-ad-3 field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_front_page_ad_3|node|sermon_series|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_front_page_block_3|node|sermon_series|form';
  $field_group->group_name = 'group_front_page_block_3';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'sermon_series';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Front Page block',
    'weight' => '5',
    'children' => array(
      0 => 'field_front_block_duration',
      1 => 'field_front_block_image',
      2 => 'field_front_blocks',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-front-page-block-3 field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_front_page_block_3|node|sermon_series|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_frot_page_blocks|node|sermon|form';
  $field_group->group_name = 'group_frot_page_blocks';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'sermon';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Front Page Blocks',
    'weight' => '8',
    'children' => array(
      0 => 'field_front_block_duration',
      1 => 'field_front_block_image',
      2 => 'field_front_blocks',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-frot-page-blocks field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_frot_page_blocks|node|sermon|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_sermon_files|node|sermon|form';
  $field_group->group_name = 'group_sermon_files';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'sermon';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Sermon Files',
    'weight' => '6',
    'children' => array(
      0 => 'field_sermon_activity',
      1 => 'field_sermon_audio',
      2 => 'field_sermon_image',
      3 => 'field_sermon_slides',
      4 => 'field_sermon_text',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-sermon-files field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_sermon_files|node|sermon|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_sermon_info|node|sermon|form';
  $field_group->group_name = 'group_sermon_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'sermon';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Sermon Info',
    'weight' => '5',
    'children' => array(
      0 => 'field_sermon_date',
      1 => 'field_sermon_scripture_passage',
      2 => 'field_speaker',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-sermon-info field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_sermon_info|node|sermon|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Front Page Ad');
  t('Front Page Blocks');
  t('Front Page block');
  t('Sermon Files');
  t('Sermon Info');

  return $field_groups;
}
