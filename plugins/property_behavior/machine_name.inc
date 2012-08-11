<?php

/**
 * @file
 * Machine Name property_behavior plugin for eck.
 */
 
$plugin = array(
  'label' => t('Machine Name'),
  'default_widget' => 'eck_extras_machine_name_property_default_widget',
  'default_formatter' => 'eck_extras_machine_name_property_default_formatter',
);

/**
 * Implements default_widget.
 */
function eck_extras_machine_name_property_default_widget($property, $vars) {
  $entity = $vars['entity'];
  $disabled = TRUE;
  if ((!isset($entity->id) && $entity->is_new)
    || empty($entity->{$property})
  ) {
    $disabled = FALSE;
  }
  return array(
    '#type' => 'machine_name',
    '#machine_name' => array(
      'exists' => 'eck_extras_machine_name_exists',
      'source' => array('title'),
      'replace_pattern' => '[^a-z0-9_]+',
      'replace' => '_',
    ),
    '#maxlength' => 255,
    '#default_value' => isset($entity->{$property}) ? $entity->{$property} : NULL,
    '#disabled' => $disabled,
  );
}

/**
 * Implements default_formatter.
 */
function eck_extras_machine_name_property_default_formatter($property, $vars) {
  return array(
    '#markup' => strip_tags($entity->{$property}),
  );
}
