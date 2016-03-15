<?php
//Extend base class
abstract class BasicQed42drupalcitiesMigration extends Migration {
  public function __construct($arguments) {
    parent::__construct($arguments);
  }
}

//Extent child class
class MigrateQed42mongocitiesMigration extends BasicQed42drupalcitiesMigration {
  public function __construct($arguments) {
    parent::__construct($arguments);
		
		//make connection
		$db_string = 'mongodb://admin:admin@localhost/qed42';
		$m = new MongoClient($db_string);
		
		//no need of this line
		$db = $m->qed42;
		
		//fetch table data from database
		$collection = $m->selectCollection("qed42", "cities");
		
		//define field array of source table 
		$fields = array(
			'_id' => 'Object ID',
			'city' => 'City',
			'loc' => 'Location',
			'pop' => 'POP',
			'state' => 'State'
		);
		
		//query array
		$query = array();
		
		//shorting array
		$sort = array(
			'_id' => 1,
		);
		
		//Set source
		$this->source = new MigrateSourceMongoDB($collection, $query, $fields, $sort);
		
		// Set destination.
		$this->destination = new MigrateDestinationNode('cities');
		
		// Set map.
		$source_key = array(
			'_id' => array(
				'type' => 'varchar',
				'length' => 24,
				'not null' => TRUE,
				'description' => 'MongoDB ID field.',
			),
		);
		
		//Set mapping object
		$this->map = new MigrateSQLMap($this->machineName, $source_key, MigrateDestinationNode::getKeySchema());
		
		//define fields mapping
		$this->addFieldMapping('title', 'pop');
		$this->addFieldMapping('field_city', 'city');
		$this->addFieldMapping('field_location_lat_long_', 'loc');
		$this->addFieldMapping('field_state', 'state'); 
  }
}