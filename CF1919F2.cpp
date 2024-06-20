#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m;
ll a[N],b[N],c[N];
struct str
{
    ll s,w,t1,t2;
    str() {}
    str(ll a,ll b,ll c):s(min(a,b)),w(min(max(a-b,0ll),c)),t1(b-s),t2(c-w) {}
    friend str operator+(const str &a,const str &b)
    {
        str c;
        c.s=a.s+b.s+min(a.w,b.t1);
        c.w=b.w+min(a.w-min(a.w,b.t1),b.t2);
        c.t1=a.t1+min(a.t2,b.t1-min(a.w,b.t1));
        c.t2=min(a.t2-min(a.t2,b.t1-min(a.w,b.t1)),b.t2-min(a.w-min(a.w,b.t1),b.t2));
        // printf("(%lld %lld %lld %lld) (%lld %lld %lld %lld) -> (%lld %lld %lld %lld)\n",a.w,a.s,a.t1,a.t2,b.w,b.s,b.t1,b.t2,c.w,c.s,c.t1,c.t2);
        return c;
    }
};
struct tree
{
    int l,r;
    str s;
}T[N<<2];
void pushup(int x)
{
    T[x].s=T[x<<1].s+T[x<<1|1].s;
}
void build(int x,int l,int r)
{
    T[x].l=l,T[x].r=r;
    if(l==r)
    {
        T[x].s=str(a[l],b[l],c[l]);
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
        T[x].s=str(a[q],b[q],c[q]);
        return;
    }
    int z=T[x].l+T[x].r>>1;
    if(q<=z) add(x<<1,q);
    else add(x<<1|1,q);
    pushup(x);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&a[i]);
    }
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&b[i]);
    }
    for(int i=1;i<=n-1;++i)
    {
        scanf("%lld",&c[i]);
    }
    build(1,1,n);
    for(int i=1;i<=m;++i)
    {
        int x;
        scanf("%d",&x);
        scanf("%lld%lld%lld",&a[x],&b[x],&c[x]);
        add(1,x);
        printf("%lld\n",T[1].s.s);
    }
    return 0;
}