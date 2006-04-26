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

#include <tntdb/postgresql/impl/result.h>
#include <tntdb/postgresql/impl/resultrow.h>
#include <tntdb/row.h>
#include <cxxtools/log.h>

log_define("tntdb.postgresql.result")

namespace tntdb
{
  namespace postgresql
  {
    Result::Result(const tntdb::Connection& c, PGresult* r)
      : conn(c),
        result(r)
    {
      log_debug("postgresql-result " << r);
    }

    Result::~Result()
    {
      if (result)
      {
        log_debug("PQclear(" << result << ')');
        ::PQclear(result);
      }
    }

    Row Result::getRow(size_type tup_num) const
    {
      return Row(new ResultRow(const_cast<Result*>(this), tup_num));
    }

    Result::size_type Result::size() const
    {
      log_debug("PQntuples(" << result << ')');
      return ::PQntuples(result);
    }

    Result::size_type Result::getFieldCount() const
    {
      log_debug("PQnfields(" << result << ')');
      return ::PQnfields(result);
    }
  }
}
