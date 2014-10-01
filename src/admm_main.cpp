// Copyright 2014 Sina Corp.
// Author: baigang
#include <signal.h>
#include <iostream>
#include <gflags/gflags.h>
#include <glog/logging.h>
#include "sample_set.h"

DEFINE_bool(use_01_label, false, "Set to use 0/1 label instead of -1/+1.");
DEFINE_string(spanning_tree_server, "127.0.0.1", "IP of ");

int main(int argc, char* argv[]) {
  ::google::InitGoogleLogging(argv[0]);
  ::google::ParseCommandLineFlags(&argc, &argv, true);

  signal(SIGPIPE, SIG_IGN);

  admm::SampleSet sample_set;
  sample_set.set_use_01_label(FLAGS_use_01_label);

  CHECK(sample_set.ParseSamples(std::cin)) << "Parsing examples failed.";

  // ADMM iterations

  return 0;
}


