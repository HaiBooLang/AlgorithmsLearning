#pragma once

namespace UnionFind
{

    class UnionFind
    {
    public:
        virtual void Union(int p, int q) = 0;     // 将元素 p 所在的集合和元素 q 所在的集合合并
        virtual void Delete(int p, int q) = 0;    // 将元素 p 所在的集合和元素 q 所在的集合分离
        virtual bool Connected(int p, int q) = 0; // 判断元素 p 和元素 q 是否在同一个集合中
        virtual int Root(int p) = 0;              // 查找元素 p 所在的集合的根节点
    };

}