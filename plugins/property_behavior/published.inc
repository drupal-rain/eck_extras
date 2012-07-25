<?php

/**
 * @file issue_status property_behavior plugin for eck.
 */

/**
 * Define the published status.
 */
define('ECK_PUBLISHED_YES', 0x01);

/**
 * Define the non-published status.
*/
define('ECK_PUBLISHED_NO', 0x00);
 
$plugin = array(
  'label' => t('Published'),
  'default_widget' => 'eck_extras_published_property_default_widget',
  'entity_view' => 'eck_extras_published_property_entity_view',
);

function eck_extras_published_property_default_widget($property, $vars) {
  return array(
    '#type' => 'checkbox',
    '#title' => $vars['properties'][$property]['label'],
    '#default_value' => $vars['entity']->{$property},
  );
}

function eck_extras_published_property_entity_view($property, $vars) {
  $entity = $vars['entity'];
  if ($entity->{$property} == ECK_PUBLISHED_NO) {
    $entity->title .= ' (Unpublished)';
    drupal_set_title($entity->title);
    if (!user_access('eck administer ' . $entity->entityType() . ' ' . $entity->bundle() . ' entities')) {
      drupal_access_denied();
    }
  }
}
