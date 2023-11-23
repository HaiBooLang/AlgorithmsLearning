#pragma once

namespace Status {

    int swap_count = 0;
    int compare_count = 0;
    int increment_count = 0;
    int decrement_count = 0;

    void reset()
    {
        swap_count = compare_count = increment_count = decrement_count = 0;
    }
}


//namespace STD {
//
//    template<typename Iterator>
//    void iter_swap(Iterator a, Iterator b)
//    {
//        std::swap(*a, *b);
//        ++Status::swap_count;
//    }
//
//    template<typename T>
//    bool less(const T& a, const T& b)
//    {
//        ++Status::compare_count;
//        return a < b;
//    }
//
//    template<typename Iterator>
//    Iterator next(Iterator it)
//    {
//        ++Status::increment_count;
//        return std::next(it);
//    }
//
//    template<typename Iterator>
//    Iterator prev(Iterator it)
//    {
//        ++Status::decrement_count;
//        return std::prev(it);
//    }
//
//}