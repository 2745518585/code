#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
const int N=1000001;
int n,m,q,rt,s=1e9,p=1,t[N],b[N],h2[N];
bool f[N],g[N],h[N];
vector<int> c[N];
struct road
{
    int m,q;
}a[N<<1];
struct tree
{
    int s,ms,f;
}T[N];
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
void dfs1(int x,int fa)
{
    h[b[x]]=false;
    h2[b[x]]=0;
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
void dfs2(int x)
{
    T[x].s=1;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==T[x].f||g[a[i].m]) continue;
        T[a[i].m].f=x;
        dfs2(a[i].m);
        T[x].s+=T[a[i].m].s;
    }
}
void solve(int x)
{
    T[x].f=0;
    dfs2(x);
    if(f[b[x]]) return;
    queue<int> Q;
    h[b[x]]=true;
    int w=0;
    for(auto i:c[b[x]]) Q.push(i);
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        if(T[k].f==0) continue;
        if(f[b[T[k].f]]) return;
        if(h[b[T[k].f]]) continue;
        h[b[T[k].f]]=true;
        ++w;
        for(auto i:c[b[T[k].f]]) Q.push(i);
    }
    s=min(s,w);
}
void dfs3(int x,int k)
{
    if(h2[b[x]]==0) h2[b[x]]=k;
    if(h2[b[x]]!=k) f[b[x]]=true;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==T[x].f||g[a[i].m]) continue;
        dfs3(a[i].m,k);
    }
}
void check(int x)
{
    f[b[x]]=true;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(g[a[i].m]) continue;
        dfs3(a[i].m,a[i].m);
    }
}
void dfs(int x)
{
    rt=0;
    q=T[x].s;
    dfs1(x,0);
    solve(rt);
    check(rt);
    g[rt]=true;
    for(int i=t[rt];i!=0;i=a[i].q)
    {
        if(g[a[i].m]) continue;
        dfs(a[i].m);
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n-1;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        road(x,y);
        road(y,x);
    }
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&b[i]);
        c[b[i]].push_back(i);
    }
    T[0].ms=1e9;
    T[1].s=n;
    dfs(1);
    printf("%d",s);
    return 0;
}