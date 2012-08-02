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
    '#disabled' => !module_exists('pathauto'),
    '#weight' => 2,
  );
  $form['eck_path']['eck_path_auto'] = array(
    '#type' => 'checkbox',
    '#title' => t('Turn On'),
    '#description' => t('Whether turn on this feature for this bundle.'),
    '#default_value' => isset($options['eck_path']['on']) ? $options['eck_path']['on'] : FALSE,
    '#weight' => 0,
  );
  $form['eck_path']['eck_path_auto_pattern'] = array(
    '#type' => 'textfield',
    '#size' => 60,
    '#title' => t('Pattern'),
    '#description' => t('Configure the path alias pattern.'),
    '#default_value' => isset($options['eck_path']['pattern']) ? $options['eck_path']['pattern'] : '',
    '#weight' => 2,
  );
  $form['eck_path']['eck_path_replacement'] = array(
    '#type' => 'fieldset',
    '#title' => t('Path Token Replacement'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => theme('token_tree',
      array(
        'token_types' => array($eck_entity_type),
      )
    ),
    '#weight' => 5,
  );
  $form['eck_path']['eck_path_classic'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use [entity_type]/[id]'),
    '#description' => t('Use classic path pattern [entity_type]/[id], use menu_alter, may take a while to rebuild the menu.'),
    '#default_value' => isset($options['eck_path']['classic']) ? $options['eck_path']['classic'] : FALSE,
    '#weight' => 10,
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
        '#weight' => 5,
      );
    }
  }
  
  $form['options'] = array(
    '#type' => 'value',
    '#value' => $options,
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
  $options_old = $form_state['values']['options'];
  // Structure of the bundle configuration.
  $options = array(
    'title' => $form_state['values']['title'],
    'eck_path' => array(
      'auto' => (bool) $form_state['values']['eck_path_auto'],
      'pattern' => $form_state['values']['eck_path_auto_pattern'],
      'classic' => (bool) $form_state['values']['eck_path_classic'],
    ),
    'published' => (bool) $form_state['values']['published'],
  );
  // If eck_path_classic change state, clear menu cache, as it use menu_alter.
  // @see eck_extras_entity_info_alter().
  if (
    !isset($options_old)
    || (isset($options_old) && $options_old['eck_path']['classic'] != $options['eck_path']['classic'])
  ) {
    entity_info_cache_clear();
    menu_rebuild();
  }

  variable_set("eck_{$form_state['eck_entity_type']}_{$form_state['eck_bundle']}_options", $options);
}
