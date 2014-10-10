// Copyright 2014. Gang Bai <me@baigang.net>
#ifndef SRC_LOSS_GRADIENT_H_
#define SRC_LOSS_GRADIENT_H_

#include <lbfgs.h>

namespace admm {

class LossGradient {
 public:
  /** Evaluating the loss function and the gradient
   *  at a specific point x with a step.
   */
  virtual lbfgsfloatval_t LossAndGradient(const lbfgsfloatval_t* x,
    const int n, const lbfgsfloatval_t step, lbfgsfloatval_t* g) = 0;

 protected:
};

}  // namespace admm

#endif  // SRC_LOSS_GRADIENT_H_

