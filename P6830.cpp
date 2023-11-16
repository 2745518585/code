#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
void build(vector<vector<int>> b);
namespace Solve
{
    const int N=2001;
    int n,a[N][N],d[N],r[N],fa[N];
    int find(int x)
    {
        if(fa[x]==x) return x;
        return fa[x]=find(fa[x]);
    }
    int construct(vector<vector<int>> a)
    {
        n=a.size();
        vector<vector<int>> b;
        b.resize(n);
        for(int i=1;i<=n;++i) b[i-1].resize(n);
        for(int i=1;i<=n;++i)
        {
            for(int j=1;j<=n;++j)
            {
                b[i-1][j-1]=0;
                if(a[i-1][j-1]==3) return 0;
            }
            if(a[i-1][i-1]!=1) return 0;
        }
        for(int i=1;i<=n;++i) fa[i]=i;
        for(int i=1;i<=n;++i)
        {
            for(int j=1;j<=n;++j)
            {
                if(a[i-1][j-1]==1)
                {
                    if(find(i)!=find(j))
                    {
                        fa[find(i)]=find(j),b[i-1][j-1]=b[j-1][i-1]=1;
                    }
                }
            }
        }
        for(int i=1;i<=n;++i)
        {
            for(int j=1;j<=n;++j)
            {
                if((find(i)==find(j))^(a[i-1][j-1]==1)) return 0;
            }
        }
        for(int i=1;i<=n;++i) r[i]=find(i),fa[i]=i;
        for(int i=1;i<=n;++i)
        {
            for(int j=1;j<=n;++j)
            {
                if(a[i-1][j-1]==2) fa[find(r[i])]=find(r[j]);
            }
        }
        for(int i=1;i<=n;++i)
        {
            for(int j=1;j<=n;++j)
            {
                if((r[i]!=r[j]&&find(r[i])==find(r[j]))^(a[i-1][j-1]==2)) return 0;
            }
        }
        for(int i=1;i<=n;++i)
        {
            if(r[i]!=i) continue;
            if(find(r[i])==i) d[find(r[i])]=i;
        }
        for(int i=1;i<=n;++i)
        {
            if(r[i]!=i) continue;
            if(find(r[i])==i) continue;
            b[d[find(r[i])]-1][i-1]=b[i-1][d[find(r[i])]-1]=1;
            d[find(r[i])]=i;
        }
        for(int i=1;i<=n;++i)
        {
            if(r[i]!=i) continue;
            if(find(r[i])==i&&d[find(r[i])]!=i)
            {
                if(b[d[find(r[i])]-1][i-1]==1) return 0;
                b[d[find(r[i])]-1][i-1]=b[i-1][d[find(r[i])]-1]=1;
            }
        }
        build(b);
        return 1;
    }
}
int construct(vector<vector<int>> a)
{
    return Solve::construct(a);
}