#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2000001;
int n,m,r,p=1,tot,t[N],b[N],c[N];
struct road
{
    int m,q;
}a[N<<1];
struct tree
{
    int b,bm;
}T[N];
struct tree2
{
    int l,r;
    ll s,k;
}T2[N<<2];
void pushup(int x)
{
    T2[x].s=T2[x<<1].s+T2[x<<1|1].s;
}
void pushdown(int x)
{
    if(T2[x].k==0) return;
    T2[x<<1].k+=T2[x].k;
    T2[x<<1].s+=T2[x].k*(T2[x<<1].r-T2[x<<1].l+1);
    T2[x<<1|1].k+=T2[x].k;
    T2[x<<1|1].s+=T2[x].k*(T2[x<<1|1].r-T2[x<<1|1].l+1);
    T2[x].k=0;
}
void build(int x,int l,int r)
{
    T2[x].l=l;
    T2[x].r=r;
    if(l==r)
    {
        T2[x].s=b[c[l]];
        return;
    }
    int z=T2[x].l+T2[x].r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    pushup(x);
}
void add(int x,int l,int r,ll k)
{
    if(T2[x].l>=l&&T2[x].r<=r)
    {
        T2[x].k+=k;
        T2[x].s+=k*(T2[x].r-T2[x].l+1);
        return;
    }
    pushdown(x);
    int z=T2[x].l+T2[x].r>>1;
    if(l<=z) add(x<<1,l,r,k);
    if(r>z) add(x<<1|1,l,r,k);
    pushup(x);
}
ll sum(int x,int l,int r)
{
    if(T2[x].l>=l&&T2[x].r<=r)
    {
        return T2[x].s;
    }
    pushdown(x);
    int z=T2[x].l+T2[x].r>>1;
    ll s=0;
    if(l<=z) s+=sum(x<<1,l,r);
    if(r>z) s+=sum(x<<1|1,l,r);
    return s;
}
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
void dfs(int x,int fa)
{
    T[x].b=++tot;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa) continue;
        dfs(a[i].m,x);
    }
    T[x].bm=tot;
}
int main()
{
    scanf("%d%d%d",&n,&m,&r);
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
    dfs(r,0);
    for(int i=1;i<=n;++i) c[T[i].b]=i;
    build(1,1,n);
    for(int i=1;i<=m;++i)
    {
        int z;
        scanf("%d",&z);
        if(z==1)
        {
            int x;
            ll k;
            scanf("%d%lld",&x,&k);
            add(1,T[x].b,T[x].bm,k);
        }
        else if(z==2)
        {
            int x;
            scanf("%d",&x);
            printf("%lld\n",sum(1,T[x].b,T[x].bm));
        }
    }
    return 0;
}