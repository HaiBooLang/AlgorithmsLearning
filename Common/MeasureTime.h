/*
 * 文件名: MeasureTime.h
 * 作者: HaiBooLang
 * 创建日期: 2023-11-18
 * 描述: 这个文件包含了一些用于测量和比较函数执行时间的模板函数。
 */
#pragma once

#include <typeinfo>
#include <map>
#include <vector>
#include <functional>
#include <chrono>
#include <iostream>
#include <algorithm>
#include <string>
#include <iomanip>
#include <cassert>

#include "DataSets.h"

// measure_time 函数接受一个函数和一些参数，执行该函数，并返回执行时间（以纳秒为单位）。
template <typename Func, typename... Args>
inline auto measure_time(Func &&func, Args &&...args)
{
	auto start = std::chrono::high_resolution_clock::now();

	std::forward<Func>(func)(std::forward<Args>(args)...);

	auto end = std::chrono::high_resolution_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

	return duration.count();
}

// compare_functions 函数接受一个函数列表和一些数据，对每个函数使用相同的数据执行指定次数，然后比较它们的平均执行时间。
template <typename DataType>
inline void compare_functions(const std::vector<std::pair<std::string, std::function<void(DataType &)>>> &functions, DataType data, const int times = 1)
{
	struct TimePair
	{
		std::string name;
		decltype(std::chrono::nanoseconds().count()) time;
	};

	std::vector<TimePair> records;
	records.reserve(functions.size());

	for (const auto &func : functions)
	{
		decltype(std::chrono::nanoseconds().count()) time = 0;
		for (int i = 0; i < times; ++i)
		{
			DataType temp_data = data;
			time += measure_time(func.second, temp_data);
			assert(std::is_sorted(std::begin(temp_data), std::end(temp_data)));
		}
		records.push_back({std::move(func.first), time / times});
	}

	std::sort(records.begin(), records.end(), [](const TimePair &a, const TimePair &b)
			  { return a.time < b.time; });

	std::cout << std::left << std::setw(40) << "Function"
			  << "Time taken (ns)\n";
	for (const auto &record : records)
	{
		std::cout << std::left << std::setw(40) << record.name
				  << std::setw(20) << record.time
				  << std::setw(20) << 100.0 * record.time / records[0].time << "\n";
	}
}

// get_type_name 函数返回给定类型的名称。
template <typename T>
inline std::string get_type_name()
{
	static const std::map<std::string, std::string> type_names =
		{
			{typeid(std::vector<int>).name(), "vector<int>"},
			{typeid(std::vector<double>).name(), "vector<double>"},
			{typeid(std::vector<float>).name(), "vector<float>"},
		};

	auto iterator = type_names.find(typeid(T).name());
	if (iterator != type_names.end())
	{
		return iterator->second;
	}
	else
	{
		return typeid(T).name();
	}
}

// get_current_time 函数返回当前时间。
inline std::tm get_current_time()
{
	auto current_time_point = std::chrono::system_clock::now();
	std::time_t current_time_time_t = std::chrono::system_clock::to_time_t(current_time_point);
	std::tm current_time_struct;
	localtime_s(&current_time_struct, &current_time_time_t);
	return current_time_struct;
}

// compare_with_all_datasets 函数接受一个函数列表，对每个函数使用各种不同的数据集执行指定次数，然后比较它们的平均执行时间。
template <typename DataType>
inline void compare_with_all_datasets(const std::vector<std::pair<std::string, std::function<void(DataType &)>>> &functions, const int size = 100, const int times = 2)
{
	std::vector<std::pair<std::string, std::function<std::vector<int>(int)>>> datasets =
		{
			{"sorted", generate_sorted_data},
			{"partially sorted", generate_partially_sorted_data},
			{"reversed", generate_reversed_data},
			{"constant", generate_constant_data},
			{"few unique", generate_few_unique_data},
		};

	std::tm current_time_struct = get_current_time();

	std::cout << std::left << std::setw(20) << "Current time: " << std::put_time(&current_time_struct, "%Y-%m-%d %H:%M:%S") << "\n"
			  << std::left << std::setw(20) << "Data size: " << size << " " << get_type_name<DataType>() << "\n";

	for (const auto &[dataset_name, generate_data] : datasets)
	{
		std::cout << "========================================\n\n";
		std::cout << "Testing with " << dataset_name << " data:\n";
		DataType data = generate_data(size);
		compare_functions(functions, data, times);
		std::cout << std::endl;
	}
}