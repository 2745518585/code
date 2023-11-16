#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll P=998244353;
int n,m,p=1,tot,t[N],b[N],d[N],rt[N];
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
struct tree
{
    int l,r;
    ll s,k;
}T[N<<4];
void pushup(int x)
{
    T[x].s=(T[T[x].l].s+T[T[x].r].s)%P;
}
void pushdown(int x)
{
    if(T[x].k==1) return;
    if(T[x].l)
    {
        T[T[x].l].s=(T[T[x].l].s*T[x].k)%P;
        T[T[x].l].k=(T[T[x].l].k*T[x].k)%P;
    }
    if(T[x].r)
    {
        T[T[x].r].s=(T[T[x].r].s*T[x].k)%P;
        T[T[x].r].k=(T[T[x].r].k*T[x].k)%P;
    }
    T[x].k=1;
}
void add(int &x,int ls,int rs,int q,ll k)
{
    if(x==0)
    {
        x=++tot;
        T[x].s=0;
        T[x].k=1;
    }
    if(ls==rs)
    {
        T[x].s=k;
        return;
    }
    pushdown(x);
    int z=ls+rs>>1;
    if(q<=z) add(T[x].l,ls,z,q,k);
    else add(T[x].r,z+1,rs,q,k);
    pushup(x);
}
ll sum(int x,int ls,int rs,int l,int r)
{
    if(x==0) return 0;
    if(ls>=l&&rs<=r)
    {
        return T[x].s;
    }
    pushdown(x);
    int z=ls+rs>>1;
    ll s=0;
    if(l<=z) s=(s+sum(T[x].l,ls,z,l,r))%P;
    if(r>z) s=(s+sum(T[x].r,z+1,rs,l,r))%P;
    return s;
}
int merg(int x1,int x2,int ls,int rs,ll t1,ll t2)
{
    if(x1==0)
    {
        T[x2].s=(T[x2].s*t1)%P;
        T[x2].k=(T[x2].k*t1)%P;
        return x2;
    }
    if(x2==0)
    {
        T[x1].s=(T[x1].s*t2)%P;
        T[x1].k=(T[x1].k*t2)%P;
        return x1;
    }
    if(ls==rs)
    {
        T[x1].s=(T[x1].s*(t2+T[x2].s)%P+T[x2].s*t1%P)%P;
        return x1;
    }
    pushdown(x1);
    pushdown(x2);
    int z=ls+rs>>1;
    T[x1].r=merg(T[x1].r,T[x2].r,z+1,rs,t1+T[T[x1].l].s,t2+T[T[x2].l].s);
    T[x1].l=merg(T[x1].l,T[x2].l,ls,z,t1,t2);
    pushup(x1);
    return x1;
}
void dfs0(int x,int fa)
{
    d[x]=d[fa]+1;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa) continue;
        dfs0(a[i].m,x);
    }
}
void dfs(int x,int fa)
{
    add(rt[x],0,n,b[x],1);
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa) continue;
        dfs(a[i].m,x);
        rt[x]=merg(rt[x],rt[a[i].m],0,n,0,sum(rt[a[i].m],0,n,0,d[x]));
    }
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
    dfs0(1,0);
    scanf("%d",&m);
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        b[y]=max(b[y],d[x]);
    }
    dfs(1,0);
    printf("%lld",sum(rt[1],0,n,0,0));
    return 0;
}