#ifndef _ADMM_ADMM_OPTIMIZER_
#define _ADMM_ADMM_OPTIMIZER_
#include <vector>
#include <lbfgs.h>

namespace admm {

class ADMMOptimizer {
 public:

  virtual void Run(int num_iterations);

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
  std::vector<float> rho_;

 private:
  ADMMOptimizer();
  ADMMOptimizer(const ADMMOptimizer&);
  void operator=(const ADMMOptimizer&);
};

}  // namespace admm

#endif  // _ADMM_ADMM_OPTIMIZER_

