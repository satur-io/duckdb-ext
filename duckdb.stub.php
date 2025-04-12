<?php

/**
 * @generate-class-entries
 */

namespace DuckDB {
    /** @not-serializable */
    class DuckDB {
        public function __construct(?string $path = null) {}

        public function query(string $query): Result {}
    }

    /** @not-serializable */
    class Result {
        public function columnCount(): int {}
        public function fetchChunk(): ?DataChunk {}
    }

    /** @not-serializable */
    class DataChunk {
        public function getSize(): int {}
        public function getVector(int $columnIndex): Vector {}
    }

    /** @not-serializable */
    class Vector {
        public function getData(int $rowIndex): mixed {}
    }

    /**
     * @strict-properties
     */
    class Exception extends \Exception {}
}

/**
 * @generate-class-entries
 */

namespace DuckDB\Value {
    /**
     * @var int
     * @cvalue PHP_DUCKDB_POSITIVE_INFINITY
     */
    const POSITIVE_INFINITY = 1;

    /**
     * @var int
     * @cvalue PHP_DUCKDB_NEGATIVE_INFINITY
     */
    const NEGATIVE_INFINITY = -1;

    /**
     * @var int
     * @cvalue PHP_DUCKDB_FINITE
     */
    const FINITE = 0;

    /** @not-serializable */
    class Timestamp {
        public function infinity(): int {}
        public function __toString(): string {}
    }

    /** @not-serializable */
    class Date {
        public function infinity(): int {}
        public function getYear(): int {}
        public function getMonth(): int {}
        public function getDay(): int {}
        public function getDays(): int {}
        public function __toString(): string {}
    }

    /** @not-serializable */
    class Time {
        public function getMicros(): int {}
        public function __toString(): string {}
    }
}

namespace {
    function duckdb_info(): void {}
}
