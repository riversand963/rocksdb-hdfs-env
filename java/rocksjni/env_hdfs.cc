// Copyright (c) 2011-present, Facebook, Inc.  All rights reserved.
//  This source code is licensed under both the GPLv2 (found in the
//  COPYING file in the root directory) and Apache 2.0 License
//  (found in the LICENSE.Apache file in the root directory).
//
// This file implements the "bridge" between Java and C++ and enables
// calling c++ ROCKSDB_NAMESPACE::Env methods from Java side.

#include <jni.h>
#include <vector>

#include "portal.h"
#include "rocksdb/env.h"
#include "include/org_rocksdb_Env.h"
#include "include/org_rocksdb_HdfsEnv.h"
#include "include/org_rocksdb_RocksEnv.h"
#include "include/org_rocksdb_RocksMemEnv.h"
#include "include/org_rocksdb_TimedEnv.h"

/*
 * Class:     org_rocksdb_HdfsEnv
 * Method:    createHdfsEnv
 * Signature: (Ljava/lang/String;)J
 */
jlong Java_org_rocksdb_HdfsEnv_createHdfsEnv(
    JNIEnv *env, jclass, jstring jfsname)
{
    jboolean has_exception = JNI_FALSE;
    auto fsname =
        ROCKSDB_NAMESPACE::JniUtil::copyStdString(env, jfsname, &has_exception);
    if (has_exception == JNI_TRUE)
    {
        // exception occurred
        return 0;
    }
    ROCKSDB_NAMESPACE::Env *hdfs_env;
    ROCKSDB_NAMESPACE::Status s =
        ROCKSDB_NAMESPACE::NewHdfsEnv(&hdfs_env, fsname);
    if (!s.ok())
    {
        // error occurred
        ROCKSDB_NAMESPACE::RocksDBExceptionJni::ThrowNew(env, s);
        return 0;
    }
    return reinterpret_cast<jlong>(hdfs_env);
}

/*
 * Class:     org_rocksdb_HdfsEnv
 * Method:    disposeInternal
 * Signature: (J)V
 */
void Java_org_rocksdb_HdfsEnv_disposeInternal(
    JNIEnv *, jobject, jlong jhandle)
{
    auto *e = reinterpret_cast<ROCKSDB_NAMESPACE::Env *>(jhandle);
    assert(e != nullptr);
    delete e;
}
