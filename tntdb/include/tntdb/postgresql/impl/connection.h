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

#ifndef TNTDB_POSTGRESQL_IMPL_CONNECTION_H
#define TNTDB_POSTGRESQL_IMPL_CONNECTION_H

#include <tntdb/iface/iconnection.h>
#include <libpq-fe.h>

namespace tntdb
{
  namespace postgresql
  {
    class Connection : public IStmtCacheConnection
    {
        PGconn* conn;

      public:
        explicit Connection(const char* conninfo);
        ~Connection();

        void beginTransaction();
        void commitTransaction();
        void rollbackTransaction();

        size_type execute(const std::string& query);
        tntdb::Result select(const std::string& query);
        tntdb::Row selectRow(const std::string& query);
        tntdb::Value selectValue(const std::string& query);
        tntdb::Statement prepare(const std::string& query);

        PGconn* getPGConn() const  { return conn; }
    };

    inline bool isError(const PGresult* res)
    {
      ExecStatusType status = PQresultStatus(res);
      return status != PGRES_COMMAND_OK
          && status != PGRES_TUPLES_OK
          && status != PGRES_COPY_OUT
          && status != PGRES_COPY_IN;
    }

  }
}

#endif // TNTDB_POSTGRESQL_IMPL_CONNECTION_H

