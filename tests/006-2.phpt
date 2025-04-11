--TEST--
Test fetch consecutive data chunks
--EXTENSIONS--
duckdb
--FILE--
<?php
$duckDB = new \DuckDB\DuckDB();

$result = $duckDB->query("SELECT 'quack' as mycolumn");
//var_dump($result);
while ($dataChunk = $result->fetchChunk()) {
    var_dump($dataChunk);
}

$result = $duckDB->query("SELECT 'quick' as mycolumn");

while ($dataChunk = $result->fetchChunk()) {
    var_dump($dataChunk);
}

?>
--EXPECT--
object(DuckDB\DataChunk)#3 (0) {
}
object(DuckDB\DataChunk)#2 (0) {
}
