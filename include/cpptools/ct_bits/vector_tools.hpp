#pragma once

#include <algorithm>
#include <cassert>
#include <cmath>
#include <numeric>
#include <ostream>
#include <vector>

namespace ct
{

/**
 * @brief the sum value of `vec`
 *
 * @tparam T
 * @param vec the vector to calculate
 * @return T the result
 */
template <typename T>
inline T sum(const std::vector<T>& vec)
{
    return std::accumulate(vec.begin(), vec.end(), T(0));
}

template <typename T, int N>
inline T sum(const T (&vec)[N])
{
    return std::accumulate(std::begin(vec), std::end(vec), T(0));
}

/**
 * @brief the mean value of `vec`
 *
 * @tparam T
 * @param vec the vector to calculate
 * @return double the result
 */
template <typename T>
inline double mean(const std::vector<T>& vec)
{
    if (vec.empty())
        return 0.0;
    return double(sum(vec)) / double(vec.size());
}

template <typename T, int N>
inline double mean(const T (&vec)[N])
{
    if (N == 0)
        return 0.0;
    return double(sum(vec)) / double(N);
}

/**
 * @brief the max value of `vec`
 *
 * @tparam T
 * @param vec the vector to calculate
 * @return T the result
 */
template <typename T>
inline T max(const std::vector<T>& vec)
{
    return *std::max_element(vec.begin(), vec.end());
}

template <typename T, int N>
inline T max(const T (&vec)[N])
{
    return *std::max_element(std::begin(vec), std::end(vec));
}

/**
 * @brief the max position of `vec`
 *
 * @tparam T
 * @param vec the vector to calculate
 * @return std::ptrdiff_t the result
 */
template <typename T>
inline std::ptrdiff_t argmax(const std::vector<T>& vec)
{
    return std::max_element(vec.begin(), vec.end()) - vec.begin();
}

template <typename T, int N>
inline std::ptrdiff_t argmax(const T (&vec)[N])
{
    return std::max_element(std::begin(vec), std::end(vec)) - std::begin(vec);
}

/**
 * @brief the min value of `vec`
 *
 * @tparam T
 * @param vec the vector to calculate
 * @return T the result
 */
template <typename T>
inline T min(const std::vector<T>& vec)
{
    return *std::min_element(vec.begin(), vec.end());
}

template <typename T, int N>
inline T min(const T (&vec)[N])
{
    return *std::min_element(std::begin(vec), std::end(vec));
}

/**
 * @brief the min position of `vec`
 *
 * @tparam T
 * @param vec the vector to calculate
 * @return std::ptrdiff_t the result
 */
template <typename T>
inline std::ptrdiff_t argmin(const std::vector<T>& vec)
{
    return std::min_element(vec.begin(), vec.end()) - vec.begin();
}

template <typename T, int N>
inline std::ptrdiff_t argmin(const T (&vec)[N])
{
    return std::min_element(std::begin(vec), std::end(vec)) - std::begin(vec);
}

/**
 * @brief stddev of vector
 *  stddev = \sqrt{\frac{1}{n} \sum_{i = 0}^{n} {(x_{i}-\bar{x})^{2}}}
 * @tparam T
 * @param vec the vector to calculate
 * @return double the result
 */
template <typename T>
inline double stddev(const std::vector<T>& vec)
{
    auto mean       = ct::mean(vec);
    double variance = 0.0;
    for (auto v : vec) {
        variance += std::pow(v - mean, 2);
    }
    variance /= vec.size();
    return std::sqrt(variance);
}

template <typename T, int N>
inline double stddev(const T (&vec)[N])
{
    auto mean       = ct::mean(vec);
    double variance = 0.0;
    for (auto v : vec) {
        variance += std::pow(v - mean, 2);
    }
    variance /= N;
    return std::sqrt(variance);
}

/**
 * @brief calculate vec[0] * vec[1] * vec[2] * ...
 *
 * @tparam T
 * @param vec the vector to calculate
 * @return T the result
 */
template <typename T>
inline T prod(const std::vector<T>& vec)
{
    return std::accumulate(vec.begin(), vec.end(), T(1), std::multiplies<T>());
}

template <typename T, int N>
inline T prod(const T (&vec)[N])
{
    return std::accumulate(std::begin(vec), std::end(vec), T(1), std::multiplies<T>());
}

/**
 * @brief Clip (limit) the values in an array.
 *
 *  Given an interval, values outside the interval are clipped to
 *  the interval edges.  For example, if an interval of ``[0, 1]``
 *  is specified, values smaller than 0 become 0, and values larger
 *  than 1 become 1.
 *
 * the inplace version of clip
 *
 * @tparam T
 * @param vec the vector to clip
 * @param low low boundary
 * @param up up boundary
 */
template <typename T>
inline void clip_(std::vector<T>& vec, const T& low, const T& up)
{
    for (auto&& v : vec) {
        if (v > up)
            v = up;
        if (v < low)
            v = low;
    }
}

/**
 * @brief Clip (limit) the values in an array.
 *
 *  Given an interval, values outside the interval are clipped to
 *  the interval edges.  For example, if an interval of ``[0, 1]``
 *  is specified, values smaller than 0 become 0, and values larger
 *  than 1 become 1.
 *
 * the inplace version of clip
 *
 * @tparam T
 * @param vec the vector to clip
 * @param low low boundary
 * @param up up boundary
 * @return the cliped vec
 */
template <typename T>
inline void clip_(std::vector<T>& vec, const std::vector<T>& low, const std::vector<T>& up)
{
    for (unsigned i = 0; i < vec.size(); i++) {
        if (vec[i] > up[i])
            vec[i] = up[i];
        if (vec[i] < low[i])
            vec[i] = low[i];
    }
}

/**
 * @brief Clip (limit) the values in an array.
 *
 *  Given an interval, values outside the interval are clipped to
 *  the interval edges.  For example, if an interval of ``[0, 1]``
 *  is specified, values smaller than 0 become 0, and values larger
 *  than 1 become 1.
 *
 * @tparam T
 * @param vec the vector to clip
 * @param low low boundary
 * @param up up boundary
 * @return the cliped vec
 */
template <typename T>
inline std::vector<T> clip(const std::vector<T>& vec, const T& low, const T& up)
{
    auto ret = vec;
    clip_(ret, low, up);
    return ret;
}

/**
 * @brief Clip (limit) the values in an array.
 *
 *  Given an interval, values outside the interval are clipped to
 *  the interval edges.  For example, if an interval of ``[0, 1]``
 *  is specified, values smaller than 0 become 0, and values larger
 *  than 1 become 1.
 *
 * @tparam T
 * @param vec the vector to clip
 * @param low low boundary
 * @param up up boundary
 * @return the cliped vec
 */
template <typename T>
inline std::vector<T> clip(const std::vector<T>& vec, const std::vector<T>& low, const std::vector<T>& up)
{
    auto ret = vec;
    clip_(ret, low, up);
    return ret;
}

template <typename T>
inline T clip(const T& scalar, const T& low, const T& up)
{
    assert(low <= up);
    if (scalar > up) {
        return up;
    }
    if (scalar < low) {
        return low;
    }
    return scalar;
}

/**
 * @brief Do an elementwise linear transform of values a * vec + b
 *
 * the inplace version of scale
 *
 * @tparam T
 * @param vec vector to modify
 * @param a The value to multiply by
 * @param b The value to add
 */
template <typename T>
inline void scale_(std::vector<T>& vec, const T& a, const T& b)
{
    for (size_t i = 0; i < vec.size(); i++) {
        vec[i] = a * vec[i] + b;
    }
}

/**
 * @brief Do an elementwise linear transform of values a * vec + b
 *
 * the inplace version of scale
 *
 * @tparam T
 * @param vec vector to modify
 * @param a The value to multiply by
 * @param b The value to add
 */
template <typename T>
inline void scale_(std::vector<T>& vec, const std::vector<T>& a, const std::vector<T>& b)
{
    for (size_t i = 0; i < vec.size(); i++) {
        vec[i] = a[i] * vec[i] + b[i];
    }
}

/**
 * @brief Do an elementwise linear transform of values a * vec + b
 *
 * @tparam T
 * @param vec vector to modify
 * @param a The value to multiply by
 * @param b The value to add
 * @return a * vec + b
 */
template <typename T>
inline std::vector<T> scale(const std::vector<T>& vec, const T& a, const T& b)
{
    auto ret = vec;
    scale_(ret, a, b);
    return ret;
}

/**
 * @brief Do an elementwise linear transform of values a * vec + b
 *
 * @tparam T
 * @param vec vector to modify
 * @param a The value to multiply by
 * @param b The value to add
 * @return a * vec + b
 */
template <typename T>
inline std::vector<T> scale(const std::vector<T>& vec, const std::vector<T>& a, const std::vector<T>& b)
{
    auto ret = vec;
    scale_(ret, a, b);
    return ret;
}

template <typename T, typename Iter>
inline void gather(const std::vector<T>& vec, std::vector<T>* out, Iter beg_ind, Iter end_ind)
{
    out->clear();
    out->reserve(end_ind - beg_ind);
    for (auto it = beg_ind; it != end_ind; it++) {
        out->push_back(vec.at(*it));
    }
}

template <typename T, typename S = size_t>
inline void gather(const std::vector<T>& vec, std::vector<T>* out, const std::vector<S>& ind)
{
    gather(vec, out, ind.begin(), ind.end());
}

template <typename T, typename S = size_t>
inline std::vector<T> gather(const std::vector<T>& vec, const std::vector<S>& ind)
{
    std::vector<T> out;
    gather(vec, &out, ind.begin(), ind.end());
    return out;
}

template <typename T, typename Iter>
inline std::vector<T> gather(const std::vector<T>& vec, Iter beg_ind, Iter end_ind)
{
    std::vector<T> out;
    gather(vec, &out, beg_ind, end_ind);
    return out;
}

template <typename T>
inline std::vector<T> flatten(const std::vector<std::vector<T>>& mat)
{
    auto nrow = mat.size();
    auto ncol = mat[0].size();
    std::vector<T> ret(nrow * ncol);
    for (int i = 0; i < nrow; i++) {
        for (int j = 0; j < ncol; j++) {
            ret[i * ncol + j] = mat[i][j];
        }
    }
    return ret;
}
/**
 * the operator namespace for ct
 */
namespace opt
{
#define CT_VEC_OP_VEC_RET_VEC(op)                                                             \
    template <typename T>                                                                     \
    inline std::vector<T> operator op(const std::vector<T>& vec1, const std::vector<T>& vec2) \
    {                                                                                         \
        assert(vec1.size() == vec2.size());                                                   \
        std::vector<T> ret(vec1.size());                                                      \
        for (int i = 0; i < vec1.size(); i++) {                                               \
            ret[i] = vec1[i] op vec2[i];                                                      \
        }                                                                                     \
        return ret;                                                                           \
    }

CT_VEC_OP_VEC_RET_VEC(+)
CT_VEC_OP_VEC_RET_VEC(-)
CT_VEC_OP_VEC_RET_VEC(*)
CT_VEC_OP_VEC_RET_VEC(/)
CT_VEC_OP_VEC_RET_VEC(%)
#undef CT_VEC_OP_VEC_RET_VEC

#define CT_VEC_OP_VEC_INPLACE(op)                                                        \
    template <typename T>                                                                \
    inline std::vector<T>& operator op(std::vector<T>& vec1, const std::vector<T>& vec2) \
    {                                                                                    \
        assert(vec1.size() == vec2.size());                                              \
        for (int i = 0; i < vec1.size(); i++) {                                          \
            vec1[i] op vec2[i];                                                          \
        }                                                                                \
        return vec1;                                                                     \
    }

CT_VEC_OP_VEC_INPLACE(+=)
CT_VEC_OP_VEC_INPLACE(-=)
CT_VEC_OP_VEC_INPLACE(*=)
CT_VEC_OP_VEC_INPLACE(/=)
CT_VEC_OP_VEC_INPLACE(%=)
#undef CT_VEC_OP_VEC_INPLACE

#define CT_VEC_OP_NUM_RET_VEC(op)                                              \
    template <typename T>                                                      \
    inline std::vector<T> operator op(const std::vector<T>& vec, const T& num) \
    {                                                                          \
        std::vector<T> ret(vec.size());                                        \
        for (int i = 0; i < vec.size(); i++) {                                 \
            ret[i] = vec[i] op num;                                            \
        }                                                                      \
        return ret;                                                            \
    }

CT_VEC_OP_NUM_RET_VEC(+)
CT_VEC_OP_NUM_RET_VEC(-)
CT_VEC_OP_NUM_RET_VEC(*)
CT_VEC_OP_NUM_RET_VEC(/)
CT_VEC_OP_NUM_RET_VEC(%)
#undef CT_VEC_OP_NUM_RET_VEC

#define CT_VEC_OP_NUM_INPLACE(op)                                         \
    template <typename T>                                                 \
    inline std::vector<T>& operator op(std::vector<T>& vec, const T& num) \
    {                                                                     \
        for (int i = 0; i < vec.size(); i++) {                            \
            vec[i] op num;                                                \
        }                                                                 \
        return vec;                                                       \
    }

CT_VEC_OP_NUM_INPLACE(+=)
CT_VEC_OP_NUM_INPLACE(-=)
CT_VEC_OP_NUM_INPLACE(*=)
CT_VEC_OP_NUM_INPLACE(/=)
CT_VEC_OP_NUM_INPLACE(%=)
#undef CT_VEC_OP_NUM_INPLACE

}  // namespace opt
}  // namespace ct