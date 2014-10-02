// Copyright 2014 Sina Corp.
// Author: baigang
#include <signal.h>
#include <iostream>  // NOLINT
#include <gflags/gflags.h>  // NOLINT
#include <glog/logging.h>  // NOLINT
#include "sample_set.h"  // NOLINT
#include "admm_optimizer.h"  // NOLINT
#include "lr/admm_lrl2.h"  // NOLINT

DEFINE_bool(use_01_label, false, "Set to use 0/1 label instead of -1/+1.");
DEFINE_string(spanning_tree_server, "127.0.0.1", "IP of ");
DEFINE_int32(num_nodes, 1,
    "Num of computing nodes. Typically num of mappers in Hadoop MR.");  // NOLINT
DEFINE_int32(job_id, 0,
    "Unique id of the current task. Typically the mapred job id.");  // NOLINT
DEFINE_int32(node_id, 0,
    "Unique id of the current node. Typically the last field in the mapper id.");  // NOLINT

int main(int argc, char* argv[]) {
  ::google::InitGoogleLogging(argv[0]);
  ::google::ParseCommandLineFlags(&argc, &argv, true);

  signal(SIGPIPE, SIG_IGN);

  admm::SampleSet sample_set;
  sample_set.set_use_01_label(FLAGS_use_01_label);

  CHECK(sample_set.ParseSamples(std::cin)) << "Parsing examples failed.";

  // ADMM iterations
  // TODO(baigang): Should be specifying the algorithm using cmd
  int feature_dimension = sample_set.Samples()[0].features.size();
  admm::ADMMOptimizer* algo = new admm::lr::ADMMLRL2(
    feature_dimension, &sample_set);

  algo->Run(10);

  LOG(INFO) << "results parameters: ";
  for (int i = 0; i < feature_dimension; ++i) {
    LOG(INFO) << "Dimension (" << i
              << "), weight ("
              << algo->Results()[i]
              << ").";
  }

  return 0;
}


