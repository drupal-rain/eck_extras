<?php

/**
 * @file
 * Name property_behavior plugin for eck.
 */

$plugin = array(
  'label' => t('Name'),
  'unique' => TRUE,
  'entity_info' => 'eck_extras_name_property_entity_info',
  'default_widget' => 'eck_extras_name_property_default_widget',
  'default_formatter' => 'eck_extras_name_property_default_formatter',
  'bundle_form' => 'eck_extras_name_property_bundle_form',
);

/**
 * Callback for property_behavior plugin: entity_info.
 */
function eck_extras_name_property_entity_info($property, $vars) {
  $info = $vars;

  $info['entity keys']['name'] = $property;

  return $info;
}

/**
 * Callback for property_behavior plugin: default_widget.
 *
 * @todo Figure out how to get entity_type here, $entity->type only fetch the bundle name.
 */
function eck_extras_name_property_default_widget($property, $vars) {
  $entity = $vars['entity'];
  $disabled = TRUE;
  if (
    (!isset($entity->id) && $entity->is_new)
    || empty($entity->{$property})
  ) {
    $disabled = FALSE;
  }
  return array(
    '#type' => 'machine_name',
    '#machine_name' => array(
      'exists' => 'eck_extras_name_exists',
      'source' => array(eck_extras_get_bundle_config($entity->entityType(), $entity->type, 'name_source')),
      'replace_pattern' => '[^a-z0-9_]+',
      'replace' => '_',
    ),
    '#maxlength' => 255,
    '#default_value' => isset($entity->{$property}) ? $entity->{$property} : NULL,
    '#disabled' => $disabled,
  );
}

/**
 * Callback for property_behavior plugin: default_formatter.
 */
function eck_extras_name_property_default_formatter($property, $vars) {
  $entity = $vars['entity'];
  return array(
      '#markup' => strip_tags($entity->{$property}),
  );
}

function eck_extras_name_property_bundle_form($property, $vars) {
  $form = &$vars['form'];
  $eck_entity_type = $form['entity_type']['#value'];
  $config = $form['bundle']['#value']->config;

  // name property.
  $form['config_name_source'] = array(
    '#title' => t('Name Property Source'),
    '#description' => t('Select the name property source.'),
    '#type' => 'select',
    '#options' => eck_extras_name_source_options($eck_entity_type->name),
    '#default_value' => isset($config['name_source']) ? $config['name_source'] : '',
    '#weight' => 5,
  );

  return $vars;
}
