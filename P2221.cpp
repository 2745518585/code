#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
ll b1[N],b2[N];
struct tree
{
    int l,r;
    ll s,s1,s2,k;
}T[N<<2];
ll gcd(ll a,ll b)
{
    if(b==0) return a;
    return gcd(b,a%b);
}
void pushup(int x)
{
    T[x].s=T[x<<1].s+T[x<<1|1].s;
    T[x].s1=T[x<<1].s1+T[x<<1|1].s1;
    T[x].s2=T[x<<1].s2+T[x<<1|1].s2;
}
void pushdown(int x)
{
    if(T[x].k==0) return;
    T[x<<1].k+=T[x].k;
    T[x<<1].s+=(T[x<<1].r-T[x<<1].l+1)*T[x].k;
    T[x<<1].s1+=(b1[T[x<<1].r]-b1[T[x<<1].l-1])*T[x].k;
    T[x<<1].s2+=(b2[T[x<<1].r]-b2[T[x<<1].l-1])*T[x].k;
    T[x<<1|1].k+=T[x].k;
    T[x<<1|1].s+=(T[x<<1|1].r-T[x<<1|1].l+1)*T[x].k;
    T[x<<1|1].s1+=(b1[T[x<<1|1].r]-b1[T[x<<1|1].l-1])*T[x].k;
    T[x<<1|1].s2+=(b2[T[x<<1|1].r]-b2[T[x<<1|1].l-1])*T[x].k;
    T[x].k=0;
}
void build(int x,int l,int r)
{
    T[x].l=l;
    T[x].r=r;
    if(l==r) return;
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    pushup(x);
}
void add(int x,int l,int r,ll k)
{
    if(T[x].l>=l&&T[x].r<=r)
    {
        T[x].k+=k;
        T[x].s+=(T[x].r-T[x].l+1)*k;
        T[x].s1+=(b1[T[x].r]-b1[T[x].l-1])*k;
        T[x].s2+=(b2[T[x].r]-b2[T[x].l-1])*k;
        return;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    if(l<=z) add(x<<1,l,r,k);
    if(r>z) add(x<<1|1,l,r,k);
    pushup(x);
}
ll sum(int x,int l,int r)
{
    if(T[x].l>=l&&T[x].r<=r)
    {
        return T[x].s;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    ll s=0;
    if(l<=z) s+=sum(x<<1,l,r);
    if(r>z) s+=sum(x<<1|1,l,r);
    return s;
}
ll sum1(int x,int l,int r)
{
    if(T[x].l>=l&&T[x].r<=r)
    {
        return T[x].s1;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    ll s=0;
    if(l<=z) s+=sum1(x<<1,l,r);
    if(r>z) s+=sum1(x<<1|1,l,r);
    return s;
}
ll sum2(int x,int l,int r)
{
    if(T[x].l>=l&&T[x].r<=r)
    {
        return T[x].s2;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    ll s=0;
    if(l<=z) s+=sum2(x<<1,l,r);
    if(r>z) s+=sum2(x<<1|1,l,r);
    return s;
}
int n,m;
int main()
{
    scanf("%d%d",&n,&m);
    for(ll i=1;i<=n;++i)
    {
        b1[i]=b1[i-1]+i;
        b2[i]=b2[i-1]+i*i;
    }
    build(1,1,n-1);
    for(int i=1;i<=m;++i)
    {
        char z[10];
        ll x,y;
        scanf("%s%lld%lld",z,&x,&y);
        --y;
        if(z[0]=='C')
        {
            ll k;
            scanf("%lld",&k);
            add(1,x,y,k);
        }
        else
        {
            ll k1=-sum2(1,x,y)+(x+y)*sum1(1,x,y)+(y-x+1-x*y)*sum(1,x,y),k2=(y-x+2)*(y-x+1)/2;
            ll z=gcd(k1,k2);
            printf("%lld/%lld\n",k1/z,k2/z);
        }
    }
    return 0;
}