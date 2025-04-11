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

    /** @not-serializable */
    class Timestamp {
        /**
         * @var int
         * @cvalue PHP_DUCKDB_POSITIVE_INFINITY
         */
        public const POSITIVE_INFINITY = 1;

        /**
         * @var int
         * @cvalue PHP_DUCKDB_NEGATIVE_INFINITY
         */
        public const NEGATIVE_INFINITY = -1;

        /**
         * @var int
         * @cvalue PHP_DUCKDB_FINITE
         */
        public const FINITE = 0;

        public function infinity(): int {}
        public function __toString(): string {}
    }

    class Date {
    }

    class Time {
    }
}

namespace {
    function duckdb_info(): void {}
}
