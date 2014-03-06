<?php

/**
 * @file
 * USIN property behavior for eck, Unique Standard Identification Number.
 */

$plugin = array(
	'label' => t('USIN'),
  'unique' => TRUE,
  'entity_info' => 'eck_extras_usin_property_entity_info',
  'entity_save' => 'eck_extras_usin_property_entity_save',
  'default_formatter' => 'eck_extras_usin_property_default_formatter',
  'bundle_form' => 'eck_extras_usin_property_bundle_form',
);

function eck_extras_usin_property_entity_info($property, $vars) {
  $info = $vars;

  $info['entity keys']['name'] = $property;

  return $info;
}

function eck_extras_usin_property_entity_save($property, $vars) {
  $entity = $vars['entity'];
  if(isset($entity->is_new) && $entity->is_new && empty($entity->{$property})){
    $bundle_config = eck_extras_get_bundle_config($entity->entityType(), $entity->type);
    $entity->{$property} = ktools_string_random($bundle_config['usin']['source'], $bundle_config['usin']['length']);
  }
}

function eck_extras_usin_property_default_formatter($property, $vars) {
  $entity = $vars['entity'];
  return array(
      '#markup' => strip_tags($entity->{$property}),
  );
}

function eck_extras_usin_property_bundle_form($property, $vars) {
  $form = &$vars['form'];
  $config = $vars['form']['bundle']['#value']->config;

  $form['config_usin'] = array(
  	'#type' => 'fieldset',
    '#title' => t('USIN Property'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#tree' => TRUE,
    '#weight' => 10,
  );
  $form['config_usin']['source'] = array(
  	'#title' => t('USIN Property Source'),
    '#description' => t('Enter the allowed characters for generating USIN.'),
    '#type' => 'textfield',
    '#size' => 128,
    '#default_value' => isset($config['usin']['source']) ? $config['usin']['source'] : '0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ',
    '#weight' => 0,
  );
  $form['config_usin']['length'] = array(
    '#title' => t('USIN Property Length'),
    '#description' => t('Enter the length of the generated USIN.'),
    '#type' => 'textfield',
    '#size' => 10,
    '#default_value' => isset($config['usin']['length']) ? $config['usin']['length'] : '10',
    '#weight' => 10,
  );

  return $vars;
}
