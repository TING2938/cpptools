#pragma once

#include <cassert>
#include "vector_tools.hpp"

namespace ct
{
/**
 * @brief Set the rand seed
 */
inline void set_rand_seed(unsigned int __seed = time(nullptr))
{
    srand(__seed);
}

/**
 * @brief [low, up) double type
 *
 * @param low
 * @param up
 * @return double
 */
inline double randf(double low = 0.0, double up = 1.0)
{
    return (double)rand() / ((double)RAND_MAX + 1) * (up - low) + low;
}

/**
 * @brief [low, up) int type
 *
 * @param low
 * @param up
 * @return int
 */
inline int randd(int low = 0, int up = 10)
{
    return rand() % (up - low) + low;
}

/**
 * @brief choise one element from [0, a).
 *
 * @param a vector or int, for choose from vector or [0, a)
 * @param prob The probabilities associated with each entry in a.
 *             If empty, the sample assumes a uniform distribution over all entries in a
 * @return int
 */
template <typename T = double>
inline int random_choise(int a, const std::vector<T>& prob = {})
{
    if (prob.empty()) {
        return randd(0, a);
    } else {
        assert(std::abs(sum(prob) - double(1.0f)) < 1e-6);
        auto r   = randf(0.0f, 1.0f);
        double s = 0.0f;
        for (int i = 0; i < prob.size(); i++) {
            s += prob[i];
            if (s >= r)
                return i;
        }
        return -1;  // else return error
    }
}

/**
 * @brief choise one element from vector a.
 *
 * @tparam T
 * @param a vector or int, for choose from vector or [0, a)
 * @param prob The probabilities associated with each entry in a.
 *             If empty, the sample assumes a uniform distribution over all entries in a
 * @return T
 */
template <typename T, typename P = double>
inline T random_choise(const std::vector<T>& a, const std::vector<P>& prob = {})
{
    return a[random_choise(a.size(), prob)];
}

/**
 * @brief choise `size` elements from vector a.
 *
 * @tparam T
 * @param a vector or int, for choose from vector or [0, a)
 * @param size
 * @param prob The probabilities associated with each entry in a.
 *             If empty, the sample assumes a uniform distribution over all entries in a
 * @return std::vector<T>
 */
template <typename T, typename P = double>
inline std::vector<T> random_choise(const std::vector<T>& a, int size, const std::vector<P>& prob = {})
{
    std::vector<T> ret(size);
    for (int i = 0; i < size; i++) {
        ret[i] = random_choise(a, prob);
    }
    return ret;
}

/**
 * @brief choise `size` elements from [0, a).
 *
 * @param a vector or int, for choose from vector or [0, a)
 * @param size number of samples to choise
 * @param prob The probabilities associated with each entry in a.
 *             If empty, the sample assumes a uniform distribution over all entries in a
 * @return Veci
 */
template <typename P = double>
inline std::vector<int> random_choise(int a, int size, const std::vector<P>& prob = {})
{
    std::vector<int> ret(size);
    for (int i = 0; i < size; i++) {
        ret[i] = random_choise(a, prob);
    }
    return ret;
}
}  // namespace ct
