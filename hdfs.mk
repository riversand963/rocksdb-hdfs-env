hdfs_SOURCES = env_hdfs.cc env_hdfs_impl.cc
hdfs_HEADERS = env_hdfs.h env_hdfs_impl.h
hdfs_LDFLAGS = -lhdfs -u hdfs_reg
