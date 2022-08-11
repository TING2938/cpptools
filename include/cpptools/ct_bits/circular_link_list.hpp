#pragma once

namespace ct
{
/**
 * @brief 简单的固定长度双向循环链表
 *
 * @tparam T 链表数据元素类型
 * @tparam N 链表长度
 */
template <typename T, unsigned N>
class CircularLinkList
{
public:
    CircularLinkList()
    {
        static_assert(N > 1, "N must larger than 1");
        auto first_node = new Node;
        this->node      = first_node;
        for (unsigned i = 0; i < N - 1; i++) {
            auto tmp         = new Node;
            this->node->next = tmp;
            tmp->prev        = this->node;
            this->node       = tmp;
        }
        this->node->next = first_node;
        first_node->prev = this->node;
    }

    CircularLinkList(const CircularLinkList&) = delete;

    ~CircularLinkList()
    {
        auto tmp = this->node;
        for (unsigned i = 0; i < N; i++) {
            auto tmp2 = tmp;
            tmp       = tmp->next;
            delete tmp2;
        }
    }

    T& value()
    {
        return this->node->data;
    }

    T& next_value(unsigned n = 1)
    {
        auto tmp = this->node;
        for (unsigned i = 0; i < n % N; i++) {
            tmp = tmp->next;
        }
        return tmp->data;
    }

    T& prev_value(unsigned n = 1)
    {
        auto tmp = this->node;
        for (unsigned i = 0; i < n % N; i++) {
            tmp = tmp->prev;
        }
        return tmp->data;
    }

    void forward(unsigned n = 1)
    {
        for (unsigned i = 0; i < n % N; i++) {
            this->node = this->node->next;
        }
    }

    void backward(unsigned n = 1)
    {
        for (unsigned i = 0; i < n % N; i++) {
            this->node = this->node->next;
        }
    }

    constexpr unsigned size() const
    {
        return N;
    }

    void fill(const T& val)
    {
        auto tmp = this->node;
        for (unsigned i = 0; i < N; i++) {
            tmp->data = val;
            tmp       = tmp->next;
        }
    }

private:
    struct Node
    {
        T data;
        Node* next;
        Node* prev;
    };

    Node* node;
};

}  // namespace ct
