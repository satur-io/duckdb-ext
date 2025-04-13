#include <duckdb.h>
#include <zend_types.h>

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

typedef struct duckdb_prepared_statement_t
{
    duckdb_prepared_statement *stmt;
    zend_object std;
} duckdb_prepared_statement_t;

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
    bool initialised;
    uint64_t row_index;
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

static inline duckdb_prepared_statement_t *prepared_statement_t_from_obj(zend_object *obj)
{
    return (duckdb_prepared_statement_t *)((char *)(obj)-XtOffsetOf(duckdb_prepared_statement_t, std));
}
#define Z_PREPARED_STATEMENT_P(zv) prepared_statement_t_from_obj(Z_OBJ_P(zv))

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
