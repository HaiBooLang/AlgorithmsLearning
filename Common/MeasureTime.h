#pragma once

#include <vector>
#include <functional>
#include <chrono>
#include <iostream>
#include <algorithm>
#include <string>

#include "DataSets.h"

template<typename Func, typename... Args>
inline auto measure_time(Func&& func, Args&&... args) {
	auto start = std::chrono::high_resolution_clock::now();

	std::forward<Func>(func)(std::forward<Args>(args)...);

	auto end = std::chrono::high_resolution_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

	return duration.count();
}  

template<typename DataType>
inline void compare_functions(const std::vector<std::pair<std::string, std::function<void(DataType&)>>>& functions, DataType data, const int times = 1) {
	struct TimePair {
		std::string name;
		decltype(std::chrono::nanoseconds().count()) time;
	};

	std::vector<TimePair> records;
	records.reserve(functions.size());

	for (const auto& func : functions) {
		long long time = 0;
		for (int i = 0; i < times; ++i) {
			time += measure_time(func.second, data);
		}
		records.push_back({ std::move(func.first), time/times });
	}

	std::sort(records.begin(), records.end(), [](const TimePair& a, const TimePair& b) {
		return a.time < b.time;
		});

	std::cout << std::left << std::setw(20) << "Function" << "Time taken (ns)\n";
	for (const auto& record : records) {
		std::cout << std::left << std::setw(20) << record.name << record.time << "\n";
	}
}

template<typename DataType>
inline void compare_with_all_datasets(const std::vector<std::pair<std::string, std::function<void(DataType&)>>>& functions, const int size = 100, const int times = 2) {
	std::vector<std::pair<std::string, std::function<std::vector<int>(int)>>> datasets = {
		{"sorted", generate_sorted_data},
		{"partially sorted", generate_partially_sorted_data},
		{"reversed", generate_reversed_data},
		{"constant", generate_constant_data},
		{"few unique", generate_few_unique_data},
	};

	for (const auto& [dataset_name, generate_data] : datasets) {
		std::cout << "========================================\n\n";
		std::cout << "Testing with " << dataset_name << " data:\n";
		DataType data = generate_data(size);
		compare_functions(functions, data, times);
		std::cout << "\n";
	}
}