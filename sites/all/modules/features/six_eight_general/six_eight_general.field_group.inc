<?php
/**
 * @file
 * six_eight_general.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function six_eight_general_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_front_page|node|blog|form';
  $field_group->group_name = 'group_front_page';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'blog';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Front Page',
    'weight' => '35',
    'children' => array(
      0 => 'field_front_blocks',
      1 => 'field_front_block_image',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-front-page field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_front_page|node|blog|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_front_page|node|event|form';
  $field_group->group_name = 'group_front_page';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'event';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Front Page',
    'weight' => '10',
    'children' => array(
      0 => 'field_front_ad_image',
      1 => 'field_front_ad',
      2 => 'field_front_ad_link',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-front-page field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_front_page|node|event|form'] = $field_group;

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
      0 => 'field_sermon_image',
      1 => 'field_sermon_audio',
      2 => 'field_sermon_slides',
      3 => 'field_sermon_text',
      4 => 'field_sermon_activity',
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
  $export['group_sermon_files|node|sermon|form'] = $field_group;

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
      1 => 'field_speaker',
      2 => 'field_sermon_scripture_passage',
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
  $export['group_sermon_info|node|sermon|form'] = $field_group;

  return $export;
}
