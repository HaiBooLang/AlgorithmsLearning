#include <iostream>
#include <random>
#include <chrono>
#include "UnionFindUnique.h"
#include "UnionFindArray.h"
#include "UnionFindVector.h"

int main()
{
    const int size = 20000000;
    const int times = 10;
    std::mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> dist(0, size - 1);

    decltype(std::chrono::milliseconds().count()) union_total_time = 0;
    decltype(std::chrono::milliseconds().count()) isconnected_total_time = 0;
    decltype(std::chrono::high_resolution_clock::now()) start_time;
    decltype(std::chrono::high_resolution_clock::now()) end_time;
    decltype(std::chrono::milliseconds().count()) duration;

    for (int i = 0; i < times; ++i) {
        UnionFindUnique uf(size);

        start_time = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < size; i++) {
            int p = dist(gen);
            int q = dist(gen);
            uf.Union(p, q);
        }
        end_time = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
        std::cout << "UnionFindUnique: Time taken for Union: " << duration << " ms" << std::endl;
        union_total_time += duration;

        start_time = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < size; i++) {
            int p = dist(gen);
            int q = dist(gen);
            uf.connected(p, q);
        }
        end_time = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
        std::cout << "UnionFindUnique: Time taken for connected: " << duration << " ms" << std::endl;
        isconnected_total_time += duration;
    }

    std::cout << "UnionFindUnique: Average time taken for Union: " << union_total_time / times << " ms" << std::endl;
    std::cout << "UnionFindUnique: Average time taken for connected: " << isconnected_total_time / times << " ms" << std::endl;

    union_total_time = 0;
    isconnected_total_time = 0;

    for (int i = 0; i < times; ++i) {
        UnionFindVector uf(size);

        start_time = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < size; i++) {
            int p = dist(gen);
            int q = dist(gen);
            uf.Union(p, q);
        }
        end_time = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
        std::cout << "UnionFindVector: Time taken for Union: " << duration << " ms" << std::endl;
        union_total_time += duration;

        start_time = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < size; i++) {
            int p = dist(gen);
            int q = dist(gen);
            uf.connected(p, q);
        }
        end_time = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
        std::cout << "UnionFindVector: Time taken for connected: " << duration << " ms" << std::endl;
        isconnected_total_time += duration;
    }

    std::cout << "UnionFindVector: Average time taken for Union: " << union_total_time / times << " ms" << std::endl;
    std::cout << "UnionFindVector: Average time taken for connected: " << isconnected_total_time / times << " ms" << std::endl;

    union_total_time = 0;
    isconnected_total_time = 0;

    for (int i = 0; i < times; ++i) {
        UnionFindArray<size> uf{};

        start_time = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < size; i++) {
            int p = dist(gen);
            int q = dist(gen);
            uf.Union(p, q);
        }
        end_time = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
        std::cout << "UnionFindArray: Time taken for Union: " << duration << " ms" << std::endl;
        union_total_time += duration;

        start_time = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < size; i++) {
            int p = dist(gen);
            int q = dist(gen);
            uf.connected(p, q);
        }
        end_time = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
        std::cout << "UnionFindArray: Time taken for connected: " << duration << " ms" << std::endl;
        isconnected_total_time += duration;
    }

    std::cout << "UnionFindArray: Average time taken for Union: " << union_total_time / times << " ms" << std::endl;
    std::cout << "UnionFindArray: Average time taken for connected: " << isconnected_total_time / times << " ms" << std::endl;

    return 0;
}