/*
 * 文件名: MainTest.h
 * 作者: HaiBooLang
 * 创建日期: 2023-11-18
 * 这个文件是程序的入口点，它调用了一些测试函数来测试不同的算法，包括并查集、搜索和排序等。
 */
#pragma once

#include "UnionFind/TestUnionFind.h"
#include "Search/TestSearch.h"
#include "Sort/TestSort.h"

int main()
{
	//UnionFind::test_union_find(2);
	//Search::test_binary_search(100000000);
	Sort::test_sort(100000,2);
	//Search::test_search();                                                                 
}