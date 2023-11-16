#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll P=1e9+7;
int n,a[N],b[N],c[N];
void exgcd(ll a,ll b,ll &x,ll &y)
{
    if(b==0) x=1,y=0;
    else exgcd(b,a%b,y,x),y-=a/b*x;
}
ll inv(ll a)
{
    a=(a%P+P)%P;
    ll x,y;
    exgcd(a,P,x,y);
    return (x%P+P)%P;
}
bool cmp(int x,int y)
{
    return a[x]<a[y];
}
namespace sgt
{
    int T[N];
    void add(int x,int k)
    {
        while(x<=n) T[x]+=k,x+=x&-x;
    }
    int sum(int x)
    {
        int s=0;
        while(x>=1) s+=T[x],x-=x&-x;
        return s;
    }
}
struct tree
{
    int l,r;
    ll s,k;
}T[N<<2];
void pushup(int x)
{
    T[x].s=(T[x<<1].s+T[x<<1|1].s)%P;
}
void pushdown(int x)
{
    if(T[x].k==1) return;
    T[x<<1].s=T[x<<1].s*T[x].k%P;
    T[x<<1].k=T[x<<1].k*T[x].k%P;
    T[x<<1|1].s=T[x<<1|1].s*T[x].k%P;
    T[x<<1|1].k=T[x<<1|1].k*T[x].k%P;
    T[x].k=1;
}
void build(int x,int l,int r)
{
    T[x].l=l,T[x].r=r;
    T[x].s=0,T[x].k=1;
    if(l==r) return;
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    pushup(x);
}
void add(int x,int q,ll k)
{
    if(T[x].l==T[x].r)
    {
        T[x].s=k;
        return;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    if(q<=z) add(x<<1,q,k);
    else add(x<<1|1,q,k);
    pushup(x);
}
ll sum(int x,int l,int r)
{
    if(l>r) return 0;
    if(T[x].l>=l&&T[x].r<=r) return T[x].s;
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    ll s=0;
    if(l<=z) s=(s+sum(x<<1,l,r))%P;
    if(r>z) s=(s+sum(x<<1|1,l,r))%P;
    return s;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=n;++i) b[i]=i;
    sort(b+1,b+n+1,cmp);
    for(int i=1;i<=n;++i) c[i]=a[b[i]];
    ll w=1;
    for(int i=1;i<=n;++i) w=w*(c[i]-i+1)%P;
    build(1,1,n);
    ll s=0;
    for(int i=1;i<=n;++i)
    {
        s=(s+w*inv((c[i]-i+1)*2)%P*sum(1,1,b[i]-1)%P)%P;
        s=(s+((sgt::sum(n)-sgt::sum(b[i]))*w%P-w*inv((c[i]-i+1)*2)%P*sum(1,b[i]+1,n)%P))%P;
        T[1].s=T[1].s*((c[i]-i)*inv(c[i]-i+1)%P)%P;
        T[1].k=T[1].k*((c[i]-i)*inv(c[i]-i+1)%P)%P;
        add(1,b[i],c[i]-i);
        sgt::add(b[i],1);
    }
    printf("%lld",(s%P+P)%P);
    return 0;
}