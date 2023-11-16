#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,q,a[N];
ll s,s1,s2;
struct tree
{
    int l,r;
    ll k,s,s1,s2;
}T[N<<2];
void pushup(int x)
{
    T[x].s=T[x<<1].s+T[x<<1|1].s;
    T[x].s1=min(T[x<<1].s1,T[x<<1|1].s1);
    T[x].s2=max(T[x<<1].s2,T[x<<1|1].s2);
}
void pushdown(int x)
{
    if(T[x].k==0) return;
    if(T[x].l==T[x].r)
    {
        if(T[x].s>T[x].k)
        {
            T[x].s-=T[x].k;
            T[x].s1-=T[x].k;
            T[x].s2-=T[x].k;
        }
        T[x].k=0;
        return;
    }
    T[x<<1].k+=T[x].k;
    T[x<<1|1].k+=T[x].k;
    pushdown(x<<1);
    pushdown(x<<1|1);
    T[x].k=0;
    pushup(x);
}
void build(int x,int l,int r)
{
    T[x].l=l;
    T[x].r=r;
    if(l==r)
    {
        if(a[l]==-1) T[x].s=0,T[x].s1=1e18,T[x].s2=-1e18;
        else T[x].s=T[x].s1=T[x].s2=a[l];
        return;
    }
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    pushup(x);
}
void add(int x,int t,int q,int k)
{
    if(T[x].l==T[x].r||q==0)
    {
        T[x].k+=k;
        return;
    }
    pushdown(x);
    if(t%2==0||q<=0) add(x<<1,t/2,q-1,k);
    if(t%2==1||q<=0) add(x<<1|1,t/2,q-1,k);
    pushup(x);
}
ll sum(int x,int t,int q)
{
    if(T[x].l==T[x].r||q==0)
    {
        return T[x].s;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    ll s=0;
    if(t%2==0) return sum(x<<1,t/2,q-1);
    else return sum(x<<1|1,t/2,q-1);
    return s;
}
ll sum1(int x,int t,int q)
{
    if(T[x].l==T[x].r||q==0)
    {
        return T[x].s1;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    ll s=0;
    if(t%2==0) return sum1(x<<1,t/2,q-1);
    else return sum1(x<<1|1,t/2,q-1);
    return s;
}
ll sum2(int x,int t,int q)
{
    if(T[x].l==T[x].r||q==0)
    {
        return T[x].s2;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    ll s=0;
    if(t%2==0) return sum2(x<<1,t/2,q-1);
    else return sum2(x<<1|1,t/2,q-1);
    return s;
}
int num(int x,int k)
{
    int s=0;
    for(int i=1;i<=k;++i) s=s*2+x%2,x/=2;
    for(int i=k+1;i<=q;++i) s*=2;
    return s+1;
}
int main()
{
    scanf("%d%d",&n,&m);
    while((1<<q)<n) ++q;
    ++q;
    for(int i=1;i<=(1<<q);++i) a[i]=-1;
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[num(i,q)]);
    }
    build(1,1,(1<<q));
    for(int i=1;i<=m;++i)
    {
        int z;
        scanf("%d",&z);
        if(z==1)
        {
            int x,y,k;
            scanf("%d%d%d",&x,&y,&k);
            add(1,y,x,k);
        }
        else if(z==2)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            ll z=sum(1,y,x),z1=sum1(1,y,x),z2=sum2(1,y,x);
            if(z1!=1e18) s^=z,s1^=z1,s2^=z2;
        }
    }
    printf("%lld\n%lld\n%lld",s1,s2,s);
    return 0;
}