# ECK Mod
* Entity Type
  - Allow changing property label after creation.
* Entity Bundle
  - Title override.
  - Pathauto pattern.

# ECK property_behavior
* hidden
* name
* text
* textarea
* url
* entityreference
* status
* usin
* @todo entity reference kit
  - entity_type
  - entity_bundle
  - entity_id

# Ctools
* Arguments
  - name
  - @todo usin

# API - Utility


# ECK Plugin: property_behavior

    $plugin = array(
      'label' => t(''), // @required
      'unique' => FALSE, // @optional Default FALSE.
      // Callbacks @ref What calls eck_property_behavior_invoke_plugin()
      'entity_info' => '',
      'entity_view' => '',
      'entity_insert' => '', // ??? Does this work?
      'entity_save' => '', // Mimic: entity_insert. Origin: Hook to hook_entity_presave().
      'entity_update' => '',
      'entity_delete' => '',
      // 
      'default_widget' => '',
      'default_formatter' => '', // @see eck__entity__view().
      'pre_set' => '', // @see eck__entity__form_submit().
      // Callbacks @ref What calls eck_property_behavior_invoke_plugin_alter()
      'property_info' => '',
      'getter' => '', // @optional @see eck_property_behavior_getter().
      'setter'> '', // @optional @see eck_property_behavior_setter().
      'validation' => '', // @optional @see eck_property_behavior_validation().
      'views_data_alter' => '',
      // The bundle edit form
      'bundle_form' => '',
    );
