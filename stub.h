#pragma once

#include <algorithm>

namespace std {

    int swap_count = 0;

    template<typename Iterator>
    void iter_swap(Iterator a, Iterator b)
    {
        std::swap(*a, *b);
        ++swap_count;
    }

}