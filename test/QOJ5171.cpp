#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll P=1e9+7;
int n,m,k,op,d[N],h[N];
ll b[N];
struct str
{
    int l,r,w;
}a[N];
bool cmp(str a,str b)
{
    if(a.l!=b.l) return a.l<b.l;
    return a.r<b.r;
}
struct pr
{
    int s;
    ll w;
    pr() {}
    pr(int s,ll w):s(s),w(w) {}
    friend pr operator+(const pr &a,const pr &b)
    {
        if(a.s!=b.s) return a.s>b.s?a:b;
        else return pr(a.s,(a.w+b.w)%P);
    }
}f[N];
namespace sgt1
{
    struct tree
    {
        int l,r;
        ll s1,s2;
    }T[N<<2];
    void pushup(int x)
    {
        T[x].s1=max(T[x<<1].s1,T[x<<1|1].s1);
        T[x].s2=min(T[x<<1].s2,T[x<<1|1].s2);
    }
    void build(int x,int l,int r)
    {
        T[x].l=l,T[x].r=r;
        T[x].s1=-1e18,T[x].s2=1e18;
        if(l==r) return;
        int z=l+r>>1;
        build(x<<1,l,z);
        build(x<<1|1,z+1,r);
        pushup(x);
    }
    void add(int x,int q,ll k1,ll k2)
    {
        if(T[x].l==T[x].r)
        {
            T[x].s1=max(T[x].s1,k1);
            T[x].s2=min(T[x].s2,k2);
            return;
        }
        int z=T[x].l+T[x].r>>1;
        if(q<=z) add(x<<1,q,k1,k2);
        else add(x<<1|1,q,k1,k2);
        pushup(x);
    }
    int sum1(int x,ll k)
    {
        if(T[x].l==T[x].r) return T[x].l;
        int z=T[x].l+T[x].r>>1;
        if(T[x<<1|1].s1>k) return sum1(x<<1|1,k);
        else return sum1(x<<1,k);
    }
    int sum2(int x,ll k)
    {
        if(T[x].l==T[x].r) return T[x].l;
        int z=T[x].l+T[x].r>>1;
        if(T[x<<1|1].s2<k) return sum2(x<<1|1,k);
        else return sum2(x<<1,k);
    }
}
namespace sgt2
{
    struct tree
    {
        int l,r;
        pr s;
    }T[N<<2];
    void pushup(int x)
    {
        T[x].s=T[x<<1].s+T[x<<1|1].s;
    }
    void build(int x,int l,int r)
    {
        T[x].l=l,T[x].r=r;
        T[x].s=pr(-1e9,0);
        if(l==r) return;
        int z=l+r>>1;
        build(x<<1,l,z);
        build(x<<1|1,z+1,r);
        pushup(x);
    }
    void add(int x,int q,pr k)
    {
        if(T[x].l==T[x].r)
        {
            T[x].s=k;
            return;
        }
        int z=T[x].l+T[x].r>>1;
        if(q<=z) add(x<<1,q,k);
        else add(x<<1|1,q,k);
        pushup(x);
    }
    pr sum(int x,int l,int r)
    {
        if(T[x].l>=l&&T[x].r<=r) return T[x].s;
        int z=T[x].l+T[x].r>>1;
        if(r<=z) return sum(x<<1,l,r);
        else if(l>z) return sum(x<<1|1,l,r);
        else return sum(x<<1,l,r)+sum(x<<1|1,l,r);
    }
}
int main()
{
    scanf("%d%d%d%d",&n,&m,&k,&op);
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d%d",&a[i].w,&a[i].l,&a[i].r);
        ++h[a[i].l],--h[a[i].r+1];
    }
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=m;++i) h[i]+=h[i-1];
    for(int i=1;i<=m;++i) h[i]=h[i-1]+(h[i]==0);
    for(int i=1;i<=n;++i)
    {
        a[i].l-=h[a[i].l];
        a[i].r-=h[a[i].r];
    }
    m-=h[m];
    a[n+1].l=m+1;
    for(int i=1;i<=n+1;++i) b[i]=b[i-1]+(k-a[i].w);
    sgt1::build(1,0,n);
    sgt1::add(1,0,0,0);
    int x=0;
    for(int i=1;i<=n+1;++i)
    {
        int p1=sgt1::sum1(1,a[i].l-b[i-1]-1),p2=sgt1::sum2(1,a[i].l-b[i-1]-1);
        if(p1>p2&&p1>x) d[i]=d[p1];
        else d[i]=max(x,max(p1,p2));
        if(a[i].w>k) x=i;
        sgt1::add(1,i,a[i].l-b[i-1],a[i-1].r-b[i-1]);
    }
    sgt2::build(1,0,n);
    sgt2::add(1,0,pr(0,1));
    for(int i=1;i<=n+1;++i)
    {
        f[i]=sgt2::sum(1,d[i],i-1);
        f[i].s+=i-1;
        sgt2::add(1,i,pr(f[i].s-i,f[i].w));
    }
    if(op==0) printf("%d",f[n+1].s);
    else printf("%d %lld",f[n+1].s,f[n+1].w);
    return 0;
}