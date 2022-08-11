#pragma once

namespace ct
{
/**
 * @brief 循环获取[0, max_num)之间的整数
 *
 */
class Ring_Number
{
public:
    Ring_Number() : max_num(0), current_num(0) {}
    Ring_Number(int max_num) : max_num(max_num), current_num(0) {}

    void set_max_number(int max_num)
    {
        this->max_num = max_num;
    }

    int value()
    {
        return this->current_num;
    }

    int forward()
    {
        int current_num_tmp = this->current_num;
        this->current_num   = (current_num_tmp + 1) % this->max_num;
        return current_num_tmp;
    }

private:
    int max_num;
    int current_num;
};

}  // namespace ct
