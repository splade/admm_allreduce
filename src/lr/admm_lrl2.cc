// Copyright 2014. Gang Bai <me@baigang.net>
#include <cmath>
#include <vector>
#include <allreduce.h>  // NOLINT
#include <gflags/gflags.h>  // NOLINT
#include <glog/logging.h>  // NOLINT
#include "admm_lrl2.h"  // NOLINT


DECLARE_int32(num_nodes);
DECLARE_int32(job_id);
DECLARE_int32(node_id);
DECLARE_string(spanning_tree_server);

namespace admm {
namespace lr {

ADMMLRL2::ADMMLRL2(int feature_dimension,
                   const ::admm::SampleSet* sample_set)
  : ADMMOptimizer(feature_dimension)
  , sample_set_(sample_set) {}

ADMMLRL2::~ADMMLRL2() {}


lbfgsfloatval_t ADMMLRL2::LossAndGradient(const lbfgsfloatval_t* x, const int n,
    const lbfgsfloatval_t step, lbfgsfloatval_t* g) {
  const std::vector<SampleSet::Sample>& samples = sample_set_->Samples();
  float loss = 0.0;
  float gradient_factor = 0.0;
  for (std::vector<SampleSet::Sample>::const_iterator cit = samples.begin();
       cit != samples.end(); ++cit) {
    float dot_product = 0.0;
    const lbfgsfloatval_t* cur = x;
    for (std::vector<float>::const_iterator fit = cit->features.begin();
         fit != cit->features.end(); ++fit, ++cur) {
      dot_product += (*fit) * (*cur);
    }
    float exp = 1.0 + std::exp(- cit->label * dot_product);
    loss += std::log(exp);
    gradient_factor += - cit->label * (1.0 - 1.0/exp);
  }
  float num_samples = static_cast<float>(samples.size());
  loss /= num_samples;
  gradient_factor /= num_samples;

  float rho_dot_residual = 0.0;
  for (int i = 0; i < n; ++i) {
    rho_dot_residual += rho_ * (x[i] - z_[i] + y_[i]);
    g[i] = x[i] * gradient_factor;
  }
  loss += 0.5 * rho_dot_residual;
  return loss;
}

void ADMMLRL2::UpdateX() {
  // carry out lbfgs here
  lbfgs_parameter_t lbfgs_parameter;
  lbfgs_parameter_init(&lbfgs_parameter);
  lbfgs_parameter.past = 1;
  lbfgs_parameter.delta = 1e-4;
  lbfgs_parameter.max_iterations = 50;
  lbfgs_parameter.orthantwise_c = 0.2;

  lbfgsfloatval_t final_fx = 0.0;
  lbfgsfloatval_t* x = lbfgs_malloc(feature_dimension_);
  for (int i = 0; i < feature_dimension_; ++i) {
    x[i] = z_[i];
  }
  int ret = lbfgs(feature_dimension_,
                  x, &final_fx,
                  ADMMLRL2::Evaluate,
                  ADMMLRL2::Progress,
                  this,
                  &lbfgs_parameter);
  if (ret != 0) {
    LOG(ERROR) << "lbfgs routine return code is " << ret;
  }
  lbfgs_free(x);
}

void ADMMLRL2::UpdateY() {
  // simply update the dual variables
  for (std::size_t i = 0; i < y_.size(); ++i) {
    y_[i] += x_[i] - z_[i];
  }
}

namespace {
void add_float(float& c1, const float& c2) {
  c1 += c2;
}
}  // unnamed namespace

void ADMMLRL2::UpdateZ() {
  // TODO(baigang):
  // get avg using all reduce
  node_socks socks;
  std::vector<float> avg_x = x_;
  all_reduce<float, add_float>(&avg_x[0], feature_dimension_,
          FLAGS_spanning_tree_server,
          FLAGS_job_id,
          FLAGS_num_nodes,
          FLAGS_node_id,
          socks);
  std::vector<float> avg_y = y_;
  all_reduce<float, add_float>(&avg_y[0], feature_dimension_,
          FLAGS_spanning_tree_server,
          FLAGS_job_id,
          FLAGS_num_nodes,
          FLAGS_node_id,
          socks);

  // update z with a analytic solution:
  float factor = (FLAGS_num_nodes * rho_)
      / (FLAGS_num_nodes * rho_ + 2.0 * lambda_);
  for (int i = 0; i < feature_dimension_; ++i) {
    z_[i] = factor * (avg_x[i] + avg_y[i]);
  }
}

void ADMMLRL2::UpdateRho() {
  // Keep \rho fixed for now.
  // But it should be modified to improve convergency.
}

///////////////////////////////////

/** @static */
int ADMMLRL2::Progress(void *instance,
                    const lbfgsfloatval_t *x,
                    const lbfgsfloatval_t *g,
                    const lbfgsfloatval_t fx,
                    const lbfgsfloatval_t xnorm,
                    const lbfgsfloatval_t gnorm,
                    const lbfgsfloatval_t step,
                    int n, int k, int ls) {
  return 0;
}

/** @static */
lbfgsfloatval_t ADMMLRL2::Evaluate(void *instance,
                                const lbfgsfloatval_t *x,
                                lbfgsfloatval_t *g,
                                const int n,
                                const lbfgsfloatval_t step) {
  return reinterpret_cast<ADMMLRL2*>(instance)->LossAndGradient(x, n, step, g);
}

}  // namespace lr
}  // namespace admm

