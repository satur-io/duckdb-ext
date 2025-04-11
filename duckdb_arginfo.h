/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: b0684019f4b18facf2a88009cf76a8288c260cb0 */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_duckdb_info, 0, 0, IS_VOID, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_DuckDB_DuckDB___construct, 0, 0, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, path, IS_STRING, 1, "null")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_DuckDB_DuckDB_query, 0, 1, DuckDB\\Result, 0)
	ZEND_ARG_TYPE_INFO(0, query, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_DuckDB_Result_columnCount, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_DuckDB_Result_fetchChunk, 0, 0, DuckDB\\DataChunk, 1)
ZEND_END_ARG_INFO()

#define arginfo_class_DuckDB_DataChunk_getSize arginfo_class_DuckDB_Result_columnCount

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_DuckDB_DataChunk_getVector, 0, 1, DuckDB\\Vector, 0)
	ZEND_ARG_TYPE_INFO(0, columnIndex, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_DuckDB_Vector_getData, 0, 1, IS_MIXED, 0)
	ZEND_ARG_TYPE_INFO(0, rowIndex, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_DuckDB_Value_Timestamp_infinity arginfo_class_DuckDB_Result_columnCount

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_DuckDB_Value_Timestamp___toString, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_FUNCTION(duckdb_info);
ZEND_METHOD(DuckDB_DuckDB, __construct);
ZEND_METHOD(DuckDB_DuckDB, query);
ZEND_METHOD(DuckDB_Result, columnCount);
ZEND_METHOD(DuckDB_Result, fetchChunk);
ZEND_METHOD(DuckDB_DataChunk, getSize);
ZEND_METHOD(DuckDB_DataChunk, getVector);
ZEND_METHOD(DuckDB_Vector, getData);
ZEND_METHOD(DuckDB_Value_Timestamp, infinity);
ZEND_METHOD(DuckDB_Value_Timestamp, __toString);

static const zend_function_entry ext_functions[] = {
	ZEND_FE(duckdb_info, arginfo_duckdb_info)
	ZEND_FE_END
};

static const zend_function_entry class_DuckDB_DuckDB_methods[] = {
	ZEND_ME(DuckDB_DuckDB, __construct, arginfo_class_DuckDB_DuckDB___construct, ZEND_ACC_PUBLIC)
	ZEND_ME(DuckDB_DuckDB, query, arginfo_class_DuckDB_DuckDB_query, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static const zend_function_entry class_DuckDB_Result_methods[] = {
	ZEND_ME(DuckDB_Result, columnCount, arginfo_class_DuckDB_Result_columnCount, ZEND_ACC_PUBLIC)
	ZEND_ME(DuckDB_Result, fetchChunk, arginfo_class_DuckDB_Result_fetchChunk, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static const zend_function_entry class_DuckDB_DataChunk_methods[] = {
	ZEND_ME(DuckDB_DataChunk, getSize, arginfo_class_DuckDB_DataChunk_getSize, ZEND_ACC_PUBLIC)
	ZEND_ME(DuckDB_DataChunk, getVector, arginfo_class_DuckDB_DataChunk_getVector, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static const zend_function_entry class_DuckDB_Vector_methods[] = {
	ZEND_ME(DuckDB_Vector, getData, arginfo_class_DuckDB_Vector_getData, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static const zend_function_entry class_DuckDB_Value_Timestamp_methods[] = {
	ZEND_ME(DuckDB_Value_Timestamp, infinity, arginfo_class_DuckDB_Value_Timestamp_infinity, ZEND_ACC_PUBLIC)
	ZEND_ME(DuckDB_Value_Timestamp, __toString, arginfo_class_DuckDB_Value_Timestamp___toString, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static zend_class_entry *register_class_DuckDB_DuckDB(void)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "DuckDB", "DuckDB", class_DuckDB_DuckDB_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_NOT_SERIALIZABLE);

	return class_entry;
}

static zend_class_entry *register_class_DuckDB_Result(void)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "DuckDB", "Result", class_DuckDB_Result_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_NOT_SERIALIZABLE);

	return class_entry;
}

static zend_class_entry *register_class_DuckDB_DataChunk(void)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "DuckDB", "DataChunk", class_DuckDB_DataChunk_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_NOT_SERIALIZABLE);

	return class_entry;
}

static zend_class_entry *register_class_DuckDB_Vector(void)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "DuckDB", "Vector", class_DuckDB_Vector_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_NOT_SERIALIZABLE);

	return class_entry;
}

static zend_class_entry *register_class_DuckDB_Exception(zend_class_entry *class_entry_Exception)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "DuckDB", "Exception", NULL);
	class_entry = zend_register_internal_class_with_flags(&ce, class_entry_Exception, ZEND_ACC_NO_DYNAMIC_PROPERTIES);

	return class_entry;
}

static zend_class_entry *register_class_DuckDB_Value_Timestamp(void)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "DuckDB\\Value", "Timestamp", class_DuckDB_Value_Timestamp_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_NOT_SERIALIZABLE);

	zval const_POSITIVE_INFINITY_value;
	ZVAL_LONG(&const_POSITIVE_INFINITY_value, PHP_DUCKDB_POSITIVE_INFINITY);
	zend_string *const_POSITIVE_INFINITY_name = zend_string_init_interned("POSITIVE_INFINITY", sizeof("POSITIVE_INFINITY") - 1, 1);
	zend_declare_class_constant_ex(class_entry, const_POSITIVE_INFINITY_name, &const_POSITIVE_INFINITY_value, ZEND_ACC_PUBLIC, NULL);
	zend_string_release(const_POSITIVE_INFINITY_name);
	ZEND_ASSERT(PHP_DUCKDB_POSITIVE_INFINITY == 1);

	zval const_NEGATIVE_INFINITY_value;
	ZVAL_LONG(&const_NEGATIVE_INFINITY_value, PHP_DUCKDB_NEGATIVE_INFINITY);
	zend_string *const_NEGATIVE_INFINITY_name = zend_string_init_interned("NEGATIVE_INFINITY", sizeof("NEGATIVE_INFINITY") - 1, 1);
	zend_declare_class_constant_ex(class_entry, const_NEGATIVE_INFINITY_name, &const_NEGATIVE_INFINITY_value, ZEND_ACC_PUBLIC, NULL);
	zend_string_release(const_NEGATIVE_INFINITY_name);
	ZEND_ASSERT(PHP_DUCKDB_NEGATIVE_INFINITY == -1);

	zval const_FINITE_value;
	ZVAL_LONG(&const_FINITE_value, PHP_DUCKDB_FINITE);
	zend_string *const_FINITE_name = zend_string_init_interned("FINITE", sizeof("FINITE") - 1, 1);
	zend_declare_class_constant_ex(class_entry, const_FINITE_name, &const_FINITE_value, ZEND_ACC_PUBLIC, NULL);
	zend_string_release(const_FINITE_name);
	ZEND_ASSERT(PHP_DUCKDB_FINITE == 0);

	return class_entry;
}

static zend_class_entry *register_class_DuckDB_Value_Date(void)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "DuckDB\\Value", "Date", NULL);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, 0);

	return class_entry;
}

static zend_class_entry *register_class_DuckDB_Value_Time(void)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "DuckDB\\Value", "Time", NULL);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, 0);

	return class_entry;
}
