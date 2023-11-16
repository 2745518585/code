#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=50001,M=201,K=31;
int n,q,b[N],c[N],d[N],e[N],fa[N][K];
ll f[N][M];
vector<int> a[N];
void dfs(int x,int w)
{
    d[x]=d[fa[x][0]]+1;
    e[d[x]]=x;
    for(int i=1;i<=q;++i)
    {
        if(d[x]-i>=1) f[x][i]=f[e[d[x]-i]][i];
        f[x][i]+=c[x];
    }
    for(auto i:a[x])
    {
        if(i==fa[x][0]) continue;
        fa[i][0]=x;
        dfs(i,w+1);
    }
}
int LCA(int x,int y)
{
    if(d[x]<d[y]) swap(x,y);
    int t=0;
    while(t>=0)
    {
        if(d[fa[x][t]]>=d[y]) x=fa[x][t],++t;
        else --t;
    }
    if(x==y) return x;
    t=0;
    while(t>=0)
    {
        if(fa[x][t]!=fa[y][t]) x=fa[x][t],y=fa[y][t],++t;
        else --t;
    }
    return fa[x][0];
}
int find(int x,int k)
{
    int t=0;
    while(t>=0)
    {
        if(d[fa[x][t]]>=k) x=fa[x][t],++t;
        else --t;
    }
    return x;
}
int main()
{
    scanf("%d",&n);
    q=200;
    for(int i=1;i<=n;++i) scanf("%d",&c[i]);
    for(int i=1;i<=n-1;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        a[x].push_back(y);
        a[y].push_back(x);
    }
    for(int i=1;i<=n;++i) scanf("%d",&b[i]);
    dfs(1,0);
    for(int i=1;i<=30;++i)
    {
        for(int j=1;j<=n;++j)
        {
            fa[j][i]=fa[fa[j][i-1]][i-1];
        }
    }
    for(int i=1;i<=n-1;++i)
    {
        int x=b[i],y=b[i+1],w;
        scanf("%d",&w);
        int z=LCA(x,y);
        if(w<=q)
        {
            ll s=f[x][w]+f[y][w];
            if(d[x]-((d[x]-d[z])/w+1)*w>=1) s-=f[find(x,d[x]-((d[x]-d[z])/w+1)*w)][w];
            if(y==z) s-=f[y][w];
            else if(d[y]-((d[y]-d[z]-1)/w+1)*w>=1) s-=f[find(y,d[y]-((d[y]-d[z]-1)/w+1)*w)][w];
            printf("%lld\n",s);
        }
        else
        {
            ll s=c[x]+c[y];
            int p=x;
            while(d[p]-w>=d[z])
            {
                p=find(p,d[p]-w);
                s+=c[p];
            }
            if(y==z) s-=c[y];
            p=y;
            while(d[p]-w>d[z])
            {
                p=find(p,d[p]-w);
                s+=c[p];
            }
            printf("%lld\n",s);
        }
    }
    return 0;
}