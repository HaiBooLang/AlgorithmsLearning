#pragma once

namespace UnionFind
{

    class UnionFind {
    public:
        virtual void Union(int p, int q) = 0;                       // ��Ԫ�� p ���ڵļ��Ϻ�Ԫ�� q ���ڵļ��Ϻϲ�
        virtual void Delete(int p, int q) = 0;                      // ��Ԫ�� p ���ڵļ��Ϻ�Ԫ�� q ���ڵļ��Ϸ���
        virtual bool Connected(int p, int q) = 0;                   // �ж�Ԫ�� p ��Ԫ�� q �Ƿ���ͬһ��������
        virtual int Root(int p) = 0;                                // ����Ԫ�� p ���ڵļ��ϵĸ��ڵ�
    };

}