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
    'label' => 'Front Page Blocks',
    'weight' => '6',
    'children' => array(
      0 => 'field_front_blocks',
      1 => 'field_front_block_image',
      2 => 'field_front_block_duration',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Front Page Blocks',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-front-page field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsible',
    ),
  );
  $export['group_front_page|node|blog|form'] = $field_group;

  return $export;
}
