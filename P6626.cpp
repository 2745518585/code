#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=1000001;
int n,m,q,t[N],p=1;
struct road
{
    int m,q;
}a[N<<1];
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
int hs1,he1,hs2,he2,h1[N],h[N],e[N];
struct str
{
    int k,t;
    str(){}
    str(int k,int t):k(k),t(t){}
}h2[N];
vector<str> b[N];
int rt;
bool g[N];
struct tree
{
    int s,ms,d;
}T[N];
void dfs1(int x,int fa)
{
    T[x].s=1;
    T[x].ms=0;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa||g[a[i].m]) continue;
        dfs1(a[i].m,x);
        T[x].s+=T[a[i].m].s;
        T[x].ms=max(T[x].ms,T[a[i].m].s);
    }
    T[x].ms=max(T[x].ms,q-T[x].s);
    if(T[x].ms<T[rt].ms) rt=x;
}
void dfs2(int x,int fa)
{
    h1[++he1]=T[x].d;
    for(auto i:b[x])
    {
        if(i.k>=T[x].d) h2[++he2]=str(i.k-T[x].d,i.t);
    }
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa||g[a[i].m]) continue;
        T[a[i].m].d=T[x].d+1;
        dfs2(a[i].m,x);
    }
}
void solve(int x)
{
    hs1=he1=hs2=he2=0;
    h1[++he1]=0;
    for(auto i:b[x]) h2[++he2]=str(i.k,i.t);
    hs1=he1;
    hs2=he2;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(g[a[i].m]) continue;
        T[a[i].m].d=1;
        dfs2(a[i].m,x);
        for(int j=hs1+1;j<=he1;++j) ++h[h1[j]];
        for(int j=hs2+1;j<=he2;++j) e[h2[j].t]-=h[h2[j].k];
        for(int j=hs1+1;j<=he1;++j) --h[h1[j]];
        hs1=he1;
        hs2=he2;
    }
    for(int i=1;i<=he1;++i) ++h[h1[i]];
    for(int i=1;i<=he2;++i) e[h2[i].t]+=h[h2[i].k];
    for(int i=1;i<=he1;++i) --h[h1[i]];
}
void dfs(int x)
{
    rt=0;
    q=T[x].s;
    dfs1(x,0);
    solve(rt);
    g[rt]=true;
    for(int i=t[rt];i!=0;i=a[i].q)
    {
        if(g[a[i].m]) continue;
        dfs(a[i].m);
    }
}
int main()
{
    int Tot;
    scanf("%d",&Tot);
    while(Tot--)
    {
        scanf("%d%d",&n,&m);
        p=1;
        for(int i=1;i<=n;++i) t[i]=g[i]=0,b[i].clear();
        for(int i=1;i<=m;++i) e[i]=0;
        for(int i=1;i<=n-1;++i)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            road(x,y);
            road(y,x);
        }
        for(int i=1;i<=m;++i)
        {
            int x,k;
            scanf("%d%d",&x,&k);
            b[x].push_back(str(k,i));
        }
        T[1].s=n;
        T[0].ms=1e9;
        dfs(1);
        for(int i=1;i<=m;++i)
        {
            printf("%d\n",e[i]);
        }
    }
    return 0;
}