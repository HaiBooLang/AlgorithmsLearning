#pragma once
#include <memory>

template<typename T>
class StackContinuous
{
private:
    std::unique_ptr<T[]> data;
    std::size_t size;
    std::size_t capacity;

public:
    explicit StackContinuous(std::size_t capacity = 16);
    StackContinuous(const StackContinuous& other);
    StackContinuous(StackContinuous&& other) noexcept;
    StackContinuous& operator=(const StackContinuous& other);
    StackContinuous& operator=(StackContinuous&& other) noexcept;
    void push(const T& item);
    void push(T&& item);
    T& top();
    const T& top() const;
    T&& pop();
    bool empty() const;
    std::size_t get_size() const;
    std::size_t get_capacity() const;

    T* begin() { return data.get(); }
    const T* begin() const { return data.get(); }
    T* end() { return data.get() + size; }
    const T* end() const { return data.get() + size; }
};

template<typename T>
StackContinuous<T>::StackContinuous(std::size_t capacity)
    : data{ std::make_unique<T[]>(capacity) }, size{ 0 }, capacity{ capacity }
{}

template<typename T>
StackContinuous<T>::StackContinuous(const StackContinuous& other)
    : data{ std::make_unique<T[]>(other.capacity) }, size{ other.size }, capacity{ other.capacity }
{
    std::copy_n(other.data.get(), size, data.get());
}

template<typename T>
StackContinuous<T>::StackContinuous(StackContinuous&& other) noexcept
    : data{ std::move(other.data) }, size{ other.size }, capacity{ other.capacity }
{
    other.size = 0;
    other.capacity = 0;
}

template<typename T>
StackContinuous<T>& StackContinuous<T>::operator=(const StackContinuous& other)
{
    if (this != &other)
    {
        StackContinuous temp{ other };
        std::swap(data, temp.data);
        size = temp.size;
        capacity = temp.capacity;
    }
    return *this;
}

template<typename T>
StackContinuous<T>& StackContinuous<T>::operator=(StackContinuous&& other) noexcept
{
    if (this != &other)
    {
        data = std::move(other.data);
        size = other.size;
        capacity = other.capacity;
        other.size = 0;
        other.capacity = 0;
    }
    return *this;
}

template<typename T>
void StackContinuous<T>::push(const T& item)
{
    if (size == capacity)
    {
        std::size_t new_capacity = capacity * 2;
        std::unique_ptr<T[]> new_data{ std::make_unique<T[]>(new_capacity) };
        std::copy_n(data.get(), size, new_data.get());
        data = std::move(new_data);
        capacity = new_capacity;
    }
    data[size++] = item;
}

template<typename T>
void StackContinuous<T>::push(T&& item)
{
    if (size == capacity)
    {
        std::size_t new_capacity = capacity * 2;
        std::unique_ptr<T[]> new_data{ std::make_unique<T[]>(new_capacity) };
        std::copy_n(data.get(), size, new_data.get());
        data = std::move(new_data);
        capacity = new_capacity;
    }
    data[size++] = std::move(item);
}

template<typename T>
T& StackContinuous<T>::top()
{
    if (empty())
    {
        throw std::out_of_range("Stack is empty");
    }
    return data[size - 1];
}

template<typename T>
const T& StackContinuous<T>::top() const
{
    if (empty())
    {
        throw std::out_of_range("Stack is empty");
    }
    return data[size - 1];
}

template<typename T>
T&& StackContinuous<T>::pop()
{
    if (empty())
    {
        throw std::out_of_range("Stack is empty");
    }
 	return std::move(data[--size]);
}

template<typename T>
bool StackContinuous<T>::empty() const
{
    return size == 0;
}

template<typename T>
std::size_t StackContinuous<T>::get_size() const
{
    return size;
}

template<typename T>
std::size_t StackContinuous<T>::get_capacity() const
{
    return capacity;
}

