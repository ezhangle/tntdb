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

#ifndef TNTDB_MYSQL_BINDUTILS_H
#define TNTDB_MYSQL_BINDUTILS_H

#include <mysql.h>
#include <string>

namespace tntdb
{
  class Date;
  class Time;
  class Datetime;

  namespace mysql
  {
    void setNull(MYSQL_BIND& value);
    void setBool(MYSQL_BIND& value, bool data);
    void setInt(MYSQL_BIND& value, int data);
    void setUnsigned(MYSQL_BIND& value, unsigned data);
    void setFloat(MYSQL_BIND& value, float data);
    void setDouble(MYSQL_BIND& value, double data);
    void setChar(MYSQL_BIND& value, char data);
    void setString(MYSQL_BIND& value, unsigned long& length, const char* data);
    void setString(MYSQL_BIND& value, unsigned long& length, const std::string& data);
    void setDate(MYSQL_BIND& value, const Date& data);
    void setTime(MYSQL_BIND& value, const Time& data);
    void setDatetime(MYSQL_BIND& value, const Datetime& data);

    bool         isNull(const MYSQL_BIND& value);
    bool         getBool(const MYSQL_BIND& value);
    int          getInt(const MYSQL_BIND& value);
    unsigned     getUnsigned(const MYSQL_BIND& value);
    long         getLong(const MYSQL_BIND& value);
    float        getFloat(const MYSQL_BIND& value);
    double       getDouble(const MYSQL_BIND& value);
    char         getChar(const MYSQL_BIND& value);
    std::string  getString(const MYSQL_BIND& value);
    Date         getDate(const MYSQL_BIND& value);
    Time         getTime(const MYSQL_BIND& value);
    Datetime     getDatetime(const MYSQL_BIND& value);

    void transferValue(MYSQL_BIND& fromValue, MYSQL_BIND& toValue,
                       bool doRelease = true);
    void copyValue(const MYSQL_BIND& fromValue, MYSQL_BIND& toValue,
                   bool doRelease = true);
    void refValue(const MYSQL_BIND& fromValue, MYSQL_BIND& toValue,
                  bool doRelease = true);
    void releaseValue(MYSQL_BIND& value);

    void release(MYSQL_BIND& bind);
    void reserve(MYSQL_BIND& bind, unsigned long size);
    void reserveKeep(MYSQL_BIND& bind, unsigned long size);

    template <typename c_type>
    void setValue(MYSQL_BIND& bind, c_type value, enum_field_types mysql_type)
    {
      reserve(bind, sizeof(c_type));
      *static_cast<c_type*>(bind.buffer) = value;
      bind.buffer_type = mysql_type;
      bind.is_null = 0;
    }

  }
}

#endif // TNTDB_MYSQL_BINDUTILS_H

