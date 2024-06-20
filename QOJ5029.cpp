#include<cstdio>
#include<algorithm>
#include<vector>
#include<random>
#include"path.h"
#include"grader.cpp"
namespace Solve
{
    using namespace std;
    const int N=1000001;
    int n,d[N],f[N],fa[N];
    vector<int> p;
    bool g[N],h[N];
    int rnd(int x,int y)
    {
        static std::mt19937 rd(std::random_device{}());
        return (std::uniform_int_distribution<int>(x,y))(rd);
    }
    int find(int x)
    {
        if(fa[x]==x) return x;
        return fa[x]=find(fa[x]);
    }
    int solve(int x1,int x2)
    {
        p.clear();
        for(int i=1;i<=n;++i) f[i]=1,g[i]=false,fa[i]=i;
        p.push_back(x1);
        p.push_back(x2);
        for(int i=1;i<=n;++i)
        {
            if(i==x1||i==x2) continue;
            if(ask(x1,i,x2)==i) p.push_back(i);
        }
        while(!p.empty())
        {
            int u=rnd(1,n),x=0;
            while(g[u]) u=rnd(1,n);
            for(auto j:p)
            {
                if(x==0) x=j;
                int z=ask(u,x,j);
                if(z) x=z;
            }
            if(x==0) x=x1;
            int v=0,w=0;
            for(int i=1;i<=n;++i)
            {
                if(x==i||g[i]) continue;
                if(v==0) v=i,w+=f[i];
                else
                {
                    int z=ask(v,x,i);
                    if(z==x) w-=f[i];
                    else w+=f[i];
                    if(w==0) v=0;
                    else if(w<0) w=-w,v=i;
                }
            }
            if(v==0) return x;
            for(int i=1;i<=n;++i) h[i]=false;
            for(auto i:p) h[i]=true;
            vector<int> q;
            w=0;
            for(int i=1;i<=n;++i)
            {
                if(x==i||g[i]) continue;
                int z=ask(v,x,i);
                if(z!=x)
                {
                    w+=f[i];
                    if(h[i]) q.push_back(i);
                }
                else
                {
                    f[x]+=f[i];
                    g[i]=true;
                }
            }
            if(w<=n/2) return x;
            swap(p,q);
        }
        return 0;
    }
    int main(int id,int _n)
    {
        n=_n;
        if(n==3) return ask(1,2,3);
        if(id==5)
        {
            int x=1,y=2;
            for(int i=1;i<=n;++i)
            {
                int z=ask(x,y,i);
                if(z==x) x=i;
                if(z==y) y=i;
            }
            for(int i=1;i<=n;++i) d[i]=i;
            nth_element(d+1,d+(n+1)/2,d+n+1,[&](int a,int b){
                return ask(x,a,b)==a;
            });
            return d[(n+1)/2];
        }
        while(true)
        {
            int z=solve(rnd(1,n),rnd(1,n));
            if(z) return z;
        }
        return 0;
    }
}
int centroid(int id,int N,int M){
	return Solve::main(id,N);
}
