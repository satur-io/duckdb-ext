--TEST--
Test consecutive iterate rows
--EXTENSIONS--
duckdb
--FILE--
<?php
$duckDB = new \DuckDB\DuckDB();

$result = $duckDB->query("SELECT 'quack' as mycolumn1, 'quick' as mycolumn2;");

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

$result = $duckDB->query("SELECT 'queck' as mycolumn1, 'quock' as mycolumn2;");

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

$result = $duckDB->query("SELECT * FROM repeat('quack', 1000000);");

$rows = 0;
while ($dataChunk = $result->fetchChunk()) {
    $rows += $dataChunk->getSize();
}

printf("%s rows", $rows)

?>
--EXPECT--
string(5) "quack"
string(5) "quick"
string(5) "queck"
string(5) "quock"
1000000 rows
