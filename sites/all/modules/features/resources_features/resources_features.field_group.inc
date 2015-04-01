<?php
/**
 * @file
 * resources_features.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function resources_features_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_front_page_ad|node|resource|form';
  $field_group->group_name = 'group_front_page_ad';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'resource';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Front Page Ad',
    'weight' => '10',
    'children' => array(
      0 => 'field_front_ad',
      1 => 'field_front_ad_image',
      2 => 'field_front_ad_link',
      3 => 'field_front_ad_duration',
      4 => 'field_front_ad_no_link',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-front-page-ad field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_front_page_ad|node|resource|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_front_page_block_1|node|resource|form';
  $field_group->group_name = 'group_front_page_block_1';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'resource';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Front Page block',
    'weight' => '11',
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
        'classes' => 'group-front-page-block-1 field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_front_page_block_1|node|resource|form'] = $field_group;

  return $export;
}
