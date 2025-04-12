--TEST--
Test Date
--EXTENSIONS--
duckdb
--FILE--
<?php
$duckDB = new \DuckDB\DuckDB();

$result = $duckDB->query("SELECT '1992-09-20'::DATE;");

$columns = $result->columnCount();
while ($dataChunk = $result->fetchChunk()) {
    $rows = $dataChunk->getSize();
    for ($i=0; $i<$columns; $i++) {
        $vector = $dataChunk->getVector($i);
        for ($r=0; $r<$rows; $r++) {
            $data = $vector->getData($r);
            printf("Class: %s\n", get_class($data));
            printf("Year: %s\n", $data->getYear());
            printf("Month: %s\n", $data->getMonth());
            printf("Day: %s\n", $data->getDay());
            printf("Date string: %s\n", $data);
            printf("Days since 1970-01-01: %s\n", $data->getDays());
        }
    }
}

$infinityDates = $duckDB->query("SELECT 'infinity'::DATE as infinity_date, '-infinity'::DATE as negative_infinity_date, 'epoch'::DATE as finite_date;");
$dataChunk = $infinityDates->fetchChunk();
$data = $dataChunk->getVector(0)->getData(0);
printf("Infinity value: %s\n", $data->infinity());
$data = $dataChunk->getVector(1)->getData(0);
printf("Infinity value: %s\n", $data->infinity());
$data = $dataChunk->getVector(2)->getData(0);
printf("Infinity value: %s\n", $data->infinity());

?>
--EXPECT--
Class: DuckDB\Value\Date
Year: 1992
Month: 9
Day: 20
Date string: 1992-09-20
Days since 1970-01-01: 8298
Infinity value: 1
Infinity value: -1
Infinity value: 0
