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
  $options = variable_get("eck_{$form_state['eck_entity_type']}_{$form_state['eck_bundle']}_options", array());
  $form['title'] = array(
    '#type' => 'textfield',
    '#size' => 60,
    '#title' => t('Title'),
    '#description' => t('Configure the title display for the entities of this bundle.'),
    '#default_value' => isset($options['title']) ? $options['title'] : '',
    '#weight' => 0,
  );
  $form['eck_path'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => !module_exists('pathauto'),
    '#title' => t('Auto Path Alias'),
    '#description' => t('Configure the auto path alias for the entities of this bundle. Require pathauto module.'),
    '#disabled' => !module_exists('pathauto'),
    '#weight' => 2,
  );
  $form['eck_path']['eck_path_auto'] = array(
    '#type' => 'checkbox',
    '#title' => t('Turn On'),
    '#description' => t('Whether turn on this feature for this bundle.'),
    '#default_value' => isset($options['eck_path']['on']) ? $options['eck_path']['on'] : FALSE,
    '#weight' => 2,
  );
  $form['eck_path']['eck_path_auto_pattern'] = array(
    '#type' => 'textfield',
    '#size' => 60,
    '#title' => t('Pattern'),
    '#description' => t('Configure the path alias pattern.'),
    '#default_value' => isset($options['eck_path']['pattern']) ? $options['eck_path']['pattern'] : '',
    '#weight' => 0,
  );
  // Replacement patterns.
  $form['token_tree'] = array(
    '#type' => 'fieldset',
    '#title' => t('Replacement patterns'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => theme('token_tree',
      array(
        'token_types' => array($eck_entity_type),
      )
    ),
    '#weight' => 5,
  );
  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
    '#weight' => 100,
  );
  
  return $form;
}

/**
 * Submit for eck_extras_bundle_edit_form().
 */
function eck_extras_bundle_edit_form_submit($form, &$form_state) {
  // Structure of the bundle configuration.
  $options = array(
    'title' => $form_state['values']['title'],
    'eck_path' => array(
      'on' => (bool) $form_state['values']['eck_path_auto'],
      'pattern' => $form_state['values']['eck_path_auto_pattern'],
    ),
  );

  variable_set("eck_{$form_state['eck_entity_type']}_{$form_state['eck_bundle']}_options", $options);
}
