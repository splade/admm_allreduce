#include <cmath>
#include <vector>
#include "admm_lrl2.h"

namespace admm{
namespace lr {

ADMMLRL2::ADMMLRL2(int feature_dimension,
                   const ::admm::SampleSet* sample_set)
    : ADMMOptimizer(feature_dimension)
    , sample_set_(sample_set) {}

ADMMLRL2::~ADMMLRL2() {}


lbfgsfloatval_t ADMMLRL2::Loss(const lbfgsfloatval_t* x, const int n) {
  const std::vector<SampleSet::Sample>& samples = sample_set_->Samples();
  float loss = 0.0;
  for (std::vector<SampleSet::Sample>::const_iterator cit = samples.begin();
       cit != samples.end(); ++cit) {
    float dot_product = 0.0;
    const lbfgsfloatval_t* cur = x;
    for (std::vector<float>::const_iterator fit = cit->features.begin();
         fit != cit->features.end(); ++fit, ++cur) {
      dot_product += (*fit) * (*cur);
    }
    loss += std::log(1.0 + std::exp(- cit->label * dot_product));
  }

  float rho_dot_residual = 0.0;
  for (int i = 0; i < n; ++i) {
    rho_dot_residual += rho_[i] * (x[i] - z_[i] + y_[i]);
  }
  loss += 0.5 * rho_dot_residual;
  return loss;
}

void ADMMLRL2::Gradient(const lbfgsfloatval_t* x, const int n,
                const lbfgsfloatval_t step, lbfgsfloatval_t* g) {
  
}


void ADMMLRL2::UpdateX() {

}

void ADMMLRL2::UpdateY() {
}

void ADMMLRL2::UpdateZ() {
}

void ADMMLRL2::UpdateRho() {
}

}  // namespace lr
}  // namespace admm

