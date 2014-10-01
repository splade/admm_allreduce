#include "admm_lrl2.h"

namespace admm{
namespace lr {

ADMMLRL2::ADMMLRL2(int feature_dimension,
                   const ::admm::SampleSet* sample_set)
    : ADMMOptimizer(feature_dimension)
    , sample_set_(sample_set) {}

ADMMLRL2::~ADMMLRL2() {}

lbfgsfloatval_t ADMMLRL2::Loss(const lbfgsfloatval_t* x, const int n) {
  return 0.0;
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

