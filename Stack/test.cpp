#include <iostream>
#include <algorithm>
#include <cassert>
#include "StackContinuous.h"
#include "StackDispersed.h"

template<typename T>
struct Print
{
    void operator()(const T& item) const
    {
        std::cout << item << " ";
    }
};

int main()
{
    // 创建一个栈对象
    StackContinuous<int> s;

    for (int i = 0; i < 256; i++)
    {
        s.push(i);
        assert(s.top == i);
    }
    std::for_each(s.begin(), s.end(), Print<int>{});
    std::cout << std::endl;

    for (int i = 255; i >= 0; i--)
    {
        assert(s.top == i);
        s.pop();
    }
    assert(s.empty());
    std::cout << std::endl;

    // 测试拷贝构造函数和赋值运算符
    StackContinuous<int> s1;
    s1.push(1);
    s1.push(2);
    s1.push(3);
    std::for_each(s1.begin(), s1.end(), Print<int>{});
    std::cout << std::endl;
    StackContinuous<int> s2{ s1 };
    assert(s2.top() == 3);
    s2.pop();
    assert(s2.top() == 2);
    s2.pop();
    assert(s2.top() == 1);
    s2.pop();
    assert(s2.empty());
    s2 = s1;
    assert(s2.top() == 3);
    s2.pop();
    assert(s2.top() == 2);
    s2.pop();
    assert(s2.top() == 1);
    s2.pop();
    assert(s2.empty());
    std::for_each(s2.begin(), s2.end(), Print<int>{});
    std::cout << std::endl;

    // 测试移动构造函数和赋值运算符
    StackContinuous<int> s3{ std::move(s1) };
    std::for_each(s3.begin(), s3.end(), Print<int>{});
    std::cout << std::endl;
    assert(s3.top() == 3);
    s3.pop();
    assert(s3.top() == 2);
    s3.pop();
    assert(s3.top() == 1);
    s3.pop();
    assert(s3.empty());

    // 测试完美转发
    StackContinuous<std::string> s5;
    s5.push("hello");
    assert(s5.top() == "hello");
    s5.push(std::string("world"));
    assert(s5.top() == "world");
    std::for_each(s5.begin(), s5.end(), Print<std::string>{});
    std::cout << std::endl;

    std::cout << "All tests passed!" << std::endl;

    StackDispersed<int> stack;
    std::cout << "Pushing 1, 2, 3" << std::endl;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    std::cout << "Top: " << stack.top() << std::endl;
    std::cout << "Popping top" << std::endl;
    stack.pop();
    std::cout << "Top: " << stack.top() << std::endl;
    std::cout << "Pushing 4" << std::endl;
    stack.push(4);
    std::cout << "Top: " << stack.top() << std::endl;
    std::cout << "Size: " << stack.get_size() << std::endl;
    std::cout << "Empty: " << stack.empty() << std::endl;
    std::cout << "Popping all elements" << std::endl;
    while (!stack.empty()) {
        std::cout << "Popped: " << stack.pop() << std::endl;
    }
    std::cout << "Size: " << stack.get_size() << std::endl;
    std::cout << "Empty: " << stack.empty() << std::endl;
    return 0;

    return 0;
}