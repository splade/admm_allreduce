// Copyright 2014. Gang Bai <me@baigang.net>
#include <istream>  // NOLINT
#include <string>
#include "sample_set.h"  // NOLINT
#include <glog/logging.h>  // NOLINT

namespace admm {
SampleSet::SampleSet()
  : use_01_label_(false)
  , num_skipped_lines_(0)
  , num_parsed_lines_(0) {
}

SampleSet::~SampleSet() {
}

// XXX(baigang): dense feature vectors only.
// Should be supporting sparse features.
bool SampleSet::ParseSamples(std::istream& input) {  // NOLINT
  std::string buf = new char[32768];
  while (input) {
    getline(input, buf);
    if (buf.length() < 1 || buf[0] == '#') {
      ++num_skipped_lines_;
      continue;
    }
    Sample sample;
    std::istringstream iss(buf);
    iss >> sample.label;
    while (iss) {
      float feature;
      iss >> feature;
      sample.features.push_back(feature);
    }

    if (sample.features.size() < 1) {
      LOG(WARNING)
        << "Empty feature in line "
        << num_parsed_lines_ + num_skipped_lines_ + 1;
      continue;
    }
    samples_.push_back(sample);
    LOG_EVERY_N(INFO, 1000) << "Parsed "
        << num_parsed_lines_ << " sample.";
  }
  if (num_parsed_lines_ < 0)
    return true;
  else
    return false;
}

}  // namespace admm

