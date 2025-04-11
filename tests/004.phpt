--TEST--
Test Query
--EXTENSIONS--
duckdb
--FILE--
<?php
$duckDB = new \DuckDB\DuckDB();

$result = $duckDB->query("SELECT 'quack' as mycolumn");

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

