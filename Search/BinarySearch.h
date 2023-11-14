#include <iterator>
#include <vector>
#include <array>
#include <list>
#include <deque>

namespace Search
{

    template<std::ranges::random_access_range Container, class T>
    constexpr auto binary_search(Container& c, const T& value)
    {
        auto first = std::begin(c);
        auto last = std::end(c);

        while (first != last)
        {
            auto mid = std::next(first, std::distance(first, last) / 2);

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

    template<std::random_access_iterator InputIt, class T>
    constexpr InputIt binary_search(InputIt first, InputIt last, const T& value)
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

    //template<class T, std::size_t N>
    //constexpr T* binary_search(T(&arr)[N], const T& value)
    //{
    //    return binary_search(std::begin(arr), std::end(arr), value);
    //}

    //template<class T>
    //constexpr typename std::vector<T>::iterator binary_search(std::vector<T>& vec, const T& value)
    //{
    //    return binary_search(vec.begin(), vec.end(), value);
    //}

    //template<class T, std::size_t N>
    //constexpr typename std::array<T, N>::iterator binary_search(std::array<T, N>& arr, const T& value)
    //{
    //    return binary_search(arr.begin(), arr.end(), value);
    //}

    //template<class T>
    //constexpr typename std::list<T>::iterator binary_search(std::list<T>& lst, const T& value)
    //{
    //    return binary_search(lst.begin(), lst.end(), value);
    //}

    //template<class T>
    //constexpr typename std::deque<T>::iterator binary_search(std::deque<T>& deq, const T& value)
    //{
    //    return binary_search(deq.begin(), deq.end(), value);
    //}

}