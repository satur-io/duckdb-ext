dnl Autotools config.m4 for PHP extension duckdb

dnl Comments in this file start with the string 'dnl' (discard to next line).
dnl Remove where necessary.

dnl Otherwise use the '--enable-duckdb' configure option:
PHP_ARG_ENABLE([duckdb],
  [whether to enable duckdb support],
  [AS_HELP_STRING([--enable-duckdb],
    [Enable duckdb support])],
  [no])

AS_VAR_IF([PHP_DUCKDB], [no],, [

  AC_DEFINE([HAVE_DUCKDB], [1],
    [Define to 1 if the PHP extension 'duckdb' is available.])

  PHP_ADD_INCLUDE(lib)

  PHP_ADD_LIBRARY_WITH_PATH(duckdb, lib, DUCKDB_SHARED_LIBADD)
  PHP_SUBST(DUCKDB_SHARED_LIBADD)

  PHP_NEW_EXTENSION([duckdb],
    [duckdb.c],
    [$ext_shared],,
    [-DZEND_ENABLE_STATIC_TSRMLS_CACHE=1])
])
