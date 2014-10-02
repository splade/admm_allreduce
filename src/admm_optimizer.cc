// Copyright 2014. Gang Bai <me@baigang.net>
#include "admm_optimizer.h"  // NOLINT
#include <gflags/gflags.h>

DEFINE_double(lambda, 0.1, "L2 regularization param.");

namespace admm {

void ADMMOptimizer::Run(int num_iterations) {
  // initialization
  z_.assign(feature_dimension_, 0.0);
  y_.assign(feature_dimension_, 0.0);
  rho_ = FLAGS_lambda;

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

