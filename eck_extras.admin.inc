<?php

/**
 * @file
 * Admin configuration form of eck_extras.
 */

/**
 * Form for setting bundle options.
 */
function eck_extras_bundle_edit_form($form, &$form_state, $eck_entity_type, $eck_bundle) {
  $form_state['eck_entity_type'] = $eck_entity_type;
  $form_state['eck_bundle'] = $eck_bundle;
  $options = $form['bundle']['#value']->config;
  // title.
  $form['title'] = array(
    '#type' => 'textfield',
    '#size' => 60,
    '#title' => t('Title'),
    '#description' => t('Configure the title display for the entities of this bundle.'),
    '#default_value' => isset($options['title']) ? $options['title'] : '',
    '#weight' => 0,
  );
  $form['title_replacement'] = array(
    '#type' => 'fieldset',
    '#title' => t('Title Token Replacement'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => theme('token_tree',
      array(
        'token_types' => array($eck_entity_type),
      )
    ),
    '#weight' => 1,
  );
  // eck_path.
  $form['eck_path'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => !module_exists('pathauto'),
    '#title' => t('Auto Path Alias'),
    '#description' => t('Configure the auto path alias for the entities of this bundle. Require pathauto module.'),
    '#weight' => 10,
  );
  $form['eck_path']['eck_path_auto'] = array(
    '#type' => 'checkbox',
    '#title' => t('Turn On'),
    '#description' => t('Whether turn on this feature for this bundle.'),
    '#default_value' => isset($options['eck_path']['auto']) ? $options['eck_path']['auto'] : FALSE,
    '#disabled' => !module_exists('pathauto'),
    '#weight' => 0,
  );
  $form['eck_path']['eck_path_auto_pattern'] = array(
    '#type' => 'textfield',
    '#size' => 60,
    '#title' => t('Pattern'),
    '#description' => t('Configure the path alias pattern.'),
    '#default_value' => isset($options['eck_path']['pattern']) ? $options['eck_path']['pattern'] : '',
    '#disabled' => !module_exists('pathauto'),
    '#weight' => 2,
  );
  $form['eck_path']['eck_path_replacement'] = array(
    '#type' => 'fieldset',
    '#title' => t('Path Token Replacement'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => theme('token_tree', array('token_types' => array($eck_entity_type))),
    '#weight' => 5,
  );
  // published.
  $properties = EntityType::loadByName($eck_entity_type)->properties;
  foreach ($properties as $property_name => $property_info) {
    if ($property_info['behavior'] == 'published') {
      $form['published'] = array(
        '#type' => 'checkbox',
        '#title' => t('Default as published'),
        '#description' => t('Set the entity to published as default.'),
        '#default_value' => isset($options['published']) ? $options['published'] : FALSE,
        '#weight' => 20,
      );
    }
  }
  if (!isset($form['published'])) {
    $form['published'] = array(
      '#type' => 'value',
      '#value' => TRUE,
    );
  }

  $form['#submit'][] = 'eck_extras_bundle_edit_form_submit';

  return $form;
}

/**
 * Submit for eck_extras_bundle_edit_form().
 */
function eck_extras_bundle_edit_form_submit($form, &$form_state) {
  $options_old = $form['bundle']['#value']->config;
  // Structure of the bundle configuration.
  $options = array(
    'title' => $form_state['values']['title'],
    'eck_path' => array(
      'auto' => (bool) $form_state['values']['eck_path_auto'],
      'pattern' => $form_state['values']['eck_path_auto_pattern'],
    ),
    'published' => (bool) $form_state['values']['published'],
  );
  // Save the configuration.
  $form['bundle']['#value']->config = array_merge($options_old, $options);
  $form['bundle']['#value']->save();
}
