#pragma once

#include <vector>
#include <numeric>

#include "UnionFInd.h"

namespace UnionFind
{

    class UnionFindVector : public UnionFind
    {
    private:
        std::size_t size = 0;
        std::vector<int> parent;
        std::vector<int> rank;

    public:
        explicit UnionFindVector(std::size_t N);
        void Union(int p, int q);
        void Delete(int p, int q);
        bool Connected(int p, int q);
        int Root(int p);
    };

    inline UnionFindVector::UnionFindVector(std::size_t N)
        : size{N}, parent(N), rank(N, 1)
    {
        std::iota(parent.begin(), parent.end(), 0);
    }

    inline int UnionFindVector::Root(int p)
    {
        while (p != parent[p])
        {
            parent[p] = parent[parent[p]];
            p = parent[p];
        }
        return p;
    }

    inline bool UnionFindVector::Connected(int p, int q)
    {
        return Root(p) == Root(q);
    }

    inline void UnionFindVector::Union(int p, int q)
    {
        int rootP = Root(p);
        int rootQ = Root(q);
        if (rootP == rootQ)
            return;
        if (rank[rootP] < rank[rootQ])
        {
            parent[rootP] = rootQ;
            rank[rootQ] += rank[rootP];
        }
        else
        {
            parent[rootQ] = rootP;
            rank[rootP] += rank[rootQ];
        }
    }

    inline void UnionFindVector::Delete(int p, int q)
    {
        int rootP = Root(p);
        int rootQ = Root(q);
        if (rootP == rootQ)
            return;
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

}