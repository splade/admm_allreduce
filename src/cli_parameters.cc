#include <gflags/gflags.h>  // NOLINT


DEFINE_string(spanning_tree_server, "127.0.0.1", "IP of ");
DEFINE_int32(num_nodes, 1,
    "Num of computing nodes. Typically num of mappers in Hadoop MR.");  // NOLINT
DEFINE_int32(job_id, 0,
    "Unique id of the current task. Typically the mapred job id.");  // NOLINT
DEFINE_int32(node_id, 0,
    "Unique id of the current node. Typically the last field in the mapper id.");  // NOLINT

DEFINE_bool(use_01_label, false, "Set to use 0/1 label instead of -1/+1.");
DEFINE_double(l2_param, 0.1, "L2 regularization param.");


