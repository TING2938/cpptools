#pragma once

#include <fmt/format.h>
#include <atomic>
#include <chrono>
#include <ctime>
#include <functional>
#include <limits>
#include <string>

#include "color.hpp"
#include "timer.hpp"

namespace ct
{
class ProgressBar
{
public:
    // 进度条的长度（不包含前后缀）
    unsigned int ncols = 25;

    // 总数
    unsigned int totalNum = 0;

    // 重绘周期，毫秒
    std::chrono::milliseconds interval = std::chrono::seconds(1);

    // 填充标志
    char sign = '=';

    // 显示样式
    enum class Style
    {
        AA,
        BB,
        NUM,
    } style = Style::AA;

protected:
    // 上次的已完成数量
    unsigned int lastNum = 0;

    // 已完成的数量
    std::atomic<unsigned int> finishedNum = 0;

    // 开始时间
    std::chrono::steady_clock::time_point beginTime;

    // 上次重绘的时间
    std::chrono::steady_clock::time_point lastTime;

    ct::Timer timingActuator;

public:
    ProgressBar() = default;

    ProgressBar(unsigned int totalNum, std::chrono::milliseconds interval = std::chrono::seconds(1))
        : totalNum(totalNum), interval(interval)
    {
    }

    // 开始
    void start()
    {
        // 记录开始时间，并初始化定时器
        this->finishedNum = 0;
        this->lastNum     = 0;
        this->beginTime   = std::chrono::steady_clock::now();
        this->lastTime    = this->beginTime;
        // 定时器用于定时调用重绘函数
        this->timingActuator.setInterval(int(this->interval.count()), std::bind(&ProgressBar::show, this));
    }

    // 完成
    void finish()
    {
        // 停止定时器
        this->timingActuator.stop();
        this->show();
        std::fprintf(stderr, "%s\n", color::showCursor);
    }

    // 一次更新num数量
    void update(unsigned int num = 1)
    {
        this->finishedNum += num;
    }

private:
    // 重绘
    void show()
    {
        // 清除上次的绘制内容
        std::fprintf(stderr, "%s\r%s", color::hideCursor, color::clearToEndLine);

        // 记录重绘的时间点
        std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();

        // 获取已完成的数量
        unsigned int tmpFinished = this->finishedNum.load();

        // 获取与开始时间和上次重绘时间的时间间隔
        auto timeFromStart = now - this->beginTime;
        auto timeFromLast  = now - this->lastTime;

        // 这次完成的数量
        unsigned int gap = tmpFinished - this->lastNum;

        // 计算速度
        double rate = gap / std::chrono::duration<double>(timeFromLast).count();

        // 应显示的百分数
        double present = (100.0 * tmpFinished) / this->totalNum;
        this->lastNum  = tmpFinished;
        this->lastTime = now;

        switch (style) {
            case Style::AA:
                style_AA(present, rate, tmpFinished, timeFromStart);
                break;
            case Style::BB:
                style_BB(present);
                break;
            default:
                style_AA(present, rate, tmpFinished, timeFromStart);
                break;
        }
    }

    void style_AA(double present, double rate, unsigned int tmpFinished, const std::chrono::nanoseconds& timeFromStart)
    {
        int barWidth = int(present * this->ncols / 100.0);

        // 之后的两部分内容分别为打印已过的时间和剩余时间
        std::time_t tfs;
        char mbstr1[100], mbstr2[100];
        tfs = std::time_t(std::chrono::duration<double>(timeFromStart).count());
        std::strftime(mbstr1, sizeof(mbstr1), "%X", gmtime(&tfs));
        int timeLast;
        if (rate != 0) {
            // 剩余时间的估计是用这次的速度和未完成的数量进行估计
            timeLast = int((this->totalNum - tmpFinished) / rate);
        } else {
            timeLast = std::numeric_limits<int>::max();
        }
        if ((this->totalNum - tmpFinished) == 0) {
            timeLast = 0;
        }
        tfs = timeLast;
        std::strftime(mbstr2, sizeof(mbstr2), "%X", gmtime(&tfs));

        fmt::print(stderr, fmt::runtime(std::string("{}{:.1f}%|{:") + sign + ">{}}{:>{}}{:.1f}MHz|{}|{}{}"),
                   color::green, present, '>', barWidth, '|', this->ncols - barWidth, rate / 1000, mbstr1, mbstr2,
                   color::reset);
    }

    void style_BB(double present)
    {
        int centerWidth = 6;
        int leftWidth   = int((this->ncols - centerWidth) * present / 100.0);
        int rightWidth  = this->ncols - leftWidth - centerWidth;

        fmt::print(stderr, "{}{:=>{}}{:.1f}%{:->{}}{}", color::green, '>', leftWidth, present, '-', rightWidth,
                   color::reset);
    }
};
}  // namespace ct
