<?php

/**
 * @file
 * Text area property_behavior plugin for eck.
 */

$plugin = array(
  'label' => t('Text area'),
  'default_widget' => 'eck_extras_textarea_property_default_widget',
  'default_formatter' => 'eck_extras_textarea_property_default_formatter',
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
  return array(
    '#markup' => strip_tags($entity->{$property}),
  );
}
