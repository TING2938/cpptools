#include <list>
#include <queue>

namespace ct
{
namespace ns_filter
{
template <typename T, int M>
class SMA
{
public:
    static_assert(M > 1, "SMA require window width>1");

    SMA() : _last_flt_value{0} {};
    ~SMA(){};
    T apply(const T& raw)
    {
        _queue.push(raw);

        if (_queue.size() > M) {
            _last_flt_value += ((raw - _queue.front()) / M);
            _queue.pop();
        } else {
            _last_flt_value = (_last_flt_value * (_queue.size() - 1) + raw) / _queue.size();
        }

        return _last_flt_value;
    }

private:
    std::queue<T> _queue;
    T _last_flt_value{0};
};

template <typename T, int M>
class WMA
{
public:
    static_assert(M > 1, "WMA require window width>1");

    WMA(){};
    ~WMA(){};
    T apply(const T& raw)
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

        return sum / den;
    }

private:
    std::list<T> _ls;
};

template <typename T>
class EMA
{
public:
    EMA() = delete;
    EMA(double alpha)
    {
        _alpha = alpha;
    };
    ~EMA(){};
    T apply(const T& raw)
    {
        if (_initlized == false) {
            _last_y    = raw;
            _initlized = true;
        } else {
            _last_y = _alpha * _last_y + (1 - _alpha) * raw;
        }
        return _last_y;
    }

private:
    T _last_y;
    double _alpha   = 0.1f;
    bool _initlized = false;
};
}  // namespace ns_filter
}  // namespace ct