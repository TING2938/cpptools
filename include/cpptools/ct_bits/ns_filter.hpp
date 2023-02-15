#pragma once

#include <iostream>
#include <list>
#include <queue>

namespace ct
{
// https://blog.csdn.net/iceboy314159/article/details/106178469
namespace ns_filter
{

template <typename T>
class Basic_Filter
{
public:
    virtual ~Basic_Filter() {}

    virtual T apply(const T& raw) = 0;

    virtual void clear() = 0;

    T last_value() const
    {
        return _last_flt_value;
    }

protected:
    T _last_flt_value;
};

/**
 * @brief Simple Moving Average, SMA
 *  y_{i} = (\sum_{j=i-n+1}^{i} x_{i}) / n
 * @tparam T
 * @tparam M
 */
template <typename T, int M>
class SMA : public Basic_Filter<T>
{
public:
    static_assert(M > 1, "SMA require window width>1");

    SMA()
    {
        this->_last_flt_value = 0;
    }

    T apply(const T& raw) override
    {
        _queue.push(raw);

        if (_queue.size() > M) {
            this->_last_flt_value += ((raw - _queue.front()) / M);
            _queue.pop();
        } else {
            this->_last_flt_value = (this->_last_flt_value * (_queue.size() - 1) + raw) / _queue.size();
        }

        return this->_last_flt_value;
    }

    void clear() override
    {
        this->_last_flt_value = 0;
        decltype(_queue){}.swap(_queue);
    }

private:
    std::queue<T> _queue;
};

/**
 * @brief Weighted Moving Average, WMA
 * y_{i} = (nx_i + (n-1)x_{i-1} + ... + x_{i-n+1}) / (n + (n-1) + ... + 1)
 */
template <typename T, int M>
class WMA : public Basic_Filter<T>
{
public:
    static_assert(M > 1, "WMA require window width>1");

    WMA()
    {
        this->_last_flt_value = 0;
    }

    T apply(const T& raw) override
    {
        _ls.push_back(raw);

        if (_ls.size() > M) {
            _ls.pop_front();
        }

        int sz  = _ls.size();
        int den = sz * (sz + 1) / 2;
        int w   = 1;
        T sum{0};
        for (auto v : _ls) {
            sum += (w * v);
            ++w;
        }

        this->_last_flt_value = sum / den;
        return this->_last_flt_value;
    }

    void clear() override
    {
        this->_last_flt_value = 0;
        _ls.clear();
    }

private:
    std::list<T> _ls;
};

/**
 * @brief Exponential Moving Average,EMA
 *    y_{i} = (1 - alpha)y_{i-1} + alpha * x_{i}
 */
template <typename T>
class EMA : public Basic_Filter<T>
{
public:
    EMA() = delete;

    EMA(double alpha) : _alpha(alpha), _initlized(false)
    {
        this->_last_flt_value = 0;
    }

    T apply(const T& raw) override
    {
        if (!_initlized) {
            this->_last_flt_value = raw;
            _initlized            = true;
        } else {
            this->_last_flt_value = _alpha * this->_last_flt_value + (1 - _alpha) * raw;
        }
        return this->_last_flt_value;
    }

    void clear() override
    {
        _initlized            = false;
        this->_last_flt_value = 0;
    }

    void set_alpha(double alpha)
    {
        _alpha = alpha;
    }

private:
    double _alpha;
    bool _initlized;
};
}  // namespace ns_filter
}  // namespace ct