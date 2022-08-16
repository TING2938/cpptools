#pragma once

#include <cstdio>
#include <functional>
#include <vector>

namespace ct
{
template <typename T, typename Operator>
class ReduceTree
{
public:
    void init(size_t size)
    {
        if (size & (size - 1)) {
            printf("size must be a power of 2.\n");
            std::exit(-1);
        }
        this->size = size;
        this->values.resize(2 * this->size, 0);
    }

    T root()
    {
        return this->values[1];
    }

    void setItem(size_t idx, T val)
    {
        idx += this->size;
        this->values[idx] = val;
        this->percolate_up(idx);
    }

    template <typename S>
    void setItem(const std::vector<S>& idx, const std::vector<T>& val)
    {
        for (size_t i = 0; i < idx.size(); i++) {
            this->setItem(idx[i], val[i]);
        }
    }

    T getItem(size_t idx)
    {
        return this->values[idx + this->size];
    }

    template <typename S>
    std::vector<T> getItem(const std::vector<S>& idx)
    {
        std::vector<T> ret(idx.size());
        for (size_t i = 0; i < idx.size(); i++) {
            ret[i] = this->getItem(idx[i]);
        }
        return ret;
    }

private:
    void percolate_up(size_t idx)
    {
        idx /= 2;
        while (idx > 0) {
            this->values[idx] = this->op(this->values[2 * idx], this->values[2 * idx + 1]);
            idx /= 2;
        }
    }

protected:
    size_t size;
    std::vector<T> values;
    Operator op;
};

template <typename T>
class SumTree : public ReduceTree<T, std::plus<T>>
{
public:
    size_t sample(T value)
    {
        size_t idx = 1;
        size_t child;
        while (idx < this->size) {
            child = 2 * idx;
            if (value <= this->values[child]) {
                idx = child;
            } else {
                value -= this->values[child];
                idx = child + 1;
            }
        }
        return idx - this->size;
    }
};
}  // namespace ct
