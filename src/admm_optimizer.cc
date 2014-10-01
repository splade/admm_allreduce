#include "admm_optimizer.h"

namespace admm {

void ADMMOptimizer::Run(int num_iterations) {

  // initialization
  z_.assign(feature_dimension_, 0.0);
  y_.assign(feature_dimension_, 0.0);
  rho_.assign(feature_dimension_, 0.1);

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

