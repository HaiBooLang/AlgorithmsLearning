#pragma once

#include <vector>
#include <functional>
#include <chrono>
#include <iostream>
#include <algorithm>
#include <string>

template<typename Func, typename... Args>
auto measure_time(Func&& func, Args&&... args) {
	auto start = std::chrono::high_resolution_clock::now();

	std::forward<Func>(func)(std::forward<Args>(args)...);

	auto end = std::chrono::high_resolution_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

	return duration.count();
}

template<typename DataType>
void compare_functions(const std::vector<std::pair<std::string, std::function<void(const DataType&)>>>& functions, const DataType& data) {
	struct TimePair {
		std::string name;
		decltype(std::chrono::nanoseconds().count()) time;
	};

	std::vector<TimePair> times;
	times.reserve(functions.size());

	for (const auto& func : functions) {
		auto time = measure_time(func.second, data);
		times.push_back({ std::move(func.first), time });
	}

	std::sort(times.begin(), times.end(), [](const TimePair& a, const TimePair& b) {
		return a.time < b.time;
		});

	for (const auto& time : times) {
		std::cout << "Function: " << time.name << ", Time taken: " << time.time << " ns\n";
	}
}