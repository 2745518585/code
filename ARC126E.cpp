#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll P=998244353;
int n,m,a[N],b[N],c[N],e[N];
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
    x=(x%P+P)%P;
    return x;
}
struct tree
{
    int l,r,t;
    ll s,w;
}T[N<<2];
void pushup(int x)
{
    T[x].s=(T[x<<1].s+T[x<<1|1].s+T[x<<1].t*T[x<<1|1].w%P)%P;
    T[x].w=(T[x<<1].w+T[x<<1|1].w)%P;
    T[x].t=(T[x<<1].t+T[x<<1|1].t)%P;
}
void build(int x,int l,int r)
{
    T[x].l=l,T[x].r=r;
    if(l==r)
    {
        T[x].t=T[x].w=T[x].s=0;
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
        T[x].t^=1;
        T[x].w=T[x].s=T[x].t*a[e[T[x].l]];
        return;
    }
    int z=T[x].l+T[x].r>>1;
    if(q<=z) add(x<<1,q);
    else add(x<<1|1,q);
    pushup(x);
}
bool cmp(int x,int y)
{
    return a[x]<a[y];
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=m;++i)
    {
        scanf("%d%d",&b[i],&a[n+i]);
    }
    for(int i=1;i<=n+m;++i) e[i]=i;
    sort(e+1,e+n+m+1,cmp);
    for(int i=1;i<=n+m;++i) c[e[i]]=i;
    build(1,1,n+m);
    ll q=0;
    for(int i=1;i<=n;++i)
    {
        add(1,c[i]);
        q=(q+a[i])%P;
    }
    // printf("%lld\n",T[1].s);
    for(int i=1;i<=m;++i)
    {
        add(1,c[b[i]]);
        add(1,c[n+i]);
        c[b[i]]=c[n+i];
        q=(q+a[n+i]-a[b[i]])%P;
        a[b[i]]=a[n+i];
        // printf("%lld %lld %lld\n",T[1].s,q,a[b[i]]);
        printf("%lld\n",((T[1].s-(n+1)*inv(2)%P*q%P)%P+P)%P);
    }
    return 0;
}