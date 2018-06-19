#ifndef WAVE_FEATURE_TRACK_HPP
#define WAVE_FEATURE_TRACK_HPP

#include <vector>
#include "wave/utils/math.hpp"

namespace wave {

template <int state_dim>
struct FeatureTrack {
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    // pointers to each point
    std::vector<double *> pts;
    // points transformed according to current operating point.
    std::vector<Vec3, Eigen::aligned_allocator<Vec3>> tpts;
    // corresponding states
    std::vector<uint32_t> p_states;
    std::vector<uint32_t> n_states;

    // transform jacobians. prev is the state before, next is the state after
    std::vector<Eigen::Matrix<double, 3, state_dim>, Eigen::aligned_allocator<Eigen::Matrix<double, 3, state_dim>>>
      prev_jac, next_jac;
};
}

#endif  // WAVE_FEATURE_TRACK_HPP