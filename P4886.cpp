#include<cstdio>
#include<algorithm>
using namespace std;
const int N=200001;
int n,m,q,s=1e9,t[N],p=1,r,q1,q2,b[N],c[N][2];
bool g[N];
struct tree
{
    int s,ms,d,h;
}T[N];
struct road
{
    int m,q,w;
}a[N<<1];
void road(int x,int y,int w)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].w=w;
}
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
    if(T[x].ms<T[r].ms) r=x;
}
void dfs2(int x,int fa)
{
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa) continue;
        T[a[i].m].d=T[x].d+a[i].w;
        T[a[i].m].h=T[x].h;
        dfs2(a[i].m,x);
    }
}
int solve(int x)
{
    if(g[x]==true)
    {
        printf("%d",s);
        exit(0);
    }
    g[x]=true;
    T[x].d=0;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        T[a[i].m].d=a[i].w;
        T[a[i].m].h=a[i].m;
        dfs2(a[i].m,x);
    }
    int w=0;
    for(int i=1;i<=m;++i)
    {
        w=max(w,T[c[i][0]].d+T[c[i][1]].d);
    }
    int u=0;
    for(int i=1;i<=m;++i)
    {
        if(T[c[i][0]].d+T[c[i][1]].d==w)
        {
            if(c[i][0]==x);
            else if(u==0) u=T[c[i][0]].h;
            else if(u!=T[c[i][0]].h) u=-1;
            if(c[i][1]==x);
            if(u==0) u=T[c[i][1]].h;
            else if(u!=T[c[i][1]].h) u=-1;
        }
    }
    s=min(s,w);
    if(u==-1)
    {
        printf("%d",s);
        exit(0);
    }
    return u;
}
void dfs(int x)
{
    r=0;
    q=T[x].s;
    dfs1(x,0);
    int u=solve(r);
    dfs(u);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n-1;++i)
    {
        int x,y,w;
        scanf("%d%d%d",&x,&y,&w);
        road(x,y,w);
        road(y,x,w);
    }
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        ++b[x],++b[y];
        c[i][0]=x,c[i][1]=y;
    }
    T[1].s=n;
    T[0].ms=1e9;
    dfs(1);
    return 0;
}