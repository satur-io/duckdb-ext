/* duckdb extension for PHP (c) 2025 Daniel Hernández-Marín */

#define PHP_DUCKDB_POSITIVE_INFINITY 1
#define PHP_DUCKDB_NEGATIVE_INFINITY -1
#define PHP_DUCKDB_FINITE 0

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "php_duckdb.h"
#include "duckdb_arginfo.h"
#include "zend_exceptions.h"

#include <duckdb.h>

/* For compatibility with older PHP versions */
#ifndef ZEND_PARSE_PARAMETERS_NONE
#define ZEND_PARSE_PARAMETERS_NONE()  \
    ZEND_PARSE_PARAMETERS_START(0, 0) \
    ZEND_PARSE_PARAMETERS_END()
#endif

static zend_object_handlers duckdb_object_handlers;
static zend_object_handlers database_object_handlers;
static zend_object_handlers connection_object_handlers;
static zend_object_handlers result_object_handlers;
static zend_object_handlers data_chunk_object_handlers;
static zend_object_handlers vector_object_handlers;
static zend_object_handlers timestamp_object_handlers;
static zend_object_handlers date_object_handlers;
static zend_object_handlers time_object_handlers;
static zend_object_handlers struct_object_handlers;

static zend_class_entry *duckdb_class_entry = NULL;
static zend_class_entry *duckdb_database_class_entry = NULL;
static zend_class_entry *duckdb_connection_class_entry = NULL;
static zend_class_entry *duckdb_result_class_entry = NULL;
static zend_class_entry *duckdb_data_chunk_class_entry = NULL;
static zend_class_entry *duckdb_vector_class_entry = NULL;
static zend_class_entry *duckdb_timestamp_class_entry = NULL;
static zend_class_entry *duckdb_date_class_entry = NULL;
static zend_class_entry *duckdb_time_class_entry = NULL;
static zend_class_entry *duckdb_struct_class_entry = NULL;

static zend_class_entry *duckdb_exception_class_entry = NULL;

/* Structs */
typedef struct duckdb_t
{
    bool initialised;
    duckdb_database *database;
    duckdb_connection *connection;
    zend_object std;
} duckdb_t;

typedef struct duckdb_database_t
{
    duckdb_database db;
    zend_object std;
} duckdb_database_t;

typedef struct duckdb_connection_t
{
    duckdb_connection conn;
    zend_object std;
} duckdb_connection_t;

typedef struct duckdb_result_t
{
    bool initialised;
    duckdb_result *result;
    zend_object std;
} duckdb_result_t;

typedef struct duckdb_data_chunk_t
{
    bool initialised;
    duckdb_data_chunk chunk;
    zend_object std;
} duckdb_data_chunk_t;

typedef struct duckdb_vector_t
{
    duckdb_vector vector;
    duckdb_type type;
    duckdb_logical_type logical_type;
    void *data;
    uint64_t *validity;
    zend_object std;
} duckdb_vector_t;

typedef struct duckdb_nested_vector_t
{
    duckdb_vector_t *vector;
    zend_object std;
} duckdb_nested_vector_t;

typedef struct duckdb_timestamp_t
{
    duckdb_timestamp timestamp;
    zend_object std;
} duckdb_timestamp_t;

typedef struct duckdb_date_t
{
    duckdb_date date;
    duckdb_date_struct date_struct;
    bool date_struct_initialised;
    zend_object std;
} duckdb_date_t;

typedef struct duckdb_time_t
{
    duckdb_time time;
    duckdb_time_struct time_struct;
    bool time_struct_initialised;
    zend_object std;
} duckdb_time_t;

/* Type transformers */
static inline duckdb_t *duckdb_t_from_obj(zend_object *obj)
{
    return (duckdb_t *)((char *)(obj)-XtOffsetOf(duckdb_t, std));
}
#define Z_DUCKDB_P(zv) duckdb_t_from_obj(Z_OBJ_P(zv))

static inline duckdb_result_t *duckdb_result_t_from_obj(zend_object *obj)
{
    return (duckdb_result_t *)((char *)(obj)-XtOffsetOf(duckdb_result_t, std));
}
#define Z_DUCKDB_RESULT_P(zv) duckdb_result_t_from_obj(Z_OBJ_P(zv))

static inline duckdb_data_chunk_t *duckdb_data_chunk_t_from_obj(zend_object *obj)
{
    return (duckdb_data_chunk_t *)((char *)(obj)-XtOffsetOf(duckdb_data_chunk_t, std));
}
#define Z_DUCKDB_DATA_CHUNK_P(zv) duckdb_data_chunk_t_from_obj(Z_OBJ_P(zv))

static inline duckdb_vector_t *duckdb_vector_t_from_obj(zend_object *obj)
{
    return (duckdb_vector_t *)((char *)(obj)-XtOffsetOf(duckdb_vector_t, std));
}
#define Z_DUCKDB_VECTOR_P(zv) duckdb_vector_t_from_obj(Z_OBJ_P(zv))

static inline duckdb_timestamp_t *duckdb_timestamp_t_from_obj(zend_object *obj)
{
    return (duckdb_timestamp_t *)((char *)(obj)-XtOffsetOf(duckdb_timestamp_t, std));
}
#define Z_DUCKDB_TIMESTAMP_P(zv) duckdb_timestamp_t_from_obj(Z_OBJ_P(zv))

static inline duckdb_date_t *duckdb_date_t_from_obj(zend_object *obj)
{
    return (duckdb_date_t *)((char *)(obj)-XtOffsetOf(duckdb_date_t, std));
}
#define Z_DUCKDB_DATE_P(zv) duckdb_date_t_from_obj(Z_OBJ_P(zv))

static inline duckdb_time_t *duckdb_time_t_from_obj(zend_object *obj)
{
    return (duckdb_time_t *)((char *)(obj)-XtOffsetOf(duckdb_time_t, std));
}
#define Z_DUCKDB_TIME_P(zv) duckdb_time_t_from_obj(Z_OBJ_P(zv))

static inline duckdb_nested_vector_t *duckdb_nested_vector_t_from_obj(zend_object *obj)
{
    return (duckdb_nested_vector_t *)((char *)(obj)-XtOffsetOf(duckdb_nested_vector_t, std));
}
#define Z_DUCKDB_NESTED_VECTOR_P(zv) duckdb_nested_vector_t_from_obj(Z_OBJ_P(zv))

/* Free object functions */
static void duckdb_free_obj(zend_object *obj)
{
    duckdb_t *duckdb = duckdb_t_from_obj(obj);

    if (duckdb->connection != NULL)
    {
        duckdb_disconnect(duckdb->connection);
    }

    if (duckdb->database != NULL)
    {
        duckdb_close(duckdb->database);
    }

    efree(duckdb->connection);
    efree(duckdb->database);
    zend_object_std_dtor(&duckdb->std);
}

static void duckdb_result_free_obj(zend_object *obj)
{
    duckdb_result_t *result_t = duckdb_result_t_from_obj(obj);

    if (result_t->initialised && result_t->result != NULL)
    {
        duckdb_destroy_result(result_t->result);
        result_t->initialised = false;
    }

    efree(result_t->result);
    zend_object_std_dtor(&result_t->std);
}

static void duckdb_data_chunk_free_obj(zend_object *obj)
{
    duckdb_data_chunk_t *data_chunk = duckdb_data_chunk_t_from_obj(obj);

    if (data_chunk->initialised && data_chunk->chunk != NULL)
    {
        duckdb_destroy_data_chunk(&data_chunk->chunk);
        data_chunk->initialised = false;
    }

    zend_object_std_dtor(&data_chunk->std);
}

static void duckdb_vector_free_obj(zend_object *obj)
{
    duckdb_vector_t *vector = duckdb_vector_t_from_obj(obj);

    if (vector->logical_type != NULL)
    {
        duckdb_destroy_logical_type(&vector->logical_type);
    }

    zend_object_std_dtor(&vector->std);
}

static void duckdb_nested_vector_free_obj(zend_object *obj)
{
    duckdb_nested_vector_t *vector = duckdb_nested_vector_t_from_obj(obj);
    zend_object_std_dtor(&vector->std);
}

static void duckdb_timestamp_free_obj(zend_object *obj)
{
    duckdb_timestamp_t *timestamp = duckdb_timestamp_t_from_obj(obj);

    zend_object_std_dtor(&timestamp->std);
}

static void duckdb_date_free_obj(zend_object *obj)
{
    duckdb_date_t *date = duckdb_date_t_from_obj(obj);
    zend_object_std_dtor(&date->std);
}

static void duckdb_time_free_obj(zend_object *obj)
{
    duckdb_time_t *time_t = duckdb_time_t_from_obj(obj);
    zend_object_std_dtor(&time_t->std);
}

/* Create object functions */
static zend_object *duckdb_new(zend_class_entry *ce)
{
    duckdb_t *duckdb = zend_object_alloc(sizeof(duckdb_t), ce);

    zend_object_std_init(&duckdb->std, ce);
    object_properties_init(&duckdb->std, ce);
    return &duckdb->std;
}

static zend_object *duckdb_result_new(zend_class_entry *ce)
{
    duckdb_result_t *result = zend_object_alloc(sizeof(duckdb_result_t), ce);

    zend_object_std_init(&result->std, ce);
    object_properties_init(&result->std, ce);

    return &result->std;
}

static zend_object *duckdb_data_chunk_new(zend_class_entry *ce)
{
    duckdb_data_chunk_t *data_chunk = zend_object_alloc(sizeof(duckdb_data_chunk_t), ce);

    zend_object_std_init(&data_chunk->std, ce);
    object_properties_init(&data_chunk->std, ce);

    return &data_chunk->std;
}

static zend_object *duckdb_vector_new(zend_class_entry *ce)
{
    duckdb_vector_t *vector = zend_object_alloc(sizeof(duckdb_vector_t), ce);

    zend_object_std_init(&vector->std, ce);
    object_properties_init(&vector->std, ce);

    return &vector->std;
}

static zend_object *duckdb_nested_vector_new(zend_class_entry *ce)
{
    duckdb_nested_vector_t *vector = zend_object_alloc(sizeof(duckdb_nested_vector_t), ce);

    zend_object_std_init(&vector->std, ce);
    object_properties_init(&vector->std, ce);

    return &vector->std;
}

static zend_object *duckdb_timestamp_new(zend_class_entry *ce)
{
    duckdb_timestamp_t *timestamp = zend_object_alloc(sizeof(duckdb_timestamp_t), ce);

    zend_object_std_init(&timestamp->std, ce);
    object_properties_init(&timestamp->std, ce);

    return &timestamp->std;
}

static zend_object *duckdb_date_new(zend_class_entry *ce)
{
    duckdb_date_t *date = zend_object_alloc(sizeof(duckdb_date_t), ce);

    zend_object_std_init(&date->std, ce);
    object_properties_init(&date->std, ce);

    return &date->std;
}

static zend_object *duckdb_time_new(zend_class_entry *ce)
{
    duckdb_time_t *time = zend_object_alloc(sizeof(duckdb_time_t), ce);

    zend_object_std_init(&time->std, ce);
    object_properties_init(&time->std, ce);

    return &time->std;
}

/* Constructors */
PHP_METHOD(DuckDB_DuckDB, __construct)
{
    zval *object = ZEND_THIS;
    duckdb_t *duckdb_t;
    char *path = NULL;
    size_t path_len = 0;

    ZEND_PARSE_PARAMETERS_START(0, 1)
    Z_PARAM_OPTIONAL
    Z_PARAM_STRING(path, path_len)
    ZEND_PARSE_PARAMETERS_END();

    duckdb_t = Z_DUCKDB_P(object);

    if (path_len == 0)
    {
        path = NULL;
    }

    duckdb_t->database = emalloc(sizeof(duckdb_database));
    if (duckdb_open(path, duckdb_t->database) == DuckDBError)
    {
        php_printf("Error opening\n");
        RETURN_THROWS();
    }

    duckdb_t->connection = emalloc(sizeof(duckdb_connection));
    if (duckdb_connect(*duckdb_t->database, duckdb_t->connection) == DuckDBError)
    {
        php_printf("Error connecting\n");
        RETURN_THROWS();
    }

    duckdb_t->initialised = true;
}

PHP_METHOD(DuckDB_DataChunk, __construct)
{
    zend_throw_exception(zend_ce_exception, "\\DuckDB\\DataChunk cannot be directly instantiated", 0);
}

/* HasTable functions (debug object output, i.e. with var_dump()) */
static HashTable *duckdb_get_debug_info(zend_object *object, int *is_temp)
{
    duckdb_t *duckdb_t = duckdb_t_from_obj(object);
    HashTable *ret = zend_new_array(1);

    zval tmp;
    array_init(&tmp);
    add_assoc_bool(&tmp, "initialised", duckdb_t->initialised);
    add_assoc_bool(&tmp, "database_initialised", duckdb_t->database);
    add_assoc_bool(&tmp, "connection_initialised", duckdb_t->connection);

    zend_hash_str_add(ret, "{duckdb}", sizeof("{duckdb}") - 1, &tmp);

    *is_temp = 1;
    return ret;
}

static HashTable *duckdb_result_get_debug_info(zend_object *object, int *is_temp)
{
    duckdb_result_t *result_t = duckdb_result_t_from_obj(object);
    HashTable *ret = zend_new_array(1);

    zval tmp;
    array_init(&tmp);
    add_assoc_bool(&tmp, "initialised", result_t->initialised);

    zend_hash_str_add(ret, "{duckdb_result}", sizeof("{duckdb_result}") - 1, &tmp);
    *is_temp = 1;
    return ret;
}

/* toString methods */
PHP_METHOD(DuckDB_Value_Timestamp, __toString)
{
    zval *object = ZEND_THIS;
    duckdb_timestamp_t *timestamp_t;

    ZEND_PARSE_PARAMETERS_NONE();

    timestamp_t = Z_DUCKDB_TIMESTAMP_P(object);
    RETURN_STRING(duckdb_get_varchar(duckdb_create_timestamp(timestamp_t->timestamp)));
}

PHP_METHOD(DuckDB_Value_Date, __toString)
{
    zval *object = ZEND_THIS;
    duckdb_date_t *date_t;

    ZEND_PARSE_PARAMETERS_NONE();

    date_t = Z_DUCKDB_DATE_P(object);
    RETURN_STRING(duckdb_get_varchar(duckdb_create_date(date_t->date)));
}

PHP_METHOD(DuckDB_Value_Time, __toString)
{
    zval *object = ZEND_THIS;
    duckdb_time_t *time_t;

    ZEND_PARSE_PARAMETERS_NONE();

    time_t = Z_DUCKDB_TIME_P(object);

    duckdb_time_struct time_struct = duckdb_from_time(time_t->time);
    char buffer[16];
    snprintf(buffer, sizeof(buffer), "%02d:%02d:%02d.%06d", time_struct.hour, time_struct.min, time_struct.sec, time_struct.micros);
    RETURN_STRING(buffer);
}

/* PHP functions */
PHP_FUNCTION(duckdb_info)
{
    ZEND_PARSE_PARAMETERS_NONE();

    php_printf("The extension %s is loaded and working!\r\n", "duckdb");
    php_printf("Library version %s\r\n", duckdb_library_version());
}

PHP_METHOD(DuckDB_DuckDB, query)
{
    zval *object = ZEND_THIS;
    duckdb_t *duckdb_t;
    duckdb_result_t *result_t;
    char *query = NULL;
    size_t query_len = 0;

    ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_STRING(query, query_len)
    ZEND_PARSE_PARAMETERS_END();

    duckdb_t = Z_DUCKDB_P(object);

    if (!USED_RET())
    {
        if (duckdb_query(*duckdb_t->connection, query, NULL) == DuckDBError)
        {
            RETURN_THROWS();
        }
        RETURN_TRUE;
    }

    object_init_ex(return_value, duckdb_result_class_entry);
    result_t = Z_DUCKDB_RESULT_P(return_value);
    result_t->result = emalloc(sizeof(duckdb_result));

    if (duckdb_query(*duckdb_t->connection, query, result_t->result) == DuckDBError)
    {
        RETURN_THROWS();
    }

    result_t->initialised = true;
}

PHP_METHOD(DuckDB_Result, columnCount)
{
    zval *object = ZEND_THIS;
    duckdb_result_t *result_t;

    ZEND_PARSE_PARAMETERS_NONE();

    result_t = Z_DUCKDB_RESULT_P(object);
    RETURN_LONG(duckdb_column_count(result_t->result));
}

PHP_METHOD(DuckDB_Result, fetchChunk)
{
    zval *object = ZEND_THIS;
    duckdb_result_t *result_t;
    duckdb_data_chunk_t *data_chunk_t;

    ZEND_PARSE_PARAMETERS_NONE();

    result_t = Z_DUCKDB_RESULT_P(object);

    object_init_ex(return_value, duckdb_data_chunk_class_entry);
    data_chunk_t = Z_DUCKDB_DATA_CHUNK_P(return_value);
    data_chunk_t->chunk = duckdb_fetch_chunk(*result_t->result);
    if (!data_chunk_t->chunk)
    {
        efree(data_chunk_t);
        RETURN_NULL();
    }
    data_chunk_t->initialised = true;
}

PHP_METHOD(DuckDB_DataChunk, getSize)
{
    zval *object = ZEND_THIS;
    duckdb_data_chunk_t *data_chunk_t;

    ZEND_PARSE_PARAMETERS_NONE();

    data_chunk_t = Z_DUCKDB_DATA_CHUNK_P(object);
    RETURN_LONG(duckdb_data_chunk_get_size(data_chunk_t->chunk));
}

PHP_METHOD(DuckDB_DataChunk, getVector)
{
    zval *object = ZEND_THIS;
    duckdb_data_chunk_t *data_chunk_t;
    duckdb_vector_t *vector_t;
    zend_long index;

    ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_LONG(index)
    ZEND_PARSE_PARAMETERS_END();

    data_chunk_t = Z_DUCKDB_DATA_CHUNK_P(object);

    object_init_ex(return_value, duckdb_vector_class_entry);
    vector_t = Z_DUCKDB_VECTOR_P(return_value);
    vector_t->vector = duckdb_data_chunk_get_vector(data_chunk_t->chunk, index);
}

static void duckdb_value_to_zval(duckdb_vector_t *vector_t, int rowIndex, zval *data)
{
    switch (vector_t->type)
    {
    case DUCKDB_TYPE_BOOLEAN:
        ZVAL_BOOL(data, ((bool *)vector_t->data)[rowIndex]);
        break;
    case DUCKDB_TYPE_VARCHAR:
        uint32_t len = ((duckdb_string_t *)vector_t->data)[rowIndex].value.inlined.length;

        if (len > 12)
        {
            ZVAL_STRINGL(data, ((duckdb_string_t *)vector_t->data)[rowIndex].value.pointer.ptr, len);
        }
        else
        {
            ZVAL_STRINGL(data, ((duckdb_string_t *)vector_t->data)[rowIndex].value.inlined.inlined, len);
        }
        break;
    case DUCKDB_TYPE_TINYINT:
        ZVAL_LONG(data, ((int8_t *)vector_t->data)[rowIndex]);
        break;
    case DUCKDB_TYPE_SMALLINT:
        ZVAL_LONG(data, ((int16_t *)vector_t->data)[rowIndex]);
        break;
    case DUCKDB_TYPE_INTEGER:
        ZVAL_LONG(data, ((int32_t *)vector_t->data)[rowIndex]);
        break;
    case DUCKDB_TYPE_BIGINT:
        ZVAL_LONG(data, ((int64_t *)vector_t->data)[rowIndex]);
        break;
    case DUCKDB_TYPE_UTINYINT:
        ZVAL_LONG(data, ((uint8_t *)vector_t->data)[rowIndex]);
        break;
    case DUCKDB_TYPE_USMALLINT:
        ZVAL_LONG(data, ((uint16_t *)vector_t->data)[rowIndex]);
        break;
    case DUCKDB_TYPE_UINTEGER:
        ZVAL_LONG(data, ((uint32_t *)vector_t->data)[rowIndex]);
        break;
    case DUCKDB_TYPE_UBIGINT:
        ZVAL_LONG(data, ((uint64_t *)vector_t->data)[rowIndex]);
        break;
    case DUCKDB_TYPE_FLOAT:
        ZVAL_DOUBLE(data, ((float *)vector_t->data)[rowIndex]);
        break;
    case DUCKDB_TYPE_DOUBLE:
        ZVAL_DOUBLE(data, ((double *)vector_t->data)[rowIndex]);
        break;
    case DUCKDB_TYPE_TIMESTAMP:
    {
        object_init_ex(data, duckdb_timestamp_class_entry);
        duckdb_timestamp_t *timestamp_t = Z_DUCKDB_TIMESTAMP_P(data);
        timestamp_t->timestamp = ((duckdb_timestamp *)vector_t->data)[rowIndex];
        break;
    }
    case DUCKDB_TYPE_DATE:
    {
        object_init_ex(data, duckdb_date_class_entry);
        duckdb_date_t *date_t = Z_DUCKDB_DATE_P(data);
        date_t->date = ((duckdb_date *)vector_t->data)[rowIndex];
        break;
    }
    case DUCKDB_TYPE_TIME:
    {
        object_init_ex(data, duckdb_time_class_entry);
        duckdb_time_t *time_t = Z_DUCKDB_TIME_P(data);
        time_t->time = ((duckdb_time *)vector_t->data)[rowIndex];
        break;
    }
    case DUCKDB_TYPE_STRUCT:
    {
        object_init_ex(data, duckdb_struct_class_entry);
        duckdb_nested_vector_t *nested_vector = Z_DUCKDB_NESTED_VECTOR_P(data);
        nested_vector->vector = vector_t;
        break;
    }
    // Other types just cast to string
    // TODO: convert types to PHP properly
    case DUCKDB_TYPE_UUID:
    {
        duckdb_hugeint uuid_hugeint = ((duckdb_hugeint *)vector_t->data)[rowIndex];
        duckdb_uhugeint uuid_uhugeint;
        uuid_uhugeint.lower = uuid_hugeint.lower;

        if (uuid_hugeint.upper >= 0)
        {
            uuid_uhugeint.upper = (uint64_t)(uuid_hugeint.upper) + (uint64_t)(INT64_MAX) + 1;
        }
        else
        {
            uuid_uhugeint.upper = (uint64_t)(uuid_hugeint.upper + INT64_MAX + 1);
        }

        duckdb_value value = duckdb_create_uuid(uuid_uhugeint);

        char *string = duckdb_get_varchar(value);
        ZVAL_STRING(data, string);
        break;
    }
    case DUCKDB_TYPE_INTERVAL:
    {
        duckdb_interval value = ((duckdb_interval *)vector_t->data)[rowIndex];
        duckdb_value value_value = duckdb_create_interval(value);

        char *string = duckdb_get_varchar(value_value);
        ZVAL_STRING(data, string);
        break;
    }
    default:
    {
        ZVAL_NULL(data);
    }
    }
}

PHP_METHOD(DuckDB_Vector, getData)
{
    zval *object = ZEND_THIS;
    duckdb_vector_t *vector_t;
    zend_long rowIndex;

    ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_LONG(rowIndex)
    ZEND_PARSE_PARAMETERS_END();

    vector_t = Z_DUCKDB_VECTOR_P(object);

    if (vector_t->type == DUCKDB_TYPE_INVALID)
    {
        vector_t->logical_type = duckdb_vector_get_column_type(vector_t->vector);
        vector_t->type = duckdb_get_type_id(vector_t->logical_type);
    }

    if (vector_t->validity == NULL)
    {
        vector_t->validity = duckdb_vector_get_validity(vector_t->vector);
    }

    if (vector_t->data == NULL)
    {
        vector_t->data = duckdb_vector_get_data(vector_t->vector);
    }

    if (duckdb_validity_row_is_valid(vector_t->validity, rowIndex))
    {
        duckdb_value_to_zval(vector_t, rowIndex, return_value);
        return;
    }

    RETURN_NULL();
}

/* Values methods */
PHP_METHOD(DuckDB_Value_Timestamp, infinity)
{
    zval *object = ZEND_THIS;
    duckdb_timestamp_t *timestamp_t;

    ZEND_PARSE_PARAMETERS_NONE();

    timestamp_t = Z_DUCKDB_TIMESTAMP_P(object);

    if (duckdb_is_finite_timestamp(timestamp_t->timestamp))
    {
        RETURN_LONG(PHP_DUCKDB_FINITE);
    }

    if ((&timestamp_t->timestamp)->micros > 0)
    {
        RETURN_LONG(PHP_DUCKDB_POSITIVE_INFINITY);
    }

    RETURN_LONG(PHP_DUCKDB_NEGATIVE_INFINITY);
}

PHP_METHOD(DuckDB_Value_Timestamp, getDate)
{
    zval *object = ZEND_THIS;
    duckdb_timestamp_t *timestamp_t;
    duckdb_timestamp_struct timestamp_struct;

    ZEND_PARSE_PARAMETERS_NONE();

    timestamp_t = Z_DUCKDB_TIMESTAMP_P(object);

    timestamp_struct = duckdb_from_timestamp(timestamp_t->timestamp);
    object_init_ex(return_value, duckdb_date_class_entry);
    duckdb_date_t *date_t = Z_DUCKDB_DATE_P(return_value);
    date_t->date = duckdb_to_date(timestamp_struct.date);
}

PHP_METHOD(DuckDB_Value_Timestamp, getTime)
{
    zval *object = ZEND_THIS;
    duckdb_timestamp_t *timestamp_t;
    duckdb_timestamp_struct timestamp_struct;

    ZEND_PARSE_PARAMETERS_NONE();

    timestamp_t = Z_DUCKDB_TIMESTAMP_P(object);

    timestamp_struct = duckdb_from_timestamp(timestamp_t->timestamp);
    object_init_ex(return_value, duckdb_time_class_entry);
    duckdb_time_t *time_t = Z_DUCKDB_TIME_P(return_value);
    time_t->time = duckdb_to_time(timestamp_struct.time);
}

PHP_METHOD(DuckDB_Value_Date, infinity)
{
    zval *object = ZEND_THIS;
    duckdb_date_t *date_t;

    ZEND_PARSE_PARAMETERS_NONE();

    date_t = Z_DUCKDB_DATE_P(object);

    if (duckdb_is_finite_date(date_t->date))
    {
        RETURN_LONG(PHP_DUCKDB_FINITE);
    }

    if (*&(&date_t->date)->days > 0)
    {
        RETURN_LONG(PHP_DUCKDB_POSITIVE_INFINITY);
    }

    RETURN_LONG(PHP_DUCKDB_NEGATIVE_INFINITY);
}

static duckdb_date_struct get_date_struct_from_date(duckdb_date_t *date)
{
    if (date->date_struct_initialised != true)
    {
        date->date_struct = duckdb_from_date(date->date);
        date->date_struct_initialised = true;
    }
    return date->date_struct;
}

PHP_METHOD(DuckDB_Value_Date, getYear)
{
    zval *object = ZEND_THIS;
    duckdb_date_t *date_t;
    duckdb_date_struct date_struct;

    ZEND_PARSE_PARAMETERS_NONE();

    date_t = Z_DUCKDB_DATE_P(object);

    date_struct = get_date_struct_from_date(date_t);

    RETURN_LONG(date_struct.year);
}

PHP_METHOD(DuckDB_Value_Date, getMonth)
{
    zval *object = ZEND_THIS;
    duckdb_date_t *date_t;
    duckdb_date_struct date_struct;

    ZEND_PARSE_PARAMETERS_NONE();

    date_t = Z_DUCKDB_DATE_P(object);

    date_struct = get_date_struct_from_date(date_t);

    RETURN_LONG(date_struct.month);
}

PHP_METHOD(DuckDB_Value_Date, getDay)
{
    zval *object = ZEND_THIS;
    duckdb_date_t *date_t;
    duckdb_date_struct date_struct;

    ZEND_PARSE_PARAMETERS_NONE();

    date_t = Z_DUCKDB_DATE_P(object);

    date_struct = get_date_struct_from_date(date_t);

    RETURN_LONG(date_struct.day);
}

PHP_METHOD(DuckDB_Value_Date, getDays)
{
    zval *object = ZEND_THIS;
    duckdb_date_t *date_t;

    ZEND_PARSE_PARAMETERS_NONE();

    date_t = Z_DUCKDB_DATE_P(object);

    RETURN_LONG((&date_t->date)->days);
}

static duckdb_time_struct get_time_struct_from_time(duckdb_time_t *time)
{
    if (time->time_struct_initialised != true)
    {
        time->time_struct = duckdb_from_time(time->time);
        time->time_struct_initialised = true;
    }
    return time->time_struct;
}

PHP_METHOD(DuckDB_Value_Time, getHour)
{
    zval *object = ZEND_THIS;
    duckdb_time_t *time_t;
    duckdb_time_struct time_struct;

    ZEND_PARSE_PARAMETERS_NONE();

    time_t = Z_DUCKDB_TIME_P(object);

    time_struct = get_time_struct_from_time(time_t);
    RETURN_LONG(time_struct.hour);
}

PHP_METHOD(DuckDB_Value_Time, getMinutes)
{
    zval *object = ZEND_THIS;
    duckdb_time_t *time_t;
    duckdb_time_struct time_struct;

    ZEND_PARSE_PARAMETERS_NONE();

    time_t = Z_DUCKDB_TIME_P(object);

    time_struct = get_time_struct_from_time(time_t);
    RETURN_LONG(time_struct.min);
}

PHP_METHOD(DuckDB_Value_Time, getSeconds)
{
    zval *object = ZEND_THIS;
    duckdb_time_t *time_t;
    duckdb_time_struct time_struct;

    ZEND_PARSE_PARAMETERS_NONE();

    time_t = Z_DUCKDB_TIME_P(object);

    time_struct = get_time_struct_from_time(time_t);
    RETURN_LONG(time_struct.sec);
}

PHP_METHOD(DuckDB_Value_Time, getMicroseconds)
{
    zval *object = ZEND_THIS;
    duckdb_time_t *time_t;
    duckdb_time_struct time_struct;

    ZEND_PARSE_PARAMETERS_NONE();

    time_t = Z_DUCKDB_TIME_P(object);

    time_struct = get_time_struct_from_time(time_t);
    RETURN_LONG(time_struct.micros);
}

PHP_METHOD(DuckDB_Value_Time, getTotalMicroseconds)
{
    zval *object = ZEND_THIS;
    duckdb_time_t *time_t;

    ZEND_PARSE_PARAMETERS_NONE();

    time_t = Z_DUCKDB_TIME_P(object);

    RETURN_LONG((&time_t->time)->micros);
}

PHP_METHOD(DuckDB_Value_Struct, childCount)
{
    zval *object = ZEND_THIS;
    duckdb_nested_vector_t *nested_vector;

    ZEND_PARSE_PARAMETERS_NONE();

    nested_vector = Z_DUCKDB_NESTED_VECTOR_P(object);

    RETURN_LONG(duckdb_struct_type_child_count(nested_vector->vector->logical_type));
}

PHP_METHOD(DuckDB_Value_Struct, childName)
{
    zval *object = ZEND_THIS;
    duckdb_nested_vector_t *nested_vector;
    zend_long index;

    ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_LONG(index)
    ZEND_PARSE_PARAMETERS_END();

    nested_vector = Z_DUCKDB_NESTED_VECTOR_P(object);

    RETURN_STRING(duckdb_struct_type_child_name(nested_vector->vector->logical_type, index));
}

PHP_METHOD(DuckDB_Value_Struct, getChild)
{
    zval *object = ZEND_THIS;
    duckdb_nested_vector_t *nested_vector;
    duckdb_vector_t *vector_t;
    zend_long index;

    ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_LONG(index)
    ZEND_PARSE_PARAMETERS_END();

    nested_vector = Z_DUCKDB_NESTED_VECTOR_P(object);

    object_init_ex(return_value, duckdb_vector_class_entry);
    vector_t = Z_DUCKDB_VECTOR_P(return_value);

    vector_t->vector = duckdb_struct_vector_get_child(nested_vector->vector->vector, index);
}

PHP_METHOD(DuckDB_Value_Struct, toArray)
{
    zval *object = ZEND_THIS;
    duckdb_nested_vector_t *nested_vector;
    zval data;

    ZEND_PARSE_PARAMETERS_NONE();

    nested_vector = Z_DUCKDB_NESTED_VECTOR_P(object);
    array_init(return_value);
    uint64_t child_size = duckdb_struct_type_child_count(nested_vector->vector->logical_type);

    for (uint64_t i = 0; i < child_size; i++)
    {
        object_init_ex(&data, duckdb_vector_class_entry);
        duckdb_vector_t *vector_t = Z_DUCKDB_VECTOR_P(&data);

        char *name = duckdb_struct_type_child_name(nested_vector->vector->logical_type, i);
        vector_t->vector = duckdb_struct_vector_get_child(nested_vector->vector->vector, i);
        add_assoc_zval(return_value, name, &data);
    }
    return;
}

PHP_RINIT_FUNCTION(duckdb)
{
#if defined(ZTS) && defined(COMPILE_DL_DUCKDB)
    ZEND_TSRMLS_CACHE_UPDATE();
#endif

    return SUCCESS;
}

PHP_MINIT_FUNCTION(duckdb)
{
    duckdb_exception_class_entry = register_class_DuckDB_Exception(zend_ce_exception);

    memcpy(&duckdb_object_handlers, &std_object_handlers, sizeof(zend_object_handlers));
    memcpy(&result_object_handlers, &std_object_handlers, sizeof(zend_object_handlers));
    memcpy(&data_chunk_object_handlers, &std_object_handlers, sizeof(zend_object_handlers));
    memcpy(&vector_object_handlers, &std_object_handlers, sizeof(zend_object_handlers));
    memcpy(&timestamp_object_handlers, &std_object_handlers, sizeof(zend_object_handlers));
    memcpy(&date_object_handlers, &std_object_handlers, sizeof(zend_object_handlers));
    memcpy(&time_object_handlers, &std_object_handlers, sizeof(zend_object_handlers));
    memcpy(&struct_object_handlers, &std_object_handlers, sizeof(zend_object_handlers));

    duckdb_class_entry = register_class_DuckDB_DuckDB();
    duckdb_class_entry->create_object = duckdb_new;
    duckdb_class_entry->default_object_handlers = &duckdb_object_handlers;
    duckdb_object_handlers.offset = XtOffsetOf(duckdb_t, std);
    duckdb_object_handlers.free_obj = duckdb_free_obj;
    duckdb_object_handlers.get_debug_info = duckdb_get_debug_info;

    duckdb_result_class_entry = register_class_DuckDB_Result();
    duckdb_result_class_entry->create_object = duckdb_result_new;
    duckdb_result_class_entry->default_object_handlers = &result_object_handlers;
    result_object_handlers.offset = XtOffsetOf(duckdb_result_t, std);
    result_object_handlers.free_obj = duckdb_result_free_obj;
    result_object_handlers.get_debug_info = duckdb_result_get_debug_info;

    duckdb_data_chunk_class_entry = register_class_DuckDB_DataChunk();
    duckdb_data_chunk_class_entry->create_object = duckdb_data_chunk_new;
    duckdb_data_chunk_class_entry->default_object_handlers = &data_chunk_object_handlers;
    data_chunk_object_handlers.free_obj = duckdb_data_chunk_free_obj;
    data_chunk_object_handlers.offset = XtOffsetOf(duckdb_data_chunk_t, std);

    duckdb_vector_class_entry = register_class_DuckDB_Vector();
    duckdb_vector_class_entry->create_object = duckdb_vector_new;
    duckdb_vector_class_entry->default_object_handlers = &vector_object_handlers;
    vector_object_handlers.free_obj = duckdb_vector_free_obj;
    vector_object_handlers.offset = XtOffsetOf(duckdb_vector_t, std);

    duckdb_timestamp_class_entry = register_class_DuckDB_Value_Timestamp();
    duckdb_timestamp_class_entry->create_object = duckdb_timestamp_new;
    duckdb_timestamp_class_entry->default_object_handlers = &timestamp_object_handlers;
    timestamp_object_handlers.free_obj = duckdb_timestamp_free_obj;
    timestamp_object_handlers.offset = XtOffsetOf(duckdb_timestamp_t, std);

    duckdb_date_class_entry = register_class_DuckDB_Value_Date();
    duckdb_date_class_entry->create_object = duckdb_date_new;
    duckdb_date_class_entry->default_object_handlers = &date_object_handlers;
    date_object_handlers.free_obj = duckdb_date_free_obj;
    date_object_handlers.offset = XtOffsetOf(duckdb_date_t, std);

    duckdb_time_class_entry = register_class_DuckDB_Value_Time();
    duckdb_time_class_entry->create_object = duckdb_time_new;
    duckdb_time_class_entry->default_object_handlers = &time_object_handlers;
    time_object_handlers.free_obj = duckdb_time_free_obj;
    time_object_handlers.offset = XtOffsetOf(duckdb_time_t, std);

    duckdb_struct_class_entry = register_class_DuckDB_Value_Struct();
    duckdb_struct_class_entry->create_object = duckdb_nested_vector_new;
    duckdb_struct_class_entry->default_object_handlers = &struct_object_handlers;
    struct_object_handlers.free_obj = duckdb_nested_vector_free_obj;
    struct_object_handlers.offset = XtOffsetOf(duckdb_nested_vector_t, std);

    return SUCCESS;
}

PHP_MINFO_FUNCTION(duckdb)
{
    php_info_print_table_start();
    php_info_print_table_row(2, "duckdb support", "enabled");
    php_info_print_table_end();
}

zend_module_entry duckdb_module_entry = {
    STANDARD_MODULE_HEADER,
    "duckdb",           /* Extension name */
    ext_functions,      /* zend_function_entry */
    PHP_MINIT(duckdb),  /* PHP_MINIT - Module initialization */
    NULL,               /* PHP_MSHUTDOWN - Module shutdown */
    PHP_RINIT(duckdb),  /* PHP_RINIT - Request initialization */
    NULL,               /* PHP_RSHUTDOWN - Request shutdown */
    PHP_MINFO(duckdb),  /* PHP_MINFO - Module info */
    PHP_DUCKDB_VERSION, /* Version */
    STANDARD_MODULE_PROPERTIES};

#ifdef COMPILE_DL_DUCKDB
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(duckdb)
#endif
