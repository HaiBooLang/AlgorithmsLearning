#pragma once
#include <memory>

template<typename T>
class StackDispersed
{
private:
    struct Node
    {
        T data;
        std::unique_ptr<Node> next;

        Node(T&& item, std::unique_ptr<Node>&& next)
            : data{ std::move(item) }, next{ std::move(next) }
        {}

        Node(const T& item, std::unique_ptr<Node>&& next)
            : data{ item }, next{ std::move(next) }
        {}
    };

    std::unique_ptr<Node> head;
    std::size_t size;

public:
    explicit StackDispersed();
    StackDispersed(const StackDispersed& other);
    StackDispersed(StackDispersed&& other) noexcept;
    StackDispersed& operator=(const StackDispersed& other);
    StackDispersed& operator=(StackDispersed&& other) noexcept;
    void push(const T& item);
    void push(T&& item);
    T& top();
    const T& top() const;
    T&& pop();
    bool empty() const;
    std::size_t get_size() const;
    std::size_t get_capacity() const;
};

template<typename T>
StackDispersed<T>::StackDispersed()
    : head{ nullptr }, size{ 0 }
{}

template<typename T>
StackDispersed<T>::StackDispersed(const StackDispersed& other)
    : head{ nullptr }, size{ other.size }
{
    if (other.head)
    {
        head = std::make_unique<Node>(other.head->data, nullptr);
        Node* this_node = head.get();
        Node* other_node = other.head.get();
        while (other_node->next)
        {
            this_node->next = std::make_unique<Node>(other_node->next->data, nullptr);
            this_node = this_node->next.get();
            other_node = other_node->next.get();
        }
    }
}

template<typename T>
StackDispersed<T>::StackDispersed(StackDispersed&& other) noexcept
    : head{ std::move(other.head) }, size{ other.size }
{
    other.size = 0;
}

template<typename T>
StackDispersed<T>& StackDispersed<T>::operator=(const StackDispersed& other)
{
    if (this != &other)
    {
        StackDispersed temp{ other };
        std::swap(head, temp.head);
        size = temp.size;
    }
    return *this;
}

template<typename T>
StackDispersed<T>& StackDispersed<T>::operator=(StackDispersed&& other) noexcept
{
    if (this != &other)
    {
        head = std::move(other.head);
        size = other.size;
        other.size = 0;
    }
    return *this;
}

template<typename T>
void StackDispersed<T>::push(const T& item)
{
    Node* new_node = new Node(item);
    new_node->next = head;
    head = new_node;
    ++size;
}

template<typename T>
void StackDispersed<T>::push(T&& item)
{
    head = std::make_unique<Node>(std::move(item), std::move(head));
    ++size;
}

template<typename T>
T& StackDispersed<T>::top()
{
    if (empty())
    {
        throw std::out_of_range("Stack is empty");
    }
    return head->data;
}

template<typename T>
const T& StackDispersed<T>::top() const
{
    if (empty())
    {
        throw std::out_of_range("Stack is empty");
    }
    return head->data;
}

template<typename T>
T&& StackDispersed<T>::pop()
{
    if (empty())
    {
        throw std::out_of_range("Stack is empty");
    }
    T&& result = std::move(head->data);
    head = std::move(head->next);
    --size;
    return std::move(result);
}

template<typename T>
bool StackDispersed<T>::empty() const
{
    return size == 0;
}

template<typename T>
std::size_t StackDispersed<T>::get_size() const
{
    return size;
}