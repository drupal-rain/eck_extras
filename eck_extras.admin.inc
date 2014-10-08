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
  $eck_bundle_obj = $form['bundle']['#value'];

  // Bundle Label
  $form['bundle_label'] = array(
    '#type' => 'textfield',
    '#title' => t('Bundle Label for \'@name\'', array('@name' => $eck_bundle_obj->name)),
    '#description' => t('Change the bundle label.'),
    '#default_value' => $eck_bundle_obj->label,
    '#weight' => -100,
  );

  // title.
  $has_title = eck_extras_entity_check_property_behavior($eck_entity_type, 'title');
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
  $has_published = eck_extras_entity_check_property_behavior($eck_entity_type, 'published');
  if ($has_published) {
    $form['published'] = array(
      '#type' => 'checkbox',
      '#title' => t('Default as published'),
      '#description' => t('Set the entity to published as default.'),
      '#default_value' => isset($options['published']) ? $options['published'] : FALSE,
      '#weight' => 20,
    );
  }
  if (!isset($form['published'])) {
    $form['published'] = array(
      '#type' => 'value',
      '#value' => TRUE,
    );
  }

  // Add submit handler
  $form['#submit'][] = 'eck_extras_bundle_edit_form_submit';

  return $form;
}

/**
 * Submit for eck_extras_bundle_edit_form().
 */
function eck_extras_bundle_edit_form_submit($form, &$form_state) {
  $eck_bundle_obj = $form['bundle']['#value'];
  $options_old = $eck_bundle_obj->config;

  // Bundle Label
  if (!empty($form_state['values']['bundle_label'])) {
    $eck_bundle_obj->label = $form_state['values']['bundle_label'];
  }

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
  $eck_bundle_obj->config = array_merge($options_old, $options);
  $eck_bundle_obj->save();
}
