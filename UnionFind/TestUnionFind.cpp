#include "TestUnionFind.h"
#include "../MeasureTime.h"

void UnionFind::test_union_find(int&& times)
{
    const int size = 10;

    std::mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> dist(0, size - 1);

    decltype(std::chrono::nanoseconds().count()) union_total_time = 0;
    decltype(std::chrono::nanoseconds().count()) isconnected_total_time = 0;
    decltype(std::chrono::nanoseconds().count()) duration = 0;

    union_total_time = 0;
    isconnected_total_time = 0;
    for (int i = 0; i < times; ++i) {
        UnionFindUnique uf(size);

        duration = 0;
        for (int i = 0; i < size; i++) {
            int p = dist(gen);
            int q = dist(gen);
            duration += measure_time([&]() { uf.Union(p, q); });
        }
        std::cout << "UnionFindUnique: Time taken for Union: " << duration << " ns" << std::endl;
        union_total_time += duration;

        duration = 0;
        for (int i = 0; i < size; i++) {
            int p = dist(gen);
            int q = dist(gen);
            duration += measure_time([&]() { uf.Connected(p, q); });
        }
        std::cout << "UnionFindUnique: Time taken for connected: " << duration << " ns" << std::endl;
        isconnected_total_time += duration;
    }
    std::cout << "UnionFindUnique: Average time taken for Union: " << union_total_time / times << " ns" << std::endl;
    std::cout << "UnionFindUnique: Average time taken for connected: " << isconnected_total_time / times << " ns" << std::endl;

    union_total_time = 0;
    isconnected_total_time = 0;
    for (int i = 0; i < times; ++i) {
        UnionFindVector uf(size);

        duration = 0;
        for (int i = 0; i < size; i++) {
            int p = dist(gen);
            int q = dist(gen);
            duration += measure_time([&]() { uf.Union(p, q); });
        }
        std::cout << "UnionFindVector: Time taken for Union: " << duration << " ns" << std::endl;
        union_total_time += duration;

        duration = 0;
        for (int i = 0; i < size; i++) {
            int p = dist(gen);
            int q = dist(gen);
            duration += measure_time([&]() { uf.Connected(p, q); });
        }
        std::cout << "UnionFindVector: Time taken for connected: " << duration << " ns" << std::endl;
        isconnected_total_time += duration;
    }
    std::cout << "UnionFindVector: Average time taken for Union: " << union_total_time / times << " ns" << std::endl;
    std::cout << "UnionFindVector: Average time taken for connected: " << isconnected_total_time / times << " ns" << std::endl;

    union_total_time = 0;
    isconnected_total_time = 0;
    for (int i = 0; i < times; ++i) {
        UnionFindArray<size> uf{};

        duration = 0;
        for (int i = 0; i < size; i++) {
            int p = dist(gen);
            int q = dist(gen);
            duration += measure_time([&]() { uf.Union(p, q); });
        }
        std::cout << "UnionFindArray: Time taken for Union: " << duration << " ns" << std::endl;
        union_total_time += duration;

        duration = 0;
        for (int i = 0; i < size; i++) {
            int p = dist(gen);
            int q = dist(gen);
            duration += measure_time([&]() { uf.Connected(p, q); });
        }
        std::cout << "UnionFindArray: Time taken for connected: " << duration << " ns" << std::endl;
        isconnected_total_time += duration;
    }
    std::cout << "UnionFindArray: Average time taken for Union: " << union_total_time / times << " ns" << std::endl;
    std::cout << "UnionFindArray: Average time taken for connected: " << isconnected_total_time / times << " ns" << std::endl;
}