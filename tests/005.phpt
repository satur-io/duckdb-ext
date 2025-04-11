--TEST--
Test column count
--EXTENSIONS--
duckdb
--FILE--
<?php
$duckDB = new \DuckDB\DuckDB();

$result = $duckDB->query("SELECT 'quack' as mycolumn");

printf("%s column(s)\n", $result->columnCount());

$result = $duckDB->query("SELECT 'quack' as mycolumn, 'quick' as mycolumn2");

printf("%s column(s)\n", $result->columnCount());
?>
--EXPECT--
1 column(s)
2 column(s)
