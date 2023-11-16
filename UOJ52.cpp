#include<cstdio>
#include<algorithm>
#include"kth.h"
namespace Solve
{
    using namespace std;
    int solve(int n1,int n2,int n3,int k)
    {
        int t1=0,t2=0,t3=0,s=0;
        while(k>=3)
        {
            int z1=get_a(t1+k/3-1),z2=get_b(t2+k/3-1),z3=get_c(t3+k/3-1);
            if(z1<=z2&&z1<=z3) t1+=k/3,s=max(s,z1);
            else if(z2<=z3) t2+=k/3,s=max(s,z2);
            else t3+=k/3,s=max(s,z3);
            k-=k/3;
        }
        if(k>0)
        {
            int z1=get_a(t1),z2=get_b(t2),z3=get_c(t3);
            if(z1<=z2&&z1<=z3) t1+=1,s=max(s,z1);
            else if(z2<=z3) t2+=1,s=max(s,z2);
            else t3+=1,s=max(s,z3);
            --k;
        }
        if(k>0)
        {
            int z1=get_a(t1),z2=get_b(t2),z3=get_c(t3);
            if(z1<=z2&&z1<=z3) t1+=1,s=max(s,z1);
            else if(z2<=z3) t2+=1,s=max(s,z2);
            else t3+=1,s=max(s,z3);
            --k;
        }
        return s;
    }
}
int query_kth(int n_a, int n_b, int n_c, int k)
{
    return Solve::solve(n_a,n_b,n_c,k);
}