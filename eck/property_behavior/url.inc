<?php

/**
 * @file
 * URL property behavior for eck, web url link.
 *
 * @todo Think out 'attributes' storage.
 * @todo Fetch title
 */

$plugin = array(
  'label' => t('URL'),
  'entity_save' => 'eck_extras_url_property_entity_save',
  'default_widget' => 'eck_extras_url_property_default_widget',
  'default_formatter' => 'eck_extras_url_property_default_formatter',
  'bundle_form' => 'eck_extras_url_property_bundle_form',
);

function eck_extras_url_property_entity_save($property, $vars) {
  $entity = $vars['entity'];
  if(!empty($entity->{$property}) && empty($entity->title)){
    $bundle_config = eck_extras_get_bundle_config($entity->entityType(), $entity->type);
    if (isset($bundle_config['url_fetch_title']) && $bundle_config['url_fetch_title']) {
      $entity->title = eck_extras_url_fetch_title($entity->{$property});
    }
  }
}

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
    '#type' => 'link',
    '#title' => isset($entity->title) ? $entity->title : $entity->{$property},
    '#href' => $entity->{$property},
    // @todo '#options'
  );
}

function eck_extras_url_property_bundle_form($property, $vars) {
  $form = &$vars['form'];
  $config = $vars['form']['bundle']['#value']->config;
  $eck_entity_type_obj = $vars['form']['entity_type']['#value'];

  // Only show if there is 'title' property behavior.
  $form['url'] = array(
    '#title' => t('URL'),
  	'#type' => 'fieldset',
  );
  if (eck_extras_entity_get_properties($eck_entity_type_obj, 'title')) {
    $form['url']['config_url_fetch_title'] = array(
      '#title' => t('Fetch Title'),
      '#description' => t('Try fetch title if title property left empty.'),
      '#type' => 'checkbox',
      '#default_value' => isset($config['url_fetch_title']) ? $config['url_fetch_title'] : FALSE,
    );
  }

  return $vars;
}
