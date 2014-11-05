// Copyright 2014. Gang Bai <me@baigang.net>
#include "admm_optimizer.h"  // NOLINT
#include <gflags/gflags_declare.h>

DECLARE_double(l2_param);

namespace admm {

void ADMMOptimizer::Run(int num_iterations) {
  // initialization
  z_.assign(feature_dimension_, 0.0);
  y_.assign(feature_dimension_, 0.0);
  rho_ = FLAGS_l2_param;

  // TODO(baigang): early stopping
  while (num_iterations --) {
    UpdateX();
    UpdateZ();
    UpdateRho();
    UpdateY();
  }
}

ADMMOptimizer::~ADMMOptimizer() {
}

}  // namespace admm

