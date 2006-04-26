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

#ifndef TNTDB_POSTGRESQL_IMPL_CURSOR_H
#define TNTDB_POSTGRESQL_IMPL_CURSOR_H

#include <tntdb/iface/icursor.h>
#include <tntdb/postgresql/impl/statement.h>
#include <tntdb/bits/statement.h>
#include <tntdb/bits/result.h>

namespace tntdb
{
  namespace postgresql
  {
    class Cursor : public ICursor
    {
        tntdb::Statement tntdbStmt;
        Statement* stmt;

        std::string cursorName;
        tntdb::Result currentResult;
        unsigned currentRow;

        unsigned fetchSize;

      public:
        Cursor(Statement* statement);
        ~Cursor();

        // method for ICursor
        Row fetch();

        // specific methods
        PGconn* getPGConn()            { return stmt->getPGConn(); }

        /**
         * Data is fetched in blocks. The fetchsize specifies, how many blocks
         * are fetched at once. This is fully transparent to the user, so there
         * is normally no need to change the default value, which is 100.
         */
        void setFetchSize(unsigned fs)  { fetchSize = fs; }
        unsigned getFetchSize() const   { return fetchSize; }
    };
  }
}

#endif // TNTDB_POSTGRESQL_IMPL_CURSOR_H

