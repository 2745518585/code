#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=100001,M=21,P=10007;
int n,m,k,a[N],b[N];
struct tree
{
    int l,r,f[M];
}T[N<<2];
void pushup(int x)
{
    for(int i=0;i<=m-1;++i) T[x].f[i]=0;
    for(int i=0;i<=m-1;++i)
    {
        for(int j=0;j<=m-1-i;++j)
        {
            T[x].f[i+j]=(T[x].f[i+j]+(ll)T[x<<1].f[i]%P*T[x<<1|1].f[j]%P)%P;
        }
    }
}
void build(int x,int l,int r)
{
    for(int i=0;i<=m-1;++i) T[x].f[i]=0;
    T[x].l=l;
    T[x].r=r;
    if(l==r)
    {
        T[x].f[0]=b[l];
        T[x].f[1]=a[l];
        return;
    }
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    pushup(x);
}
void add(int x,int q)
{
    if(T[x].l==T[x].r)
    {
        T[x].f[0]=b[q];
        T[x].f[1]=a[q];
        return;
    }
    int z=T[x].l+T[x].r>>1;
    if(q<=z) add(x<<1,q);
    else add(x<<1|1,q);
    pushup(x);
}
ll qpow(ll a,ll b)
{
    ll x=1;
    while(b)
    {
        if(b&1) x=x*a%P;
        a=a*a%P;
        b>>=1;
    }
    return x;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&b[i]);
    }
    build(1,1,n);
    ll s=1;
    for(int i=1;i<=n;++i)
    {
        s=s*(a[i]+b[i])%P;
    }
    scanf("%d",&k);
    for(int i=1;i<=k;++i)
    {
        int x;
        scanf("%d",&x);
        s=s*qpow(a[x]+b[x],P-2)%P;
        scanf("%d%d",&a[x],&b[x]);
        add(1,x);
        s=s*(a[x]+b[x])%P;
        ll w=0;
        for(int i=0;i<=m-1;++i)
        {
            w=(w+T[1].f[i])%P;
        }
        printf("%lld\n",((s-w)%P+P)%P);
    }
    return 0;
}