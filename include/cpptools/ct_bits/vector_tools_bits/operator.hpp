#pragma once

#include <cassert>
#include <vector>

namespace ct
{
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