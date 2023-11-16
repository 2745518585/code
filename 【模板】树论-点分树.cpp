#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=200001,M=31;
int n,m,q,s,t[N],p=1,r,tot,rt1[N],rt2[N];
bool g[N];
ll b[N];
struct tree
{
    int s,ms,k,f[M],d[M];
}T[N];
struct tree2
{
    int l,r;
    ll s;
}T2[N<<6];
struct road
{
    int m,q;
}a[N<<1];
void pushup(int x)
{
    T2[x].s=T2[T2[x].l].s+T2[T2[x].r].s;
}
void add(int &x,int ls,int rs,int q,ll k)
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
ll sum(int x,int ls,int rs,int l,int r)
{
    if(x==0) return 0;
    if(ls>=l&&rs<=r)
    {
        return T2[x].s;
    }
    int z=ls+rs>>1;
    ll s=0;
    if(l<=z) s+=sum(T2[x].l,ls,z,l,r);
    if(r>z) s+=sum(T2[x].r,z+1,rs,l,r);
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
    add(rt1[r],1,n,T[x].d[T[x].k]+1,b[x]);
    if(T[x].k>1) add(rt2[r],1,n,T[x].d[T[x].k-1]+1,b[x]);
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
void check(int x,ll k)
{
    for(int i=1;i<=T[x].k;++i)
    {
        add(rt1[T[x].f[i]],1,n,T[x].d[i]+1,k-b[x]);
        if(i>1) add(rt2[T[x].f[i]],1,n,T[x].d[i-1]+1,k-b[x]);
    }
    b[x]=k;
}
ll find(int x,ll k)
{
    ll s=0;
    for(int i=1;i<=T[x].k;++i)
    {
        s+=sum(rt1[T[x].f[i]],1,n,1,k-T[x].d[i]+1);
        if(i<T[x].k) s-=sum(rt2[T[x].f[i+1]],1,n,1,k-T[x].d[i]+1);
    }
    return s;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&b[i]);
    }
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
    int las=0;
    for(int i=1;i<=m;++i)
    {
        int z,x;
        ll k;
        scanf("%d%d%lld",&z,&x,&k);
        x^=las,k^=las;
        if(z==0) printf("%lld\n",las=find(x,k));
        else if(z==1) check(x,k);
    }
    return 0;
}