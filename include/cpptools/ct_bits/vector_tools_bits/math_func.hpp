#pragma once

#include <algorithm>
#include <cmath>
#include <functional>
#include <numeric>
#include <vector>

namespace ct
{
template <typename _Tp, typename _InputIterator>
inline _Tp sum(_InputIterator __first, _InputIterator __last)
{
    return std::accumulate(__first, __last, (_Tp)(0));
}

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
    return ct::sum<T>(vec.begin(), vec.end());
}

template <typename T, int N>
inline T sum(const T (&vec)[N])
{
    return ct::sum<T>(vec, vec + N);
}

template <typename _InputIterator>
inline double mean(_InputIterator __first, _InputIterator __last)
{
    int N    = 0;
    double s = 0.0;
    for (auto it = __first; it != __last; ++it) {
        s += *it;
        ++N;
    }
    if (N == 0)
        return 0.0;
    return s / N;
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
    return ct::mean(vec.begin(), vec.end());
}

template <typename T, int N>
inline double mean(const T (&vec)[N])
{
    return ct::mean(vec, vec + N);
}

template <typename _InputIterator>
inline auto max(_InputIterator __first, _InputIterator __last) -> typename std::decay<decltype(*__first)>::type
{
    return *std::max_element(__first, __last);
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


template <typename _InputIterator>
inline std::ptrdiff_t argmax(_InputIterator __first, _InputIterator __last)
{
    return std::max_element(__first, __last) - __first;
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
    return ct::argmax(vec.begin(), vec.end());
}

template <typename T, int N>
inline std::ptrdiff_t argmax(const T (&vec)[N])
{
    return ct::argmax(std::begin(vec), std::end(vec));
}

template <typename _InputIterator>
inline auto min(_InputIterator __first, _InputIterator __last) -> typename std::decay<decltype(*__first)>::type
{
    return *std::min_element(__first, __last);
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

template <typename _InputIterator>
inline std::ptrdiff_t argmin(_InputIterator __first, _InputIterator __last)
{
    return std::min_element(__first, __last) - __first;
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

template <typename _InputIterator>
inline double stddev(_InputIterator __first, _InputIterator __last)
{
    auto mean       = ct::mean(__first, __last);
    double variance = 0.0;
    int N           = 0;
    for (auto it = __first; it != __last; ++it) {
        variance += std::pow(*it - mean, 2);
        ++N;
    }
    variance /= N;
    return std::sqrt(variance);
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
    return ct::stddev(vec.begin(), vec.end());
}

template <typename T, int N>
inline double stddev(const T (&vec)[N])
{
    return ct::stddev(vec, vec + N);
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
}  // namespace ct