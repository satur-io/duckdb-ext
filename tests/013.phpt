--TEST--
Test timestamp
--EXTENSIONS--
duckdb
--FILE--
<?php
$duckDB = new \DuckDB\DuckDB();

$result = $duckDB->query("SELECT '1521-04-23 12:45:17.1234'::TIMESTAMP as mycolumn_date1, '1521-04-17 12:45:17.1234'::TIMESTAMP as mycolumn_date1;");

$columns = $result->columnCount();
while ($dataChunk = $result->fetchChunk()) {
    $rows = $dataChunk->getSize();
    for ($i=0; $i<$columns; $i++) {
        $vector = $dataChunk->getVector($i);
        for ($r=0; $r<$rows; $r++) {
            $data = $vector->getData($r);
            printf("%s\n", $data);
            unset($data);
        }
        unset($vector);
    }
}
unset($dataChunk);
unset($result);

$infinityTimestamps = $duckDB->query("SELECT 'infinity'::TIMESTAMP as infinity_timestamp, '-infinity'::TIMESTAMP as negative_infinity_timestamp, 'epoch'::TIMESTAMP as finite_timestamp;");
var_dump($infinityTimestamps->columnCount());

$dataChunk = $infinityTimestamps->fetchChunk();
$data = $dataChunk->getVector(0)->getData(0);
printf("Infinity value: %s\n", $data->infinity());
$data = $dataChunk->getVector(1)->getData(0);
printf("Infinity value: %s\n", $data->infinity());
$data = $dataChunk->getVector(2)->getData(0);
printf("Infinity value: %s\n", $data->infinity());

?>
--EXPECT--
1521-04-23 12:45:17.1234
1521-04-17 12:45:17.1234
int(3)
Infinity value: 1
Infinity value: -1
Infinity value: 0
