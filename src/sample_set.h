#ifndef _ADMM_SAMPLE_SET_H_
#define _ADMM_SAMPLE_SET_H_
#include <istream>
#include <vector>

namespace admm {

class SampleSet {
 public:

  class Sample {
   public:
    float label;
    // TODO(baigang): support sparse features otherwise this is a unmature toy.
    std::vector<float> features;
  };

  bool ParseSamples(std::istream& input);

  const std::vector<Sample>& Samples() const {return samples_;}
  std::vector<Sample>* MutateSamples() {return &samples_;}

  bool use_01_label() const {return use_01_label_;}
  void set_use_01_label(bool set) {use_01_label_ = set;}
  
  SampleSet();
  virtual ~SampleSet();
 protected:
  std::vector<Sample> samples_;
  bool use_01_label_;
  unsigned int num_skipped_lines_;
  unsigned int num_parsed_lines_;
};

}  // namespace admm

#endif  // _ADMM_SAMPLE_SET_H_

