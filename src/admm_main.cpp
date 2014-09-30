// Copyright 2014 Sina Corp.
// Author: baigang
#include <signal.h>
#include <gflags/gflags.h>
#include <glog/logging.h>

int main(int argc, char* argv[]) {
  ::google::InitGoogleLogging(argv[0]);
  ::google::ParseCommandLineFlags(&argc, &argv, true);

  signal(SIGPIPE, SIG_IGN);

  
  return 0;
}


