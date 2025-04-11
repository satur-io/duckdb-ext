--TEST--
Test get Vector
--EXTENSIONS--
duckdb
--FILE--
<?php
$duckDB = new \DuckDB\DuckDB();

$result = $duckDB->query("SELECT 'quack' as mycolumn1, 'quick' as mycolumn2;");

$columns = $result->columnCount();
while ($dataChunk = $result->fetchChunk()) {
    for ($i=0; $i<$columns; $i++) {
        $vector = $dataChunk->getVector($i);
        var_dump($vector);
    }
}
?>
--EXPECT--
object(DuckDB\Vector)#4 (0) {
}
object(DuckDB\Vector)#5 (0) {
}