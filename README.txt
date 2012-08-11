=== Feature ===
1. Property Behavior: 
  * Published: Type(Interger/Unsigned Integer), like node published function.
2. Path and Pathauto per bundle and per entity.
3. Property Lable change after it's created.

== Planed Feature ==


=== Integration ===
1. Field UI: title, published, eck_path.
1. Pathauto.
2. Dispay Suite.

=== Change Logs ===

7.x-1.x -> 7.x-2.x
1. Version 2 add configuration form for each bundle created by eck.
  Configuration save in variable: 'eck_{entity_type}_{bundle}_options'.
2. Add title replace feature.
3. Add auto alias feature, require pathauto module.


=== API Hook ===
hook_eck_extras_pathauto_alias_alter(&$alias, &$context)
  @see eck_extras_pathauto_create_alias().
