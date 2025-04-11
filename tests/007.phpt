--TEST--
Test data chunk size
--EXTENSIONS--
duckdb
--FILE--
<?php
$duckDB = new \DuckDB\DuckDB();

$result = $duckDB->query("SELECT * FROM repeat('h', 1000000);");

$rows = 0;
while ($dataChunk = $result->fetchChunk()) {
    $rows += $dataChunk->getSize();
}

printf("%s rows", $rows)

?>
--EXPECT--
1000000 rows
