<?php

$plugin = array(
  'label' => t('Node reference'),
  'default_widget' => 'eck_extras_nodereference_property_default_widget',
  'default_formatter' => 'eck_extras_nodereference_property_default_formatter',
  'property_info' => 'eck_extras_nodereference_property_property_info',
  'pre_set' => 'eck_extras_nodereference_property_pre_set',
  'getter' => 'eck_extras_nodereference_property_getter',
  'setter' => 'eck_extras_nodereference_property_setter',
);

function eck_extras_nodereference_property_default_widget($property, $vars) {
  $entity = $vars['entity'];
  $config = eck_extras_entity_get_bundle_config($entity, $property);

  return array(
    '#type' => 'entityreference',
    '#title' => t('@label', array('@label' => $vars['properties'][$property]['label'])),
    '#era_entity_type' => 'node',
    // '#ear_bundles' => array(),
    // '#ear_cardinality' => 1,
    '#default_value' => isset($entity->{$property}) ? $entity->{$property} : 0,
  );
}

function eck_extras_nodereference_property_default_formatter($property, $vars) {
  $entity = $vars['entity'];
  $config = eck_extras_entity_get_bundle_config($entity, $property);

  return array(
    '#markup' => strip_tags($property . '(Node): ' . $entity->{$property}),
  );
}

/**
 * @see entityreference_autocomplete_validate_entityreference().
 * @see eck__entity__form_submit().
 * @see eck_property_behavior_invoke_plugin().
 */
function eck_extras_nodereference_property_pre_set($property, $vars) {
  // @issue This would be called twice because bug in eck__entity__form_submit().
  // I've forked it to fix it.

  // 'entity' type must have EntityDrauplWrapper in validate process.
  return entity_metadata_wrapper($vars['data']['entity_type'], $vars['data']['entity_id']);
}

function eck_extras_nodereference_property_property_info($property, $vars) {
  $info = $vars;
  // Predefined type to 'node'
  $info['properties'][$property]['type'] = 'node';

  return $info;
}

function eck_extras_nodereference_property_getter($property, $vars) {
  $entity = $vars['entity'];
  $config = eck_extras_entity_get_bundle_config($entity, $property);

  // Entity metadata wrapper get chain.
  return entity_metadata_wrapper('node', $entity->{$property});
}

function eck_extras_nodereference_property_setter($property, $vars) {
  $entity = $vars['entity'];
  $entity->{$property} = $vars['value'];
}
