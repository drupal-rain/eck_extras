<?php

/**
 * @file
 * ctools arguments plugin: eck_name.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t("Entity: ECK Name"),
  'description' => t('Creates an entity context from an eck name property_behavior argument.'),
  'context' => 'eck_extras_arguments_eck_name_context',
  'get child' => 'eck_extras_arguments_eck_name_get_child',
  'get children' => 'eck_extras_arguments_eck_name_get_children',
);

function eck_extras_arguments_eck_name_get_child($plugin, $parent, $child) {
  $plugins = eck_extras_arguments_eck_name_get_children($plugin, $parent);
  return $plugins[$parent . ':' . $child];
}

/**
 * Make available all the eck entity types that have name property behavior.
 */
function eck_extras_arguments_eck_name_get_children($original_plugin, $parent) {
  $eck_entity_types = eck_extras_get_entity_types();
  $plugins = array();
  foreach ($eck_entity_types as $eck_entity_type => $eck_bundles) {
    // Only deal with entity that has name property_behavior.
    if (!eck_extras_entity_check_property_behavior($eck_entity_type, 'name')) {
      continue;
    }
    $plugin = $original_plugin;
    $entity_info = entity_get_info($eck_entity_type);
    $plugin['title'] = t('@entity: ECK Name', array('@entity' => $entity_info['label']));
    $plugin['keyword'] = $eck_entity_type;
    $plugin['description'] = t('Creates @entity context from an ECK Name argument.', array('@entity' => $eck_entity_type));
    $plugin['name'] = $parent . ':' . $eck_entity_type;
    $plugin_id = $parent . ':' . $eck_entity_type;
    $plugins[$plugin_id] = $plugin;
  }

  return $plugins;
}

function eck_extras_arguments_eck_name_context($arg = NULL, $conf = NULL, $empty = FALSE) {
  $eck_entity_type = explode(':', $conf['name']);
  $eck_entity_type = $eck_entity_type[1];
  // If unset it wants a generic, unfilled context.
  if ($empty) {
    return ctools_context_create_empty('entity:' . $eck_entity_type);
  }

  // We can accept either an entity object or a pure id.
  if (is_object($arg)) {
    return ctools_context_create('entity:' . $eck_entity_type, $arg);
  }

  // @todo A better solution?
  $name = str_replace('-', '_', $arg);
  $entity = eck_extras_load_by_name($eck_entity_type, $name);
  if (!$entity) {
    return FALSE;
  }

  return ctools_context_create('entity:' . $eck_entity_type, $entity);
}

