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
  $has_title = eck_extras_entity_check_property_behavior($eck_entity_type, 'title');
  // title.
  if ($has_title) {
    $form['title'] = array(
      '#type' => 'fieldset',
      '#title' => t('Title'),
      '#tree' => TRUE,
      '#collapsible' => TRUE,
      '#weight' => 0,
    );
    $form['title']['pattern'] = array(
      '#type' => 'textfield',
      '#size' => 60,
      '#title' => t('Title Pattern'),
      '#description' => t('Configure the title display for the entities of this bundle.'),
      '#default_value' => isset($options['title']) ? $options['title'] : '',
      '#weight' => 0,
    );

    $form['title']['token'] = array(
      '#type' => 'fieldset',
      '#title' => t('Token Replacement'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#description' => theme('token_tree',
        array(
          'token_types' => array($eck_entity_type),
        )
      ),
      '#weight' => 1,
    );
  }
  // eck_path.
  if (module_exists('path')) {
    $form['eck_path'] = array(
      '#type'        => 'fieldset',
      '#title'       => t('Auto Path Alias'),
      '#description' => t('Configure the auto path alias for the entities of this bundle. Require pathauto module.'),
      '#tree'        => TRUE,
      '#collapsible' => TRUE,
      '#collapsed'   => !module_exists('pathauto'),
      '#weight'      => 10,
    );
    $form['eck_path']['auto'] = array(
      '#type'          => 'checkbox',
      '#title'         => t('Turn On'),
      '#description'   => t('Whether turn on this feature for this bundle.'),
      '#default_value' => isset($options['eck_path']['auto']) ? $options['eck_path']['auto'] : FALSE,
      '#disabled'      => !module_exists('pathauto'),
      '#weight'        => 0,
    );
    $form['eck_path']['auto_pattern'] = array(
      '#type'          => 'textfield',
      '#size'          => 60,
      '#title'         => t('Pattern'),
      '#description'   => t('Configure the path alias pattern.'),
      '#default_value' => isset($options['eck_path']['pattern']) ? $options['eck_path']['pattern'] : '',
      '#disabled'      => !module_exists('pathauto'),
      '#weight'        => 2,
    );
    $form['eck_path']['token'] = array(
      '#type'        => 'fieldset',
      '#title'       => t('Token Replacement'),
      '#collapsible' => TRUE,
      '#collapsed'   => TRUE,
      '#description' => theme('token_tree', array('token_types' => array($eck_entity_type))),
      '#weight'      => 5,
    );
  }
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
    'title' => $form_state['values']['title']['pattern'],
    'eck_path' => array(
      'auto' => (bool) $form_state['values']['eck_path']['auto'],
      'pattern' => $form_state['values']['eck_path']['auto_pattern'],
    ),
    'published' => (bool) $form_state['values']['published'],
  );
  // Save the configuration.
  $form['bundle']['#value']->config = array_merge($options_old, $options);
  $form['bundle']['#value']->save();
}
