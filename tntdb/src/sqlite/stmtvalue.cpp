/* 
   Copyright (C) 2005 Tommi Maekitalo

This file is part of tntdb.

Tntdb is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

Tntdb is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with tntdb; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330,
Boston, MA  02111-1307  USA
*/

#include <tntdb/sqlite/impl/stmtvalue.h>
#include <tntdb/date.h>
#include <tntdb/time.h>
#include <tntdb/datetime.h>
#include <cxxtools/log.h>

log_define("tntdb.sqlite.stmtvalue");

namespace tntdb
{
  namespace sqlite
  {
    bool StmtValue::isNull() const
    {
      log_debug("sqlite3_column_type(" << getStmt() << ", " << iCol << ')');
      return ::sqlite3_column_type(getStmt(), iCol) == SQLITE_NULL;
    }

    bool StmtValue::getBool() const
    {
      return getInt() != 0;
    }

    int StmtValue::getInt() const
    {
      log_debug("sqlite3_column_int(" << getStmt() << ", " << iCol << ')');
      return ::sqlite3_column_int(getStmt(), iCol);
    }

    unsigned StmtValue::getUnsigned() const
    {
      log_debug("possible loss of data in conversion from int to unsigned");
      return static_cast<unsigned>(getInt());
    }

    float StmtValue::getFloat() const
    {
      return static_cast<float>(getInt());
    }

    double StmtValue::getDouble() const
    {
      log_debug("sqlite3_column_double(" << getStmt() << ", " << iCol << ')');
      return ::sqlite3_column_double(getStmt(), iCol);
    }

    char StmtValue::getChar() const
    {
      log_debug("sqlite3_column_text(" << getStmt() << ", " << iCol << ')');
      const unsigned char* ret = ::sqlite3_column_text(getStmt(), iCol);
      return static_cast<char>(*ret);
    }

    std::string StmtValue::getString() const
    {
      log_debug("sqlite3_column_bytes(" << getStmt() << ", " << iCol << ')');
      int bytes = ::sqlite3_column_bytes(getStmt(), iCol);
      log_debug("sqlite3_column_text(" << getStmt() << ", " << iCol << ')');
      const unsigned char* ret = ::sqlite3_column_text(getStmt(), iCol);
      return std::string(reinterpret_cast<const char*>(ret), bytes);
    }

    Date StmtValue::getDate() const
    {
      std::string str = getString();
      return Date::fromIso(str);
    }

    Time StmtValue::getTime() const
    {
      std::string str = getString();
      return Time::fromIso(str);
    }

    Datetime StmtValue::getDatetime() const
    {
      std::string str = getString();
      return Datetime::fromIso(str);
    }

  }
}
