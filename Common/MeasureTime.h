#pragma once

#include <chrono>

template<typename Func, typename... Args>
auto measure_time(Func&& func, Args&&... args) {
    auto start = std::chrono::high_resolution_clock::now();

    std::forward<Func>(func)(std::forward<Args>(args)...);

    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    return duration.count();
}

