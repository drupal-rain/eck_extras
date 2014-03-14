<?php

/**
 * @file
 * Entityreference property_behavior plugin for eck.
 *
 * @see entityreference_autocomplete_validate_entityreference().
 */

$plugin = array(
  'label' => t('Entity reference'),
  'default_widget' => 'eck_extras_entityreference_property_default_widget',
  'default_formatter' => 'eck_extras_entityreference_property_default_formatter',
  'property_info' => 'eck_extras_entityreference_property_property_info',
  'pre_set' => 'eck_extras_entityreference_property_pre_set',
  'getter' => 'eck_extras_entityreference_property_getter',
  'setter' => 'eck_extras_entityreference_property_setter',
  'bundle_form' => 'eck_extras_entityreference_property_bundle_form',
);

function eck_extras_entityreference_property_default_widget($property, $vars) {
  $entity = $vars['entity'];
  $config = eck_extras_entity_get_bundle_config($entity, $property);

  return array(
  	'#type' => 'entityreference',
    '#title' => t('@label', array('@label' => $vars['properties'][$property]['label'])),
    '#era_entity_type' => isset($config['entity_type']) ? $config['entity_type'] : '',
    // '#ear_bundles' => array(),
    // '#ear_cardinality' => 1,
    '#default_value' => isset($entity->{$property}) ? $entity->{$property} : 0,
  );
}

function eck_extras_entityreference_property_default_formatter($property, $vars) {
  $entity = $vars['entity'];
  $config = eck_extras_entity_get_bundle_config($entity, $property);

  return array(
  	'#markup' => strip_tags($property . '(' . $config['entity_type'] . '): ' . $entity->{$property}),
  );
}

/**
 * @see entityreference_autocomplete_validate_entityreference().
 * @see eck__entity__form_submit().
 * @see eck_property_behavior_invoke_plugin().
 */
function eck_extras_entityreference_property_pre_set($property, $vars) {
  // @issue This would be called twice because bug in eck__entity__form_submit().
  // I've forked it to fix it.

  // 'entity' type must have EntityDrauplWrapper in validate process.
  return entity_metadata_wrapper($vars['data']['entity_type'], $vars['data']['entity_id']);
}

function eck_extras_entityreference_property_property_info($property, $vars) {
  $info = $vars;
  // Predefined type any 'entity'
  $info['properties'][$property]['type'] = 'entity';

  return $info;
}

function eck_extras_entityreference_property_getter($property, $vars) {
  $entity = $vars['entity'];
  $config = eck_extras_entity_get_bundle_config($entity, $property);

  // Entity metadata wrapper get chain.
  return entity_metadata_wrapper($config['entity_type'], $entity->{$property});
}

function eck_extras_entityreference_property_setter($property, $vars) {
  $entity = $vars['entity'];
  // While entity metadata wrapper is just a wrapper of data, setter is setting by the data.
  //$entity->{$property} = ktools_entity_id($vars['value']);
  $entity->{$property} = KtoolsEntity::interId($vars['value']);
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
      $container = 'config_' . $name;
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
        '#default_value' => isset($config[$name]['entity_type']) ? $config[$name]['entity_type'] : '',
      );
    }
  }

  return $vars;
}
