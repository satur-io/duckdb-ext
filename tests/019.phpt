--TEST--
Test Struct
--EXTENSIONS--
duckdb
--FILE--
<?php
$duckDB = new \DuckDB\DuckDB();

$result = $duckDB->query("SELECT {'yes': 'duck', 'maybe': 'goose', 'huh': NULL, 'no': 'heron'} AS s;");

$columns = $result->columnCount();
while ($dataChunk = $result->fetchChunk()) {
    $rows = $dataChunk->getSize();
    for ($i=0; $i<$columns; $i++) {
        $vector = $dataChunk->getVector($i);
        for ($r=0; $r<$rows; $r++) {
            $data = $vector->getData($r);
            $childs = $data->childCount();
            printf("Childs: %s\n", $childs);

            for ($i=0; $i<$childs; $i++) {
                printf("Name %s: %s\n", $i, $data->childName($i));

                $nested_vector = $data->getChild($i);
                printf("Value %s: %s\n", $i, $nested_vector->getData($r));
            }
        }
    }
}


$result = $duckDB->query("SELECT * FROM VALUES ({'yes': 'duck', 'maybe': 'goose'}), ({'yes': 'cua', 'maybe': 'alfred'}) AS s;");
$columns = $result->columnCount();
while ($dataChunk = $result->fetchChunk()) {
    $rows = $dataChunk->getSize();
    for ($i=0; $i<$columns; $i++) {
        $vector = $dataChunk->getVector($i);
        for ($r=0; $r<$rows; $r++) {
            $data = $vector->getData($r);
            $childs = $data->childCount();
            printf("Childs: %s\n", $childs);

            $dataArray = $data->toArray();
            foreach ($dataArray as $key => $value) {
                printf("Row %s, for the key %s, value %s\n", $r, $key, $value);
            }

            printf("To string: %s\n", $data);
        }
    }
}

?>
--EXPECT--
Childs: 4
Name 0: yes
Value 0: duck
Name 1: maybe
Value 1: goose
Name 2: huh
Value 2: 
Name 3: no
Value 3: heron
Childs: 2
Row 0, for the key yes, value duck
Row 0, for the key maybe, value goose
To string: {"yes":"duck","maybe":"goose"}
Childs: 2
Row 1, for the key yes, value cua
Row 1, for the key maybe, value alfred
To string: {"yes":"cua","maybe":"alfred"}
