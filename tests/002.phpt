--TEST--
Test info
--EXTENSIONS--
duckdb
--FILE--
<?php
duckdb_info();
?>
--EXPECT--
The extension duckdb is loaded and working!
Library version v1.2.2
