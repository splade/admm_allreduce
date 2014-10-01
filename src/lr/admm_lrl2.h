#ifndef _ADMM_LR_LRL2ADMM_H_
#define _ADMM_LR_LRL2ADMM_H_

#include "../admm_optimizer.h"
#include "../loss_gradient.h"
#include "../sample_set.h"

namespace admm {
namespace lr {

/** @class ADMM optimizer for logistic regression with L2 normalization.
 * The loss function for ADMM LR is
 * $$\frac{1}{m} \sum_{i=1}^{m} \log(1+\exp(-y_i* \mathbf{w} \mathbf{x}_i)) + \lambda{\|\mathbf{w}\|}_2^2$$
 *
 */
class ADMMLRL2
    : public LossGradient
    , public ADMMOptimizer {
 public:
  virtual lbfgsfloatval_t Loss(const lbfgsfloatval_t* x, const int n);
  virtual void Gradient(const lbfgsfloatval_t* x, const int n,
                const lbfgsfloatval_t step, lbfgsfloatval_t* g);

  /** for callback in lbfgs */
  static lbfgsfloatval_t Evaluate(void *instance,
                                  const lbfgsfloatval_t *x,
                                  lbfgsfloatval_t *g,
                                  const int n,
                                  const lbfgsfloatval_t step);

  /** for callback in lbfgs */
  static int Progress(void *instance,
                      const lbfgsfloatval_t *x,
                      const lbfgsfloatval_t *g,
                      const lbfgsfloatval_t fx,
                      const lbfgsfloatval_t xnorm,
                      const lbfgsfloatval_t gnorm,
                      const lbfgsfloatval_t step,
                      int n, int k, int ls);

  inline float lambda() const {return lambda_;}
  void set_lambda(float lbd) {lambda_ = lbd;}

  virtual void UpdateX();
  virtual void UpdateY();
  virtual void UpdateZ();
  virtual void UpdateRho();

  ADMMLRL2(int feature_dimension,
           const ::admm::SampleSet* sample_set);
  virtual ~ADMMLRL2();
 protected:
  float lambda_;
  const ::admm::SampleSet* sample_set_;

 private:
  ADMMLRL2();
  ADMMLRL2(const ADMMLRL2&);
  void operator= (const ADMMLRL2&);
};

}  // namespace lr
}  // namespace admm

#endif  // _ADMM_LR_LRL2ADMM_H_

