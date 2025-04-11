--TEST--
Test fetch data chunk
--EXTENSIONS--
duckdb
--FILE--
<?php
$duckDB = new \DuckDB\DuckDB();

$result = $duckDB->query("SELECT 'quack' as mycolumn");

while ($dataChunk = $result->fetchChunk()) {
    var_dump($dataChunk);
}

?>
--EXPECT--
object(DuckDB\DataChunk)#3 (0) {
}
