--TEST--
Test string representation for non-customized types (uuid)
--EXTENSIONS--
duckdb
--FILE--
<?php
$duckDB = new \DuckDB\DuckDB();

$result = $duckDB->query("SELECT '9180eef3-9683-4568-bc19-a6968bc5e7b0'::UUID as mycolumn_uuid1;");

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
string(36) "9180eef3-9683-4568-bc19-a6968bc5e7b0"
