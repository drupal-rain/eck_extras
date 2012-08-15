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
    '#weight' => 2,
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
    '#description' => theme('token_tree', array('token_types' => array($eck_entity_type),)),
    '#weight' => 5,
  );
  $form['eck_crud'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('CRUD Paths'),
    '#description' => t('Configure the crud paths setting for this bundle.'),
    '#weight' => 5,
  );
  $form['eck_crud']['eck_crud_view'] = array(
    '#type' => 'textfield',
    '#size' => 60,
    '#title' => t('Entity View Path'),
    '#description' => t("Use '%' for the entity id placeholder. e.g. ENTITY_TYPE/BUNDLE/%"),
    '#default_value' => isset($options['eck_crud']['view']) ? $options['eck_crud']['view'] : '',
    '#weight' => 0,
  );
  $form['eck_crud']['eck_crud_add'] = array(
    '#type' => 'textfield',
    '#size' => 60,
    '#title' => t('Entity Add Path'),
    '#description' => t('e.g. ENTITY_TYPE/BUNDLE/add'),
    '#default_value' => isset($options['eck_crud']['add']) ? $options['eck_crud']['add'] : '',
    '#weight' => 1,
  );
  $form['eck_crud']['eck_crud_edit'] = array(
    '#type' => 'textfield',
    '#size' => 60,
    '#title' => t('Entity Edit Path'),
    '#description' => t("Use '%' for the entity id placeholder. e.g. ENTITY_TYPE/BUNDLE/%/edit"),
    '#default_value' => isset($options['eck_crud']['edit']) ? $options['eck_crud']['edit'] : '',
    '#weight' => 2,
  );
  $form['eck_crud']['eck_crud_delete'] = array(
    '#type' => 'textfield',
    '#size' => 60,
    '#title' => t('Entity Delete Path'),
    '#description' => t("Use '%' for the entity id placeholder. e.g. ENTITY_TYPE/BUNDLE/%/delete"),
    '#default_value' => isset($options['eck_crud']['delete']) ? $options['eck_crud']['delete'] : '',
    '#weight' => 3,
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
    ),
    'eck_crud' => array(
      'view' => $form_state['values']['eck_crud_view'],
      'add' => $form_state['values']['eck_crud_add'],
      'edit' => $form_state['values']['eck_crud_edit'],
      'delete' => $form_state['values']['eck_crud_delete'],
    ),
    'published' => (bool) $form_state['values']['published'],
  );
  // Save the configuration.
  variable_set("eck_{$form_state['eck_entity_type']}_{$form_state['eck_bundle']}_options", $options);
  
  // If eck_crud_* change state, clear menu cache, as it use menu_alter.
  // @see eck_extras_entity_info_alter().
  if (_eck_extras_crud_changed($options_old, $options)) {
    entity_info_cache_clear();
    menu_rebuild();
  }
}

/**
 * Helper function for checking if the eck_crud configuration is changed.
 */
function _eck_extras_crud_changed($options_old, $options_new) {
  $crud = array('view', 'add', 'edit', 'delete');
  // Initiate configuration.
  if (count($options_old) == 0) {
    foreach ($crud as $op) {
      if (!empty($options_new['eck_crud'][$op])) {
        return TRUE;
      }
    }
  }
  // Update configuration.
  else {
    foreach ($crud as $op) {
      if ($options_old['eck_crud'][$op] != $options_new['eck_crud'][$op]) {
        return TRUE;
      }
    }
  }
}

