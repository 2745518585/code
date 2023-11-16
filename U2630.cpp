#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=200001,M=31;
const ll P=1e9+7;
int n,k,a[N];
ll C[M][M];
struct tree
{
    int l,r;
    ll k,s;
}T[M][N<<2];
void pushup(tree T[],int x)
{
    T[x].s=(T[x<<1].s+T[x<<1|1].s)%P;
}
void pushdown(tree T[],int x)
{
    if(T[x].k==1) return;
    T[x<<1].s=(T[x<<1].s*T[x].k)%P;
    T[x<<1].k=(T[x<<1].k*T[x].k)%P;
    T[x<<1|1].s=(T[x<<1|1].s*T[x].k)%P;
    T[x<<1|1].k=(T[x<<1|1].k*T[x].k)%P;
    T[x].k=1;
}
void build(tree T[],int x,int l,int r)
{
    T[x].l=l;
    T[x].r=r;
    T[x].k=1;
    T[x].s=0;
    if(l==r) return;
    int z=l+r>>1;
    build(T,x<<1,l,z);
    build(T,x<<1|1,z+1,r);
    pushup(T,x);
}
void add(tree T[],int x,int q,ll k)
{
    if(T[x].l==T[x].r)
    {
        T[x].s=k;
        return;
    }
    pushdown(T,x);
    int z=T[x].l+T[x].r>>1;
    if(q<=z) add(T,x<<1,q,k);
    else add(T,x<<1|1,q,k);
    pushup(T,x);
}
void add2(tree T[],int x,int l,int r,ll k)
{
    if(l>r) return;
    if(T[x].l>=l&&T[x].r<=r)
    {
        T[x].k=(T[x].k*k)%P;
        T[x].s=(T[x].s*k)%P;
        return;
    }
    pushdown(T,x);
    int z=T[x].l+T[x].r>>1;
    if(l<=z) add2(T,x<<1,l,r,k);
    if(r>z) add2(T,x<<1|1,l,r,k);
    pushup(T,x);
}
ll sum(tree T[],int x,int l,int r)
{
    if(l>r) return 0;
    if(T[x].l>=l&&T[x].r<=r)
    {
        return T[x].s;
    }
    pushdown(T,x);
    int z=T[x].l+T[x].r>>1;
    ll s=0;
    if(l<=z) s=(s+sum(T,x<<1,l,r))%P;
    if(r>z) s=(s+sum(T,x<<1|1,l,r))%P;
    return s;
}
ll qpow(ll x)
{
    ll s=1;
    for(int i=1;i<=k;++i) s=(s*x)%P;
    return s;
}
void exgcd(ll a,ll b,ll &x,ll &y)
{
    if(b==0) x=1,y=0;
    else exgcd(b,a%b,y,x),y-=a/b*x;
}
ll inv(ll a)
{
    ll x,y;
    exgcd(a,P,x,y);
    x=(x%P+P)%P;
    return x;
}
void init()
{
    for(int i=0;i<=k;++i)
    {
        C[i][0]=1;
        for(int j=1;j<=i;++j)
        {
            C[i][j]=C[i][j-1]*(i-j+1)%P*inv(j)%P;
        }
    }
}
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    init();
    for(int i=0;i<=k;++i) build(T[i],1,1,n);
    for(int i=1;i<=n;++i)
    {
        ll z[M];
        for(int j=0;j<=k;++j)
        {
            z[j]=sum(T[j],1,1,a[i]-1);
            ll w=1;
            for(int l=0;l<=j;++l)
            {
                w=(w+z[l]*C[j][l]%P)%P;
            }
            add(T[j],1,a[i],w);
        }
        for(int j=0;j<=k;++j)
        {
            add2(T[j],1,a[i]+1,n,2);
        }
    }
    printf("%lld",sum(T[k],1,1,n));
    return 0;
}