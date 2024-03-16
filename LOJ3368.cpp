#include<cstdio>
#include<algorithm>
#include<vector>
#include"mushrooms.h"
namespace Solve
{
    using namespace std;
    const int N=100001;
    int n;
    vector<int> a[2],b;
    int query(vector<int> x)
    {
        return use_machine(x);
    }
    void solve1(int t)
    {
        int p=b.back();
        b.pop_back();
        int x=a[t][0];
        if(query({x,p})==0) a[t].push_back(p);
        else a[t^1].push_back(p);
    }
    void solve2(int t)
    {
        int p1=b.back();
        b.pop_back();
        int p2=b.back();
        b.pop_back();
        int x=a[t][0],y=a[t][1];
        int k=query({x,p1,y,p2});
        if((k/2)%2==0) a[t].push_back(p1);
        else a[t^1].push_back(p1);
        if(k%2==0) a[t].push_back(p2);
        else a[t^1].push_back(p2);
    }
    void solve3(int t)
    {
        int p1=b.back();
        b.pop_back();
        int p2=b.back();
        b.pop_back();
        int p3=b.back();
        b.pop_back();
        int x=a[t][0],y=a[t][1],z=a[t][2];
        int k=query({x,p1,y,p2,z,p3});
        if(k%2==0) a[t].push_back(p3);
        else a[t^1].push_back(p3);
        if((k/2)%2==0)
        {
            if((k/4)%2==0) a[t].push_back(p1),a[t].push_back(p2);
            else a[t^1].push_back(p1),a[t^1].push_back(p2);
            return;
        }
        if(a[t^1].size()<2)
        {
            k=query({x,p1});
            if(k%2==0) a[t].push_back(p1),a[t^1].push_back(p2);
            else a[t^1].push_back(p1),a[t].push_back(p2);
            return;
        }
        int p4=b.back();
        b.pop_back();
        int p5=b.back();
        b.pop_back();
        int u=a[t^1][0],v=a[t^1][1];
        k=query({x,p1,y,p4,z,u,p2,v,p5})-1;
        if(k%2==0) a[t^1].push_back(p5);
        else a[t].push_back(p5);
        if((k/2)%2==0) a[t].push_back(p4);
        else a[t^1].push_back(p4);
        if((k/4)%2==0) a[t].push_back(p1),a[t^1].push_back(p2);
        else a[t^1].push_back(p1),a[t].push_back(p2);
    }
    int main(int _n)
    {
        n=_n;
        a[0].push_back(0);
        for(int i=1;i<=n-1;++i) b.push_back(i);
        if(n<=200)
        {
            int s=1;
            for(int i=1;i<=n-1;++i)
            {
                if(query({0,i})==0) ++s;
            }
            return s;
        }
        while(max(a[0].size(),a[1].size())<110&&b.size()>0)
        {
            int t=a[0].size()>a[1].size()?0:1;
            if(a[t].size()>=3&&b.size()>=5) solve3(t);
            else if(a[t].size()>=2&&b.size()>=2) solve2(t);
            else solve1(t);
        }
        int s=0;
        while(b.size()>0)
        {
            int t=a[0].size()>a[1].size()?0:1;
            vector<int> p;
            for(auto i:a[t])
            {
                if(b.size()==0) break;
                p.push_back(i);
                p.push_back(b.back());
                b.pop_back();
            }
            int k=query(p);
            if(t==0) s+=(p.size()/2-1)-k/2;
            else s+=k/2;
            a[t^(k%2)].push_back(p.back());
        }
        return a[0].size()+s;
    }
}
int count_mushrooms(int n)
{
    return Solve::main(n);
}