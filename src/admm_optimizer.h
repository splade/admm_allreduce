// Copyright 2014. Gang Bai <me@baigang.net>
#ifndef SRC_ADMM_OPTIMIZER_H_
#define SRC_ADMM_OPTIMIZER_H_
#include <vector>
#include <lbfgs.h>  // NOLINT

namespace admm {

class ADMMOptimizer {
 public:
  void Run(int num_iterations);

  inline const std::vector<float>& Results() const {
    return z_;
  }

  /** Distributed update of parameter X. */
  virtual void UpdateX() = 0;

  /** Distributed update of dual variable Y. */
  virtual void UpdateY() = 0;

  /** Centralized update of the consensus Z. */
  virtual void UpdateZ() = 0;

  /** Centralized update of the lagrangian multiplier rho. */
  virtual void UpdateRho() = 0;

  explicit ADMMOptimizer(int n)
      : feature_dimension_(n) {}
  virtual ~ADMMOptimizer();

 protected:
  int feature_dimension_;
  std::vector<float> x_;
  std::vector<float> y_;
  std::vector<float> z_;
  float rho_;
  float lambda_;

 private:
  ADMMOptimizer();
  ADMMOptimizer(const ADMMOptimizer&);
  void operator=(const ADMMOptimizer&);
};

}  // namespace admm

#endif  // SRC_ADMM_OPTIMIZER_H_

