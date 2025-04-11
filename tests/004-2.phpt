--TEST--
Test consecutive queries
--EXTENSIONS--
duckdb
--FILE--
<?php
$duckDB = new \DuckDB\DuckDB();

$result = $duckDB->query("SELECT 'quack' as mycolumn");
var_dump($result);


$result = $duckDB->query("SELECT 'quick' as mycolumn");
var_dump($result);

?>
--EXPECT--
object(DuckDB\Result)#2 (1) {
  ["{duckdb_result}"]=>
  array(1) {
    ["initialised"]=>
    bool(true)
  }
}
object(DuckDB\Result)#3 (1) {
  ["{duckdb_result}"]=>
  array(1) {
    ["initialised"]=>
    bool(true)
  }
}
