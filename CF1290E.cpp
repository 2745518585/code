#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=500001;
int n,a[N];
ll b[N];
struct tree
{
    int l,r,s2,ms,ms2,mt,k1,k2;
    ll s;
}T[N<<2];
void pushup(int x)
{
    T[x].s=T[x<<1].s+T[x<<1|1].s;
    T[x].s2=T[x<<1].s2+T[x<<1|1].s2;
    T[x].ms=max(T[x<<1].ms,T[x<<1|1].ms);
    T[x].ms2=max(T[x].ms!=T[x<<1].ms?T[x<<1].ms:T[x<<1].ms2,T[x].ms!=T[x<<1|1].ms?T[x<<1|1].ms:T[x<<1|1].ms2);
    T[x].mt=(T[x].ms==T[x<<1].ms?T[x<<1].mt:0)+(T[x].ms==T[x<<1|1].ms?T[x<<1|1].mt:0);
}
void pushdown1(int x,int k)
{
    if(T[x].s2==0) return;
    T[x].s+=(ll)k*T[x].s2;
    T[x].ms+=k;
    T[x].ms2+=k;
    T[x].k1+=k;
    T[x].k2+=k;
}
void pushdown2(int x,int k)
{
    if(T[x].s2==0) return;
    if(k<T[x].ms&&k>=T[x].ms2)
    {
        T[x].s+=(ll)T[x].mt*(k-T[x].ms);
        T[x].ms=k;
        T[x].k2=min(T[x].k2,k);
    }
}
void pushdown(int x)
{
    if(T[x].k1!=0)
    {
        pushdown1(x<<1,T[x].k1);
        pushdown1(x<<1|1,T[x].k1);
        T[x].k1=0;
    }
    if(T[x].k2!=1e9)
    {
        pushdown2(x<<1,T[x].k2);
        pushdown2(x<<1|1,T[x].k2);
        T[x].k2=1e9;
    }
}
void build(int x,int l,int r)
{
    T[x].l=l;
    T[x].r=r;
    T[x].k1=0;
    T[x].k2=1e9;
    T[x].ms=T[x].ms2=T[x].mt=T[x].s=T[x].s2=0;
    if(l==r) return;
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    pushup(x);
}
void add1(int x,int q,int k)
{
    if(T[x].l==T[x].r)
    {
        T[x].s=T[x].ms=k;
        T[x].s2=1;
        T[x].mt=1;
        return;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    if(q<=z) add1(x<<1,q,k);
    else add1(x<<1|1,q,k);
    pushup(x);
}
void add2(int x,int l,int r,int k)
{
    if(l>r) return;
    if(T[x].l>=l&&T[x].r<=r)
    {
        pushdown1(x,k);
        return;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    if(l<=z) add2(x<<1,l,r,k);
    if(r>z) add2(x<<1|1,l,r,k);
    pushup(x);
}
void add3(int x,int l,int r,int k)
{
    if(l>r) return;
    if(T[x].l>=l&&T[x].r<=r&&k>=T[x].ms2)
    {
        pushdown2(x,k);
        return;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    if(l<=z) add3(x<<1,l,r,k);
    if(r>z) add3(x<<1|1,l,r,k);
    pushup(x);
}
int sum(int x,int l,int r)
{
    if(l>r) return 0;
    if(T[x].l>=l&&T[x].r<=r)
    {
        return T[x].s2;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1,s=0;
    if(l<=z) s+=sum(x<<1,l,r);
    if(r>z) s+=sum(x<<1|1,l,r);
    return s;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        a[x]=i;
    }
    build(1,1,n);
    for(int i=1;i<=n;++i)
    {
        add1(1,a[i],i+1);
        add2(1,a[i]+1,n,1);
        add3(1,1,a[i]-1,sum(1,1,a[i]));
        b[i]=T[1].s-i;
    }
    build(1,1,n);
    for(int i=1;i<=n;++i)
    {
        a[i]=n-a[i]+1;
        add1(1,a[i],i+1);
        add2(1,a[i]+1,n,1);
        add3(1,1,a[i]-1,sum(1,1,a[i]));
        b[i]-=(ll)i*(i+1)-T[1].s;
        printf("%lld\n",b[i]);
    }
    return 0;
}