#include <iterator>

namespace Search
{

    template<class InputIt, class T>
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

}