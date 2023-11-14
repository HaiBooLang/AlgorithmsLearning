#pragma once

#include <iterator>
#include <vector>
#include <array>
#include <list>
#include <deque>

namespace Sort
{

    template<std::ranges::random_access_range Container>
    constexpr void selection_sort(Container& c)
    {
        for (auto i = std::begin(c); i != std::end(c); ++i)
        {
            auto min_element = std::min_element(i, std::end(c));
            if (*min_element < *i)
            {
                std::iter_swap(i, min_element);
            }
        }
    }

    template<std::random_access_iterator InputIt>
    constexpr void selection_sort(InputIt first, InputIt last)
    {
        for (auto i = first; i != last; ++i)
        {
            auto min_element = std::min_element(i, last);
            if (*min_element < *i)
            {
                std::iter_swap(i, min_element);
            }
        }
    }

}