--TEST--
Create a DuckDB object
--EXTENSIONS--
duckdb
--FILE--
<?php
$duckDB = new \DuckDB\DuckDB();

var_dump($duckDB);

?>
--EXPECT--
object(DuckDB\DuckDB)#1 (1) {
  ["{duckdb}"]=>
  array(3) {
    ["initialised"]=>
    bool(true)
    ["database_initialised"]=>
    bool(true)
    ["connection_initialised"]=>
    bool(true)
  }
}