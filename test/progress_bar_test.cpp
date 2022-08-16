#include <gtest/gtest.h>

#include <cpptools/ct_bits/progress_bar.hpp>

TEST(ct_test, progressbar_test)
{
    int N = 100;
    ct::ProgressBar bar(N, std::chrono::seconds(1));
    bar.style = ct::ProgressBar::Style::BB;

    bar.start();
    for (int i = 0; i < N; i++) {
        bar.update();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    bar.finish();
}
