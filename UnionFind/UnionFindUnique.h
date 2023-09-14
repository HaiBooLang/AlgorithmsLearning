#pragma once

#include <memory>
#include <numeric>

// 基于并查集的数据结构
class UnionFindUnique
{
private:
    std::size_t size = 0;                           // 元素的数量
    std::unique_ptr<int[]> parent;                  // 存储每个元素的父节点
    std::unique_ptr<int[]> rank;                    // 存储每个集合的大小（即根节点的子节点数）
public:
    explicit UnionFindUnique(std::size_t N);
    void Union(int p, int q);                       // 将元素 p 所在的集合和元素 q 所在的集合合并
    void Delete(int p, int q);                      // 将元素 p 所在的集合和元素 q 所在的集合分离
    bool connected(int p, int q);                   // 判断元素 p 和元素 q 是否在同一个集合中
    int root(int p);                                // 查找元素 p 所在的集合的根节点
};

inline UnionFindUnique::UnionFindUnique(std::size_t N)
    : size{ N }, parent(std::make_unique<int[]>(N)), rank(std::make_unique<int[]>(N))   // 初始化列表初始化 size、parent 和 rank 成员变量
                                                                                        // parent 和 rank 都是使用 std::unique_ptr 类型的智能指针管理的动态数组
{
    std::fill_n(rank.get(), N, 1);                                          // 将 rank 数组中的所有元素初始化为 1
    std::generate_n(parent.get(), N, [n = 0]() mutable { return n++; });    // 将 parent 数组中的元素初始化为 0 到 N-1 的连续整数
}

inline int UnionFindUnique::root(int p) // 
{
    while (p != parent[p])
    {
        parent[p] = parent[parent[p]];  // 路径压缩，将元素 p 到根节点路径上的所有节点的父节点都直接指向根节点，从而加速后续查找操作
        p = parent[p];                  // 查找元素 p 的根节点
    }
    return p;
}

inline bool UnionFindUnique::connected(int p, int q)
{
    return root(p) == root(q);          // 判断元素 p 和元素 q 所在的集合的根节点是否相同
}

inline void UnionFindUnique::Union(int p, int q)
{
    int rootP = root(p);                // 查找元素 p 和元素 q 所在的集合的根节点
    int rootQ = root(q);
    if (rootP == rootQ) return;         // 如果它们已经在同一个集合中，则不需要进行任何操作
    if (rank[rootP] < rank[rootQ])      // 否则，将两个集合合并，将元素数量较少的集合合并到元素数量较多的集合中，并更新根节点的子节点数
    {
                                        // 如果集合 rootP 的大小小于集合 rootQ 的大小
        parent[rootP] = rootQ;          // 则将集合 rootP 的根节点指向集合 rootQ 的根节点
        rank[rootQ] += rank[rootP];     // 并将集合 rootQ 的大小增加 rootP 的大小
    }
    else {
        parent[rootQ] = rootP;
        rank[rootP] += rank[rootQ];
    }
}

inline void UnionFindUnique::Delete(int p, int q)
{
    int rootP = root(p);
    int rootQ = root(q);
    if (rootP == rootQ) return;
    if (rank[rootP] < rank[rootQ]) 
    {
        parent[rootP] = rootP;
        rank[rootQ] -= rank[rootP];
    }
    else 
    {
        parent[rootQ] = rootQ;
        rank[rootP] -= rank[rootQ];
    }
}