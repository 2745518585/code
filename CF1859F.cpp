#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=200001,M=21;
int n,m,k,b[N],pow2[N],d[N],fa[N][M];
ll t,f[N],f1[N][M],f2[N][M],g[N],h[N];
vector<pair<int,int>> a[N];
struct str
{
    int x,y;
    ll w;
}c[N];
void dfs0(int x)
{
    d[x]=d[fa[x][0]]+1;
    for(auto i:a[x])
    {
        if(i.first==fa[x][0]) continue;
        fa[i.first][0]=x;
        h[i.first]=h[x]+i.second;
        dfs0(i.first);
    }
}
void dfs1(int x)
{
    for(auto i:a[x])
    {
        if(i.first==fa[x][0]) continue;
        g[i.first]=g[x]+(i.second-1)/pow2[k]+1;
        dfs1(i.first);
        f[x]=min(f[x],f[i.first]+i.second+(i.second-1)/pow2[k]+1);
    }
}
void dfs2(int x)
{
    for(auto i:a[x])
    {
        if(i.first==fa[x][0]) continue;
        f[i.first]=min(f[i.first],f[x]+i.second+(i.second-1)/pow2[k]+1);
        dfs2(i.first);
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
ll sum1(int x,int y)
{
    int t=0;
    ll s=1e18,w=0;
    while(t>=0)
    {
        if(d[fa[x][t]]>=d[y])
        {
            s=min(s,f1[x][t]+w+(g[fa[x][t]]-g[y]));
            w+=h[x]-h[fa[x][t]];
            x=fa[x][t];
            ++t;
        }
        else --t;
    }
    return s;
}
ll sum2(int x,int y)
{
    int t=0;
    ll s=1e18,w=0;
    while(t>=0)
    {
        if(d[fa[x][t]]>=d[y])
        {
            s=min(s,f2[x][t]+w+(h[fa[x][t]]-h[y]));
            w+=g[x]-g[fa[x][t]];
            x=fa[x][t];
            ++t;
        }
        else --t;
    }
    return s;
}
int main()
{
    pow2[0]=1;
    for(int i=1;i<=20;++i) pow2[i]=pow2[i-1]*2;
    int TOT;
    scanf("%d",&TOT);
    while(TOT--)
    {
        scanf("%d%lld",&n,&t);
        for(int i=1;i<=n;++i) a[i].clear();
        for(int i=1;i<=n-1;++i)
        {
            int x,y,w;
            scanf("%d%d%d",&x,&y,&w);
            a[x].push_back(make_pair(y,w));
            a[y].push_back(make_pair(x,w));
        }
        static char z[N];
        scanf("%s",z+1);
        for(int i=1;i<=n;++i) b[i]=z[i]-'0';
        fa[1][0]=0;
        h[1]=0;
        dfs0(1);
        for(int i=1;i<=20;++i)
        {
            for(int j=1;j<=n;++j)
            {
                fa[j][i]=fa[fa[j][i-1]][i-1];
            }
        }
        scanf("%d",&m);
        for(int i=1;i<=m;++i)
        {
            scanf("%d%d",&c[i].x,&c[i].y);
            c[i].w=h[c[i].x]+h[c[i].y]-h[LCA(c[i].x,c[i].y)]*2;
        }
        for(k=1;k<=20;++k)
        {
            for(int i=1;i<=n;++i)
            {
                if(b[i]==1) f[i]=t*k;
                else f[i]=1e18;
            }
            g[1]=0;
            dfs1(1);
            dfs2(1);
            for(int i=1;i<=n;++i)
            {
                f1[i][0]=f[fa[i][0]]+h[i]-h[fa[i][0]];
                f2[i][0]=f[fa[i][0]]+g[i]-g[fa[i][0]];
            }
            for(int i=1;i<=20;++i)
            {
                for(int j=1;j<=n;++j)
                {
                    f1[j][i]=min(f1[j][i-1]+(g[fa[j][i-1]]-g[fa[j][i]]),f1[fa[j][i-1]][i-1]+(h[j]-h[fa[j][i-1]]));
                    f2[j][i]=min(f2[j][i-1]+(h[fa[j][i-1]]-h[fa[j][i]]),f2[fa[j][i-1]][i-1]+(g[j]-g[fa[j][i-1]]));
                }
            }
            for(int i=1;i<=m;++i)
            {
                int x=c[i].x,y=c[i].y,z=LCA(x,y);
                c[i].w=min(c[i].w,f[x]+g[x]+g[y]-g[z]*2);
                c[i].w=min(c[i].w,sum1(x,z)+(g[y]-g[z]));
                c[i].w=min(c[i].w,sum2(y,z)+(h[x]-h[z]));
            }
        }
        for(int i=1;i<=m;++i)
        {
            printf("%lld\n",c[i].w);
        }
    }
    return 0;
}