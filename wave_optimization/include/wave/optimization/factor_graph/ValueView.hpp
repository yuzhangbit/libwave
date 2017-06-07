/**
 * @file
 * @ingroup optimization
 */

#ifndef WAVE_OPTIMIZATION_FACTOR_GRAPH_VALUE_HPP
#define WAVE_OPTIMIZATION_FACTOR_GRAPH_VALUE_HPP

#include <iostream>

#include "wave/utils/math.hpp"
#include "wave/optimization/factor_graph/FactorVariableBase.hpp"

namespace wave {
/** @addtogroup optimization
 *  @{ */


/*
 * A structure mapping useful types to an underlying value buffer.
 *
 * While variables and values are fundamental to the factor graph approach, a
 * _view_ is a syntactic convenience. It is a data structure which assigns
 * labels to an underlying value, to simplify interacting with it. For example,
 * a Pose3D view may define elements of the underlying 6D value as `position`
 * and `orientation`. In the Factor's evaluation function, these objects can
 * then be used as independent Eigen vectors.
 *
 * This class is meant to be derived by specialized variable types which assign
 * meaning to the underlying data vector.
 *
 * @todo add more syntactic sugar
 */
template <int S>
class ValueView {
 public:
    constexpr static int Size = S;
    using MappedType = Eigen::Matrix<double, Size, 1>;

    ValueView() = delete;

    /** Construct to map the given array
     * The variable's values are valid only as long as `*data` is valid.
     *
     * @param data pointer to an array of size Size.
     */
    explicit ValueView(double *d) : map{d} {}

    /** Return the size of the underlying value */
    constexpr int size() const noexcept {
        return Size;
    }

    /** Return a raw pointer to the start of the internal vector.
     */
    const double *data() const {
        return this->map.data();
    }
    double *data() {
        return this->map.data();
    }

    void print(std::ostream &os) const {
        os << "ValueView<" << Size << ">";
    }

 protected:
    Eigen::Map<MappedType> map;
};

template <int S>
inline std::ostream &operator<<(std::ostream &os, const ValueView<S> &v) {
    v.print(os);
    return os;
}

/** @} group optimization */
}  // namespace wave

#endif  // WAVE_OPTIMIZATION_FACTOR_GRAPH_VALUE_HPP