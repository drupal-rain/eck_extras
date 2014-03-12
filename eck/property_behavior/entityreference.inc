<?php

/**
 * @file
 * Entityreference property_behavior plugin for eck.
 */

$plugin = array(
  'label' => t('Entity reference'),
  'default_widget' => 'eck_extras_entityreference_property_default_widget',
  'default_formatter' => 'eck_extras_entityreference_property_default_formatter',
  'bundle_form' => 'eck_extras_entityreference_property_bundle_form',
  // 'property_info'
);

function eck_extras_entityreference_property_default_widget($property, $vars) {
  $entity = $vars['entity'];
  $config = eck_extras_entity_get_bundle_config($entity);
  $config_key = 'entityreference_' . $property;

  return array(
  	'#type' => 'entityreference',
    '#title' => t('@label', array('@label' => $vars['properties'][$property]['label'])),
    '#era_entity_type' => isset($config[$config_key]['entity_type']) ? $config[$config_key]['entity_type'] : '',
    // '#ear_bundles' => array(),
    // '#ear_cardinality' => 1,
  );
}

function eck_extras_entityreference_property_default_formatter($property, $vars) {

}

function eck_extras_entityreference_property_bundle_form($property, $vars) {
  // @todo Bundles options
  $form = &$vars['form'];
  $eck_entity_type = $form['entity_type']['#value'];
  $eck_bundle = $form['bundle']['#value'];
  $config = $eck_bundle->config;

  $form['entityreference'] = array(
    '#title' => t('Entity reference'),
    '#type' => 'fieldset',
  );
  // Each entityreference property get a separate settings
  foreach ($eck_entity_type->properties as $name => $property) {
    if ($property['behavior'] == 'entityreference') {
      $container = 'config_entityreference_' . $name;
      $config_key = 'entityreference_' . $name;
      $form['entityreference'][$container] = array(
        '#type' => 'fieldset',
        '#title' => t('@label', array('@label' => $property['label'])),
        '#collapsible' => TRUE,
        '#collapsed' => FALSE,
        '#tree' => TRUE,
      );
      $form['entityreference'][$container]['entity_type'] = array(
      	'#type' => 'select',
        '#title' => t('Entity type'),
        '#options' => eck_extras_entity_type_options(),
        '#default_value' => isset($config[$config_key]['entity_type']) ? $config[$config_key]['entity_type'] : '',
      );
    }
  }

  return $vars;
}
