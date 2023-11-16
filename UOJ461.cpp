#include<cstdio>
#include<algorithm>
#include<vector>
#include"graph.h"
namespace Solve
{
    using namespace std;
    const int N=1001;
    int n;
    bool g[N],h[N][N];
    vector<int> a[N],c1,c2;
    vector<pair<int,int>> a2,b;
    bool abc(int x,int l,int r)
    {
        for(int i=l;i<=r;++i) b.push_back(make_pair(x,i));
        int z=query(b);
        for(int i=l;i<=r;++i) b.pop_back();
        return z;
    }
    void check(int x)
    {
        int p=-1;
        while(true)
        {
            if(abc(x,p+1,x-1)==true)
            {
                for(int i=p+1;i<=x-1;++i) b.push_back(make_pair(x,i));
                break;
            }
            int l=p+1,r=x-1;
            while(l<r)
            {
                int z=l+r>>1;
                if(abc(x,p+1,z)==false) r=z;
                else l=z+1;
            }
            for(int i=p+1;i<=l-1;++i) b.push_back(make_pair(x,i));
            p=l;
            a[x].push_back(p);
            a[p].push_back(x);
            a2.push_back(make_pair(x,p));
            h[x][p]=h[p][x]=true;
        }
    }
    void dfs(int x,int w)
    {
        if(g[x]) return;
        g[x]=true;
        if(w==0) c1.push_back(x);
        else c2.push_back(x);
        for(auto i:a[x]) dfs(i,w^1);
    }
    std::vector<int> solve(int _n)
    {
        n=_n;
        for(int i=0;i<=n-1;++i) check(i);
        dfs(0,0);
        b.clear();
        for(auto i:c1)
        {
            for(auto j:c2)
            {
                if(h[i][j]==false) b.push_back(make_pair(i,j));
            }
        }
        for(auto i:a2)
        {
            b.push_back(make_pair(i.first,i.second));
            if(query(b)==true) return vector<int>();
            b.pop_back();
        }
        return c1;
    }
}
std::vector<int> check_bipartite(int vsize)
{
    return Solve::solve(vsize);
}