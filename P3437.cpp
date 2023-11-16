#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=50001,M=101;
int n,m,q,a[N],sp,phi[N];
ll c,P,b1[M][N],b2[M][N];
vector<ll> d[N];
ll qpow(ll a,ll b,ll P)
{
    ll x=1,y=a;
    while(b)
    {
        if(b&1) x=x*y%P;
        y=y*y%P;
        b>>=1;
    }
    return x;
}
ll qpow2(int n,int q)
{
    return b1[q][n%10000]*b2[q][n/10000]%phi[q];
}
ll solve(int n,int q,int t)
{
    if(phi[q]==1) return 0;
    if(n==0) return a[t];
    if(n-1<d[t].size()&&d[t][n-1]<phi[q+1]) return qpow2(d[t][n-1],q);
    return qpow2(solve(n-1,q+1,t)+phi[q+1],q);
}
int get_phi(int x)
{
    int z=x,s=x;
    for(int i=2;i*i<=x;++i)
    {
        if(z%i==0)
        {
            s=s/i*(i-1);
            while(z%i==0) z/=i;
        }
    }
    if(z>1) s=s/z*(z-1);
    return s;
}
struct tree
{
    int l,r,t;
    ll s;
}T[N<<2];
void pushup(int x)
{
    T[x].s=(T[x<<1].s+T[x<<1|1].s)%P;
    T[x].t=min(T[x<<1].t,T[x<<1|1].t);
}
void build(int x,int l,int r)
{
    T[x].l=l;
    T[x].r=r;
    if(l==r)
    {
        T[x].s=a[l];
        T[x].t=0;
        return;
    }
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    pushup(x);
}
void add(int x,int l,int r)
{
    if(T[x].t>30) return;
    if(T[x].l==T[x].r)
    {
        ++T[x].t;
        T[x].s=solve(T[x].t,1,T[x].l);
        // printf("%d %lld\n",T[x].l,T[x].s);
        return;
    }
    int z=T[x].l+T[x].r>>1;
    if(l<=z) add(x<<1,l,r);
    if(r>z) add(x<<1|1,l,r);
    pushup(x);
}
ll sum(int x,int l,int r)
{
    if(T[x].l>=l&&T[x].r<=r)
    {
        return T[x].s;
    }
    int z=T[x].l+T[x].r>>1;
    ll s=0;
    if(l<=z) s=(s+sum(x<<1,l,r))%P;
    if(r>z) s=(s+sum(x<<1|1,l,r))%P;
    return s;
}
int main()
{
    scanf("%d%d%lld%lld",&n,&m,&P,&c);
    phi[++q]=P;
    while(phi[q]>1) ++q,phi[q]=get_phi(phi[q-1]);
    for(int i=1;i<=q;++i)
    {
        for(int j=0;j<=20000;++j)
        {
            b1[i][j]=qpow(c,j,phi[i]);
            b2[i][j]=qpow(c,j*10000,phi[i]);
        }
    }
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=n;++i)
    {
        ll w=a[i];
        d[i].push_back(w);
        for(int j=1;j<=30;++j)
        {
            ll z=1;
            for(int i=1;i<=w;++i)
            {
                z*=c;
                if(z>=P) break;
            }
            if(z>=P) break;
            w=z;
            d[i].push_back(w);
        }
    }
    build(1,1,n);
    for(int i=1;i<=m;++i)
    {
        int z,x,y;
        scanf("%d%d%d",&z,&x,&y);
        if(z==0) add(1,x,y);
        else if(z==1) printf("%lld\n",sum(1,x,y));
    }
    return 0;
}