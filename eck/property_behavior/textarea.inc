<?php

/**
 * @file
 * Text area property_behavior plugin for eck.
 */

$plugin = array(
  'label' => t('Text area'),
  'default_widget' => 'eck_extras_textarea_property_default_widget',
  'default_formatter' => 'eck_extras_textarea_property_default_formatter',
  'bundle_form' => 'eck_extras_textarea_property_bundle_form',
);

function eck_extras_textarea_property_default_widget($property, $vars) {
  $entity = $vars['entity'];
  return array(
    '#type' => 'textarea',
    '#title' => t('@title', array('@title' => $vars['properties'][$property]['label'])),
    '#default_value' => isset($entity->{$property}) ? $entity->{$property} : '',
  );
}

function eck_extras_textarea_property_default_formatter($property, $vars) {
  $entity = $vars['entity'];
  $config = eck_extras_get_bundle_config($entity->entityType(), $entity->type, $property);

  return array(
    '#markup' => check_markup($entity->{$property}, $config['text_format']),
  );
}

function eck_extras_textarea_property_bundle_form($property, $vars) {
  $form = &$vars['form'];
  $config = $vars['form']['bundle']['#value']->config;
  $eck_entity_type = $vars['form']['entity_type']['#value'];

  $name = 'config_' . $property;
  $form[$name] = array(
    '#type' => 'fieldset',
    '#title' => t('@property Settings', array('@property' => $property)),
    '#collapsible' => TRUE,
    '#tree' => TRUE,
  );
  $form[$name]['text_format'] = array(
    '#type' => 'select',
    '#title' => t('Text format'),
    '#description' => t('Text format for @property', array('@property' => $property)),
    '#options' => KtoolsListOptions::filterFormats(),
    '#default_value' => KtoolsArray::defaultValue($config, array($property, 'text_format'), filter_default_format()),
  );

  //$form['#submit'][] = 'eck_extras_textarea_property_bundle_form_submit';

  return $vars;
}

function eck_extras_textarea_property_bundle_form_submit($form, &$form_state) {
  // dsm($form_state);
}
