<?php

/**
 * @file
 * URL property behavior for eck, web url link.
 */

$plugin = array(
  'label' => t('URL'),
  'default_widget' => 'eck_extras_url_property_default_widget',
  'default_formatter' => 'eck_extras_url_property_default_formatter',
);

function eck_extras_url_property_default_widget($property, $vars) {
  $entity = $vars['entity'];
  return array(
    '#title' => $vars['properties'][$property]['label'],
    '#type' => 'urlfield',
    '#default_value' => isset($entity->{$property}) ? $entity->{$property} : NULL,
  );
}

function eck_extras_url_property_default_formatter($property, $vars) {
  $entity = $vars['entity'];
  return array(
    '#markup' => strip_tags($entity->{$property}),
  );
}
