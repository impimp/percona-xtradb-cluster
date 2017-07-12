/*
   Copyright (c) 2012,2013 Monty Program Ab

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; version 2 of the License.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA */
#pragma once

/* C++ standard header files */
#include <string>
#include <vector>

/* MySQL header files */
#include "./sql_string.h"

/* RocksDB includes */
#include "rocksdb/table.h"
#include "rocksdb/utilities/transaction_db.h"

namespace myrocks {

enum RDB_IO_ERROR_TYPE {
  RDB_IO_ERROR_TX_COMMIT,
  RDB_IO_ERROR_DICT_COMMIT,
  RDB_IO_ERROR_BG_THREAD,
  RDB_IO_ERROR_GENERAL,
  RDB_IO_ERROR_LAST
};

const char *get_rdb_io_error_string(const RDB_IO_ERROR_TYPE err_type);

void rdb_handle_io_error(const rocksdb::Status status,
                         const RDB_IO_ERROR_TYPE err_type);

int rdb_normalize_tablename(const std::string &tablename, std::string *str)
    MY_ATTRIBUTE((__nonnull__, __warn_unused_result__));

int rdb_split_normalized_tablename(const std::string &fullname, std::string *db,
                                   std::string *table = nullptr,
                                   std::string *partition = nullptr)
    MY_ATTRIBUTE((__warn_unused_result__));

std::vector<std::string> rdb_get_open_table_names(void);

int rdb_get_table_perf_counters(const char *tablename,
                                Rdb_perf_counters *counters)
    MY_ATTRIBUTE((__nonnull__(2)));

void rdb_get_global_perf_counters(Rdb_perf_counters *counters)
    MY_ATTRIBUTE((__nonnull__(1)));

void rdb_queue_save_stats_request();

/*
  Access to singleton objects.
*/

rocksdb::TransactionDB *rdb_get_rocksdb_db();

class Rdb_cf_manager;
Rdb_cf_manager &rdb_get_cf_manager();

rocksdb::BlockBasedTableOptions &rdb_get_table_options();

class Rdb_dict_manager;
Rdb_dict_manager *rdb_get_dict_manager(void)
    MY_ATTRIBUTE((__warn_unused_result__));

class Rdb_ddl_manager;
Rdb_ddl_manager *rdb_get_ddl_manager(void)
    MY_ATTRIBUTE((__warn_unused_result__));

} // namespace myrocks
