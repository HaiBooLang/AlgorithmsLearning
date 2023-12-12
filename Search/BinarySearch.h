#include <iterator>
#include <vector>
#include <array>
#include <list>
#include <deque>

namespace Search
{

    // 定义一个名为 binary_search 的模板函数
    // 它接受一个随机访问范围（例如，数组或向量）和一个要查找的值
    template <std::ranges::random_access_range Container, class T>
    constexpr auto binary_search(Container &c, const T &value)
    {
        // 获取容器的开始和结束迭代器
        auto first = std::begin(c);
        auto last = std::end(c);

        // 只要开始迭代器不等于结束迭代器，就继续循环
        while (first != last)
        {
            // 计算中间元素的迭代器
            auto mid = std::next(first, std::distance(first, last) / 2);

            // 如果中间元素等于要查找的值，就返回中间元素的迭代器
            if (*mid == value)
            {
                return mid;
            }
            // 如果中间元素小于要查找的值，就将开始迭代器设置为中间元素之后的位置
            else if (*mid < value)
            {
                first = std::next(mid);
            }
            // 如果中间元素大于要查找的值，就将结束迭代器设置为中间元素的位置
            else
            {
                last = mid;
            }
        }

        // 如果没有找到要查找的值，就返回结束迭代器
        return last;
    }

    template <std::random_access_iterator InputIt, class T>
    constexpr InputIt binary_search(InputIt first, InputIt last, const T &value)
    {
        while (first != last)
        {
            InputIt mid = std::next(first, std::distance(first, last) / 2);

            if (*mid == value)
            {
                return mid;
            }
            else if (*mid < value)
            {
                first = std::next(mid);
            }
            else
            {
                last = mid;
            }
        }

        return last;
    }

    // template<class T, std::size_t N>
    // constexpr T* binary_search(T(&arr)[N], const T& value)
    //{
    //     return binary_search(std::begin(arr), std::end(arr), value);
    // }

    // template<class T>
    // constexpr typename std::vector<T>::iterator binary_search(std::vector<T>& vec, const T& value)
    //{
    //     return binary_search(vec.begin(), vec.end(), value);
    // }

    // template<class T, std::size_t N>
    // constexpr typename std::array<T, N>::iterator binary_search(std::array<T, N>& arr, const T& value)
    //{
    //     return binary_search(arr.begin(), arr.end(), value);
    // }

    // template<class T>
    // constexpr typename std::list<T>::iterator binary_search(std::list<T>& lst, const T& value)
    //{
    //     return binary_search(lst.begin(), lst.end(), value);
    // }

    // template<class T>
    // constexpr typename std::deque<T>::iterator binary_search(std::deque<T>& deq, const T& value)
    //{
    //     return binary_search(deq.begin(), deq.end(), value);
    // }

}