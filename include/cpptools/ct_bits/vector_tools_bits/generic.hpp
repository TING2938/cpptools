#pragma once

#include <algorithm>
#include <cassert>
#include <vector>

namespace ct
{

template <typename _InputIterator, typename _Tp>
inline bool contain(_InputIterator __first, _InputIterator __last, const _Tp& __val)
{
    return std::find(__first, __last, __val) != __last;
}

template <typename T>
inline bool contain(const std::vector<T>& vec, const T& __val)
{
    return ct::contain(vec.begin(), vec.end(), __val);
}

template <typename T, int N>
inline bool contain(const T (&vec)[N], const T& __val)
{
    return ct::contain(std::begin(vec), std::end(vec), __val);
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
}  // namespace ct
