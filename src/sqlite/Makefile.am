AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_builddir)/include

sources = connection.cpp connectionmanager.cpp cursor.cpp error.cpp statement.cpp stmtvalue.cpp stmtrow.cpp

if MAKE_SQLITE

driver_LTLIBRARIES = tntdb@abi_current@-sqlite.la

tntdb@abi_current@_sqlite_la_SOURCES = $(sources)
tntdb@abi_current@_sqlite_la_LDFLAGS = -module -version-info @sonumber@ -lsqlite3 @SHARED_LIB_FLAG@
tntdb@abi_current@_sqlite_la_LIBADD = $(top_builddir)/src/libtntdb.la

endif
