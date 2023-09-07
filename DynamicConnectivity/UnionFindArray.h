#pragma once

#include <array>
#include <numeric>
#include <memory>

template<std::size_t N>
class UnionFindArray
{
private:
    std::unique_ptr<std::array<int, N>> parent;
    std::unique_ptr<std::array<int, N>> rank;
public:
    explicit UnionFindArray();
    void Union(int p, int q);
    void Delete(int p, int q);
    bool isConnected(int p, int q);
    int root(int p);
};

template<std::size_t N>
inline UnionFindArray<N>::UnionFindArray()
    :parent{ std::make_unique<std::array<int, N>>() }, rank{ std::make_unique<std::array<int, N>>() }
{
    std::iota(parent->begin(), parent->end(), 0);
    std::fill(rank->begin(), rank->end(), 1);
}

template<std::size_t N>
inline int UnionFindArray<N>::root(int p)
{
    while (p != (*parent)[p])
    {
        (*parent)[p] = (*parent)[(*parent)[p]];
        p = (*parent)[p];
    }
    return p;
}

template<std::size_t N>
inline bool UnionFindArray<N>::isConnected(int p, int q)
{
    return root(p) == root(q);
}

template<std::size_t N>
inline void UnionFindArray<N>::Union(int p, int q)
{
    int rootP = root(p);
    int rootQ = root(q);
    if (rootP == rootQ) return;
    if ((*rank)[rootP] < (*rank)[rootQ])
    {
        (*parent)[rootP] = rootQ;
        (*rank)[rootQ] += (*rank)[rootP];
    }
    else
    {
        (*parent)[rootQ] = rootP;
        (*rank)[rootP] += (*rank)[rootQ];
    }
}

template<std::size_t N>
inline void UnionFindArray<N>::Delete(int p, int q)
{
    int rootP = root(p);
    int rootQ = root(q);
    if (rootP == rootQ) return;
    if ((*rank)[rootP] < (*rank)[rootQ])
    {
        (*parent)[rootP] = rootQ;
        (*rank)[rootQ] -= (*rank)[rootP];
    }
    else
    {
        (*parent)[rootQ] = rootP;
        (*rank)[rootP] -= (*rank)[rootQ];
    }
}