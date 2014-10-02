// Copyright 2014. Gang Bai <me@baigang.net>
#ifndef SRC_LOSS_GRADIENT_H_
#define SRC_LOSS_GRADIENT_H_

#include <lbfgs.h>

namespace admm {

class LossGradient {
 public:
  /** Evaluating the loss function. */
  virtual lbfgsfloatval_t Loss(const lbfgsfloatval_t* x) = 0;

  /** Get the gradient at a specific point x with a step. */
  virtual void Gradient(const lbfgsfloatval_t* x, const int n,
                const lbfgsfloatval_t step, lbfgsfloatval_t* g) = 0;

  inline void SetLBFGSEvaluateFunc(lbfgs_evaluate_t evaluate_func) {
    evaluate_func_ = evaluate_func;
  }
  inline void SetLBFGSProgressFunc(lbfgs_progress_t progress_func) {
    progress_func_ = progress_func;
  }

 protected:
  lbfgs_progress_t progress_func_;
  lbfgs_evaluate_t evaluate_func_;
};

}  // namespace admm

#endif  // SRC_LOSS_GRADIENT_H_

