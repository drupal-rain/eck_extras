<?php

/**
 * @file
 * published property_behavior plugin for eck.
 */

$plugin = array(
  'label' => t('Published'),
  'default_widget' => 'eck_extras_published_property_default_widget',
  'entity_view' => 'eck_extras_published_property_entity_view',
);

/**
 * Implements 'default_widget'.
 */
function eck_extras_published_property_default_widget($property, $vars) {
  $entity = $vars['entity'];

  if (isset($entity->is_new) && $entity->is_new) {
    $options = bundle::loadByMachineName("{$entity->entityType()}_{$entity->bundle()}")->config;
    $published = (int) $options['published'];
  }
  else {
    $published = isset($entity->{$property}) ? $entity->{$property} : 0;
  }

  return array(
    '#type' => 'checkbox',
    '#title' => $vars['properties'][$property]['label'],
    '#default_value' => $published,
  );
}

/**
 * Implements 'entity_view'.
 */
function eck_extras_published_property_entity_view($property, $vars) {
  $entity = $vars['entity'];
  if ($entity->{$property} == ECK_PUBLISHED_NO) {
    $entity->title .= ' (Unpublished)';
    drupal_set_title($entity->title);
    if (!user_access('eck administer ' . $entity->entityType() . ' ' . $entity->bundle() . ' entities')) {
      drupal_access_denied();
      drupal_exit();
    }
  }
}
