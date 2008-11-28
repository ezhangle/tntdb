/* 
 * Copyright (C) 2007 Tommi Maekitalo
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef TNTDB_ORACLE_CONNECTION_H
#define TNTDB_ORACLE_CONNECTION_H

#include <tntdb/iface/iconnection.h>
#include <oci.h>

namespace tntdb
{
  namespace oracle
  {
    class Connection : public IStmtCacheConnection
    {
        OCIEnv*     envhp;   /* the environment handle */
        OCIServer*  srvhp;   /* the server handle */
        OCIError*   errhp;   /* the error handle */
        OCISession* usrhp;   /* user session handle */
        OCISvcCtx*  svchp;   /* the service handle */
        tntdb::Statement pingStmt;

        void logon(const std::string& dblink, const std::string& user, const std::string& password);

        unsigned transactionActive;

      public:
        void checkError(sword ret, const char* function = 0) const;

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
        bool ping();

        OCIEnv* getEnvHandle() const        { return envhp; }
        OCIError* getErrorHandle() const    { return errhp; }
        OCIServer* getSrvHandle() const     { return srvhp; }
        OCISvcCtx* getSvcCtxHandle() const  { return svchp; }
        bool isTransactionActive() const    { return transactionActive > 0; }
    };

  }
}

#endif // TNTDB_ORACLE_CONNECTION_H

