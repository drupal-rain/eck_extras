<?php

/**
 * @file
 * Text property_behavior plugin for eck.
 */

$plugin = array(
  'label' => t('Text'),
  'default_widget' => 'eck_extras_text_property_default_widget',
  'default_formatter' => 'eck_extras_text_property_default_formatter',
);

function eck_extras_text_property_default_widget($property, $vars) {
  $entity = $vars['entity'];
  return array(
  	'#type' => 'textfield',
    '#title' => t('@title', array('@title' => $vars['properties'][$property]['label'])),
    '#size' => 60,
    '#maxlength' => 225,
    '#default_value' => isset($entity->{$property}) ? $entity->{$property} : '',
  );
}

function eck_extras_text_property_default_formatter($property, $vars) {
  $entity = $vars['entity'];
  return array(
    '#markup' => strip_tags($entity->{$property}),
  );
}
