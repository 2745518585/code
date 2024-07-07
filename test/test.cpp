#include<bits/stdc++.h>
#include"grader.cpp"
#include"pen.h"
namespace Solve
{
    using namespace std;
    int n,a[101];
    bool h[101];
    int rnd(int x,int y)
    {
        static mt19937 gen(random_device{}());
        return uniform_int_distribution<int>(x,y)(gen);
    }
    pair<int,int> rnd_pair(int x,int y)
    {
        int s1=rnd(x,y),s2=rnd(x,y);
        while(s1==s2) s2=rnd(x,y);
        return make_pair(s1,s2);
    }
    pair<int,int> main(int _n)
    {
        n=_n;
        for(int i=0;i<=n-1;++i) a[i]=-1,h[i]=true;
        int x=0;
        for(int i=0;i<=n-1;++i)
        {
            for(int j=0;j<=n-1;++j)
            {
                if(!h[j]) continue;
                while(a[j]<i) h[j]&=write(j),++a[j];
                if(!h[j]) break;
            }
            int x1=-1,x2=-1;
            for(int i=0;i<=n-1;++i)
            {
                if(!h[i]) continue;
                if(x1==-1||a[i]<a[x1]) x2=x1,x1=i;
                else if(x2==-1||a[i]<a[x2]) x2=i;
            }
            if(n+i-a[x1]-a[x2]>n+4||i==5) return make_pair(x1,x2);
        }
    }
}
std::pair<int,int> solve(int n)
{
    return Solve::main(n);
}
