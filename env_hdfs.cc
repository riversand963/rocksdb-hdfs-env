//  Copyright (c) 2021-present, Facebook, Inc.  All rights reserved.
//  This source code is licensed under both the GPLv2 (found in the
//  COPYING file in the root directory) and Apache 2.0 License
//  (found in the LICENSE.Apache file in the root directory).

#include "env_hdfs.h"

#include <rocksdb/utilities/object_registry.h>

#include "env_hdfs_impl.h"

namespace ROCKSDB_NAMESPACE {

#ifndef ROCKSDB_LITE

extern "C" FactoryFunc<Env> hdfs_reg;

FactoryFunc<Env> hdfs_reg =
    ObjectLibrary::Default()->Register<Env>(
        "hdfs://.*",
        [](const std::string& fsname, std::unique_ptr<Env>* env,
           std::string* /* errmsg */) {
          *env = NewHdfsEnv(fsname);
          return env->get();
        });

#endif  // ROCKSDB_LITE

// The factory method for creating an HDFS Env
std::unique_ptr<Env>
NewHdfsEnv(const std::string& fsname) {
  return std::unique_ptr<Env>(new HdfsEnv(fsname));
}


}  // namespace ROCKSDB_NAMESPACE
