--TEST--
Test decimal (float, double)
--EXTENSIONS--
duckdb
--FILE--
<?php
$duckDB = new \DuckDB\DuckDB();

$result = $duckDB->query("SELECT 1.1::FLOAT as mycolumn1, 4.1::DOUBLE as mycolumn2;");

$columns = $result->columnCount();
while ($dataChunk = $result->fetchChunk()) {
    $rows = $dataChunk->getSize();
    for ($i=0; $i<$columns; $i++) {
        $vector = $dataChunk->getVector($i);
        for ($r=0; $r<$rows; $r++) {
            $data = $vector->getData($r);
            var_dump($data);
        }
    }
}
?>
--EXPECT--
float(1.100000023841858)
float(4.1)
