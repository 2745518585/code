#include<cstdio>
#include<algorithm>
using namespace std;
const int N=200001,M=31;
int n,m,q,s,t[N],p=1,r,tot,b[N],rt[N];
bool g[N];
struct tree
{
    int s,ms,k,f[M],d[M];
}T[N];
struct tree2
{
    int l,r,s;
}T2[N<<6];
struct road
{
    int m,q;
}a[N<<1];
void pushup(int x)
{
    T2[x].s=T2[T2[x].l].s+T2[T2[x].r].s;
}
void add(int &x,int ls,int rs,int q,int k)
{
    if(x==0) x=++tot;
    if(ls==rs)
    {
        T2[x].s+=k;
        return;
    }
    int z=ls+rs>>1;
    if(q<=z) add(T2[x].l,ls,z,q,k);
    else add(T2[x].r,z+1,rs,q,k);
    pushup(x);
}
int sum(int x,int ls,int rs)
{
    if(x==0||T2[x].s==0) return 1e9;
    if(ls==rs) return ls-1;
    int z=ls+rs>>1;
    if(T2[T2[x].l].s>=1) return sum(T2[x].l,ls,z);
    else return sum(T2[x].r,z+1,rs);
    return s;
}
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
void dfs1(int x,int fa)
{
    ++T[x].k;
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
    T[x].f[T[x].k]=r;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa||g[a[i].m]) continue;
        T[a[i].m].d[T[x].k]=T[x].d[T[x].k]+1;
        dfs2(a[i].m,x);
    }
}
void dfs(int x)
{
    r=0;
    q=T[x].s;
    dfs1(x,0);
    T[r].d[T[r].k]=0;
    dfs2(r,0);
    g[r]=true;
    for(int i=t[r];i!=0;i=a[i].q)
    {
        if(g[a[i].m]) continue;
        dfs(a[i].m);
    }
}
void check(int x)
{
    if(b[x]==0)
    {
        for(int i=1;i<=T[x].k;++i)
        {
            add(rt[T[x].f[i]],1,n,T[x].d[i]+1,1);
        }
        b[x]=1;
    }
    else if(b[x]==1)
    {
        for(int i=1;i<=T[x].k;++i)
        {
            add(rt[T[x].f[i]],1,n,T[x].d[i]+1,-1);
        }
        b[x]=0;
    }
}
int find(int x)
{
    int s=1e9;
    for(int i=1;i<=T[x].k;++i)
    {
        s=min(s,sum(rt[T[x].f[i]],1,n)+T[x].d[i]);
    }
    return s==1e9?-1:s;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n-1;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        road(x,y);
        road(y,x);
    }
    T[1].s=n;
    T[0].ms=1e9;
    dfs(1);
    scanf("%d",&m);
    for(int i=1;i<=m;++i)
    {
        int z,x;
        scanf("%d%d",&z,&x);
        if(z==0) check(x);
        else if(z==1) printf("%d\n",find(x));
    }
    return 0;
}