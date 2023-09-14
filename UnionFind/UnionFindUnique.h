#pragma once

#include <memory>
#include <numeric>

// ���ڲ��鼯�����ݽṹ
class UnionFindUnique
{
private:
    std::size_t size = 0;                           // Ԫ�ص�����
    std::unique_ptr<int[]> parent;                  // �洢ÿ��Ԫ�صĸ��ڵ�
    std::unique_ptr<int[]> rank;                    // �洢ÿ�����ϵĴ�С�������ڵ���ӽڵ�����
public:
    explicit UnionFindUnique(std::size_t N);
    void Union(int p, int q);                       // ��Ԫ�� p ���ڵļ��Ϻ�Ԫ�� q ���ڵļ��Ϻϲ�
    void Delete(int p, int q);                      // ��Ԫ�� p ���ڵļ��Ϻ�Ԫ�� q ���ڵļ��Ϸ���
    bool connected(int p, int q);                   // �ж�Ԫ�� p ��Ԫ�� q �Ƿ���ͬһ��������
    int root(int p);                                // ����Ԫ�� p ���ڵļ��ϵĸ��ڵ�
};

inline UnionFindUnique::UnionFindUnique(std::size_t N)
    : size{ N }, parent(std::make_unique<int[]>(N)), rank(std::make_unique<int[]>(N))   // ��ʼ���б��ʼ�� size��parent �� rank ��Ա����
                                                                                        // parent �� rank ����ʹ�� std::unique_ptr ���͵�����ָ�����Ķ�̬����
{
    std::fill_n(rank.get(), N, 1);                                          // �� rank �����е�����Ԫ�س�ʼ��Ϊ 1
    std::generate_n(parent.get(), N, [n = 0]() mutable { return n++; });    // �� parent �����е�Ԫ�س�ʼ��Ϊ 0 �� N-1 ����������
}

inline int UnionFindUnique::root(int p) // 
{
    while (p != parent[p])
    {
        parent[p] = parent[parent[p]];  // ·��ѹ������Ԫ�� p �����ڵ�·���ϵ����нڵ�ĸ��ڵ㶼ֱ��ָ����ڵ㣬�Ӷ����ٺ������Ҳ���
        p = parent[p];                  // ����Ԫ�� p �ĸ��ڵ�
    }
    return p;
}

inline bool UnionFindUnique::connected(int p, int q)
{
    return root(p) == root(q);          // �ж�Ԫ�� p ��Ԫ�� q ���ڵļ��ϵĸ��ڵ��Ƿ���ͬ
}

inline void UnionFindUnique::Union(int p, int q)
{
    int rootP = root(p);                // ����Ԫ�� p ��Ԫ�� q ���ڵļ��ϵĸ��ڵ�
    int rootQ = root(q);
    if (rootP == rootQ) return;         // ��������Ѿ���ͬһ�������У�����Ҫ�����κβ���
    if (rank[rootP] < rank[rootQ])      // ���򣬽��������Ϻϲ�����Ԫ���������ٵļ��Ϻϲ���Ԫ�������϶�ļ����У������¸��ڵ���ӽڵ���
    {
                                        // ������� rootP �Ĵ�СС�ڼ��� rootQ �Ĵ�С
        parent[rootP] = rootQ;          // �򽫼��� rootP �ĸ��ڵ�ָ�򼯺� rootQ �ĸ��ڵ�
        rank[rootQ] += rank[rootP];     // �������� rootQ �Ĵ�С���� rootP �Ĵ�С
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