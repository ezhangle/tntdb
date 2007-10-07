/* 
 * Copyright (C) 2005 Tommi Maekitalo
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

#ifndef TNTDB_IFACE_IROW_H
#define TNTDB_IFACE_IROW_H

#include <cxxtools/refcounted.h>
#include <string>

namespace tntdb
{
  class Value;

  /// common interface for row-types
  class IRow : public cxxtools::RefCounted
  {
    public:
      typedef unsigned size_type;

      virtual size_type size() const = 0;
      virtual Value getValue(size_type field_num) const = 0;
  };
}

#endif // TNTDB_IFACE_IROW_H

