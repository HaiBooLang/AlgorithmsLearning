#pragma once

#include <algorithm>

namespace std {

    int swap_count = 0;
    int compare_count = 0;
    int increment_count = 0;
    int decrement_count = 0;

    template<typename Iterator>
    void iter_swap(Iterator a, Iterator b)
    {
        std::swap(*a, *b);
        ++swap_count;
    }

    template<typename T>
    bool less(const T& a, const T& b)
    {
        ++compare_count;
        return a < b;
    }

    template<typename Iterator>
    Iterator next(Iterator it)
    {
        ++increment_count;
        return std::next(it);
    }

    template<typename Iterator>
    Iterator prev(Iterator it)
    {
        ++decrement_count;
        return std::prev(it);
    }

}