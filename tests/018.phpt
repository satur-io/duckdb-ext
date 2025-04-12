--TEST--
Test Time
--EXTENSIONS--
duckdb
--FILE--
<?php
$duckDB = new \DuckDB\DuckDB();

$result = $duckDB->query("SELECT '1992-09-20 11:30:00.123456'::TIME as mycolumn1;");

$columns = $result->columnCount();
while ($dataChunk = $result->fetchChunk()) {
    $rows = $dataChunk->getSize();
    for ($i=0; $i<$columns; $i++) {
        $vector = $dataChunk->getVector($i);
        for ($r=0; $r<$rows; $r++) {
            $data = $vector->getData($r);
            printf("Time string: %s\n", $data);
            printf("Microseconds: %s\n", $data->getMicros());
        }
    }
}
?>
--EXPECT--
Time string: 11:30:00.123456
Microseconds: 41400123456
