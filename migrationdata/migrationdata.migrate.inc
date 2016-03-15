<?php
/**
 * @file
 * Declares our migrations.
 */
    

/**
 * Implements hook_migrate_api().
 */
function migrationdata_migrate_api() {
	
	$api = array(
    'api' => 2,
    'groups' => array( //define group array
      'qed42data' => array( //machine name
        'title' => t('Qed42data Imports'), //title
      ),
    ),

    'migrations' => array( //Migration array
      'Qed42Data' => array(
        'class_name' => 'MigrateQed42mongocitiesMigration', //Migration class name
        'group_name' => 'qed42data', //migration class blong to this group
      ),
      ),
		);

  return $api;
}
?>