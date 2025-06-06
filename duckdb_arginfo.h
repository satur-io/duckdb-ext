/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 58b04ffa7fa6c4c97ce914d5c24f61290743782d */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_duckdb_info, 0, 0, IS_VOID, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_DuckDB_DuckDB___construct, 0, 0, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, path, IS_STRING, 1, "null")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_TYPE_MASK_EX(arginfo_class_DuckDB_DuckDB_query, 0, 1, DuckDB\\Result, MAY_BE_BOOL)
	ZEND_ARG_TYPE_INFO(0, query, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_DuckDB_DuckDB_prepare, 0, 1, DuckDB\\PreparedStatement, 0)
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

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_DuckDB_PreparedStatement_bindParam, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, param, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_DuckDB_PreparedStatement_execute, 0, 0, DuckDB\\Result, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_DuckDB_Value_Timestamp_infinity arginfo_class_DuckDB_Result_columnCount

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_DuckDB_Value_Timestamp_getDate, 0, 0, DuckDB\\Value\\Date, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_DuckDB_Value_Timestamp_getTime, 0, 0, DuckDB\\Value\\Time, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_DuckDB_Value_Timestamp___toString, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_DuckDB_Value_Date_infinity arginfo_class_DuckDB_Result_columnCount

#define arginfo_class_DuckDB_Value_Date_getYear arginfo_class_DuckDB_Result_columnCount

#define arginfo_class_DuckDB_Value_Date_getMonth arginfo_class_DuckDB_Result_columnCount

#define arginfo_class_DuckDB_Value_Date_getDay arginfo_class_DuckDB_Result_columnCount

#define arginfo_class_DuckDB_Value_Date_getDays arginfo_class_DuckDB_Result_columnCount

#define arginfo_class_DuckDB_Value_Date___toString arginfo_class_DuckDB_Value_Timestamp___toString

#define arginfo_class_DuckDB_Value_Time_getTotalMicroseconds arginfo_class_DuckDB_Result_columnCount

#define arginfo_class_DuckDB_Value_Time_getHour arginfo_class_DuckDB_Result_columnCount

#define arginfo_class_DuckDB_Value_Time_getMinutes arginfo_class_DuckDB_Result_columnCount

#define arginfo_class_DuckDB_Value_Time_getSeconds arginfo_class_DuckDB_Result_columnCount

#define arginfo_class_DuckDB_Value_Time_getMicroseconds arginfo_class_DuckDB_Result_columnCount

#define arginfo_class_DuckDB_Value_Time___toString arginfo_class_DuckDB_Value_Timestamp___toString

#define arginfo_class_DuckDB_Value_Struct_childCount arginfo_class_DuckDB_Result_columnCount

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_DuckDB_Value_Struct_childName, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_DuckDB_Value_Struct_getChild, 0, 1, DuckDB\\Vector, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_DuckDB_Value_Struct_toArray, 0, 0, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_DuckDB_Value_Struct___toString arginfo_class_DuckDB_Value_Timestamp___toString

ZEND_FUNCTION(duckdb_info);
ZEND_METHOD(DuckDB_DuckDB, __construct);
ZEND_METHOD(DuckDB_DuckDB, query);
ZEND_METHOD(DuckDB_DuckDB, prepare);
ZEND_METHOD(DuckDB_Result, columnCount);
ZEND_METHOD(DuckDB_Result, fetchChunk);
ZEND_METHOD(DuckDB_DataChunk, getSize);
ZEND_METHOD(DuckDB_DataChunk, getVector);
ZEND_METHOD(DuckDB_Vector, getData);
ZEND_METHOD(DuckDB_PreparedStatement, bindParam);
ZEND_METHOD(DuckDB_PreparedStatement, execute);
ZEND_METHOD(DuckDB_Value_Timestamp, infinity);
ZEND_METHOD(DuckDB_Value_Timestamp, getDate);
ZEND_METHOD(DuckDB_Value_Timestamp, getTime);
ZEND_METHOD(DuckDB_Value_Timestamp, __toString);
ZEND_METHOD(DuckDB_Value_Date, infinity);
ZEND_METHOD(DuckDB_Value_Date, getYear);
ZEND_METHOD(DuckDB_Value_Date, getMonth);
ZEND_METHOD(DuckDB_Value_Date, getDay);
ZEND_METHOD(DuckDB_Value_Date, getDays);
ZEND_METHOD(DuckDB_Value_Date, __toString);
ZEND_METHOD(DuckDB_Value_Time, getTotalMicroseconds);
ZEND_METHOD(DuckDB_Value_Time, getHour);
ZEND_METHOD(DuckDB_Value_Time, getMinutes);
ZEND_METHOD(DuckDB_Value_Time, getSeconds);
ZEND_METHOD(DuckDB_Value_Time, getMicroseconds);
ZEND_METHOD(DuckDB_Value_Time, __toString);
ZEND_METHOD(DuckDB_Value_Struct, childCount);
ZEND_METHOD(DuckDB_Value_Struct, childName);
ZEND_METHOD(DuckDB_Value_Struct, getChild);
ZEND_METHOD(DuckDB_Value_Struct, toArray);
ZEND_METHOD(DuckDB_Value_Struct, __toString);

static const zend_function_entry ext_functions[] = {
	ZEND_FE(duckdb_info, arginfo_duckdb_info)
	ZEND_FE_END
};

static const zend_function_entry class_DuckDB_DuckDB_methods[] = {
	ZEND_ME(DuckDB_DuckDB, __construct, arginfo_class_DuckDB_DuckDB___construct, ZEND_ACC_PUBLIC)
	ZEND_ME(DuckDB_DuckDB, query, arginfo_class_DuckDB_DuckDB_query, ZEND_ACC_PUBLIC)
	ZEND_ME(DuckDB_DuckDB, prepare, arginfo_class_DuckDB_DuckDB_prepare, ZEND_ACC_PUBLIC)
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

static const zend_function_entry class_DuckDB_PreparedStatement_methods[] = {
	ZEND_ME(DuckDB_PreparedStatement, bindParam, arginfo_class_DuckDB_PreparedStatement_bindParam, ZEND_ACC_PUBLIC)
	ZEND_ME(DuckDB_PreparedStatement, execute, arginfo_class_DuckDB_PreparedStatement_execute, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static const zend_function_entry class_DuckDB_Value_Timestamp_methods[] = {
	ZEND_ME(DuckDB_Value_Timestamp, infinity, arginfo_class_DuckDB_Value_Timestamp_infinity, ZEND_ACC_PUBLIC)
	ZEND_ME(DuckDB_Value_Timestamp, getDate, arginfo_class_DuckDB_Value_Timestamp_getDate, ZEND_ACC_PUBLIC)
	ZEND_ME(DuckDB_Value_Timestamp, getTime, arginfo_class_DuckDB_Value_Timestamp_getTime, ZEND_ACC_PUBLIC)
	ZEND_ME(DuckDB_Value_Timestamp, __toString, arginfo_class_DuckDB_Value_Timestamp___toString, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static const zend_function_entry class_DuckDB_Value_Date_methods[] = {
	ZEND_ME(DuckDB_Value_Date, infinity, arginfo_class_DuckDB_Value_Date_infinity, ZEND_ACC_PUBLIC)
	ZEND_ME(DuckDB_Value_Date, getYear, arginfo_class_DuckDB_Value_Date_getYear, ZEND_ACC_PUBLIC)
	ZEND_ME(DuckDB_Value_Date, getMonth, arginfo_class_DuckDB_Value_Date_getMonth, ZEND_ACC_PUBLIC)
	ZEND_ME(DuckDB_Value_Date, getDay, arginfo_class_DuckDB_Value_Date_getDay, ZEND_ACC_PUBLIC)
	ZEND_ME(DuckDB_Value_Date, getDays, arginfo_class_DuckDB_Value_Date_getDays, ZEND_ACC_PUBLIC)
	ZEND_ME(DuckDB_Value_Date, __toString, arginfo_class_DuckDB_Value_Date___toString, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static const zend_function_entry class_DuckDB_Value_Time_methods[] = {
	ZEND_ME(DuckDB_Value_Time, getTotalMicroseconds, arginfo_class_DuckDB_Value_Time_getTotalMicroseconds, ZEND_ACC_PUBLIC)
	ZEND_ME(DuckDB_Value_Time, getHour, arginfo_class_DuckDB_Value_Time_getHour, ZEND_ACC_PUBLIC)
	ZEND_ME(DuckDB_Value_Time, getMinutes, arginfo_class_DuckDB_Value_Time_getMinutes, ZEND_ACC_PUBLIC)
	ZEND_ME(DuckDB_Value_Time, getSeconds, arginfo_class_DuckDB_Value_Time_getSeconds, ZEND_ACC_PUBLIC)
	ZEND_ME(DuckDB_Value_Time, getMicroseconds, arginfo_class_DuckDB_Value_Time_getMicroseconds, ZEND_ACC_PUBLIC)
	ZEND_ME(DuckDB_Value_Time, __toString, arginfo_class_DuckDB_Value_Time___toString, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static const zend_function_entry class_DuckDB_Value_Struct_methods[] = {
	ZEND_ME(DuckDB_Value_Struct, childCount, arginfo_class_DuckDB_Value_Struct_childCount, ZEND_ACC_PUBLIC)
	ZEND_ME(DuckDB_Value_Struct, childName, arginfo_class_DuckDB_Value_Struct_childName, ZEND_ACC_PUBLIC)
	ZEND_ME(DuckDB_Value_Struct, getChild, arginfo_class_DuckDB_Value_Struct_getChild, ZEND_ACC_PUBLIC)
	ZEND_ME(DuckDB_Value_Struct, toArray, arginfo_class_DuckDB_Value_Struct_toArray, ZEND_ACC_PUBLIC)
	ZEND_ME(DuckDB_Value_Struct, __toString, arginfo_class_DuckDB_Value_Struct___toString, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static void register_duckdb_symbols(int module_number)
{
	REGISTER_LONG_CONSTANT("DuckDB\\Value\\POSITIVE_INFINITY", PHP_DUCKDB_POSITIVE_INFINITY, CONST_PERSISTENT);
	ZEND_ASSERT(PHP_DUCKDB_POSITIVE_INFINITY == 1);
	REGISTER_LONG_CONSTANT("DuckDB\\Value\\NEGATIVE_INFINITY", PHP_DUCKDB_NEGATIVE_INFINITY, CONST_PERSISTENT);
	ZEND_ASSERT(PHP_DUCKDB_NEGATIVE_INFINITY == -1);
	REGISTER_LONG_CONSTANT("DuckDB\\Value\\FINITE", PHP_DUCKDB_FINITE, CONST_PERSISTENT);
	ZEND_ASSERT(PHP_DUCKDB_FINITE == 0);
}

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

static zend_class_entry *register_class_DuckDB_PreparedStatement(void)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "DuckDB", "PreparedStatement", class_DuckDB_PreparedStatement_methods);
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

	return class_entry;
}

static zend_class_entry *register_class_DuckDB_Value_Date(void)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "DuckDB\\Value", "Date", class_DuckDB_Value_Date_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_NOT_SERIALIZABLE);

	return class_entry;
}

static zend_class_entry *register_class_DuckDB_Value_Time(void)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "DuckDB\\Value", "Time", class_DuckDB_Value_Time_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_NOT_SERIALIZABLE);

	return class_entry;
}

static zend_class_entry *register_class_DuckDB_Value_Struct(void)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "DuckDB\\Value", "Struct", class_DuckDB_Value_Struct_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, 0);

	return class_entry;
}
