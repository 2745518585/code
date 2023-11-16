#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=10000001;
int n,m;
ll b[N];
struct str
{
    ll l,r,h;
    int k;
}a[N];
struct tree
{
    int l,r,t;
    ll s,m,lm,rm;
}T[N];
bool cmp(str a,str b)
{
    if(a.h!=b.h) return a.h<b.h;
    return a.k>b.k;
}
void pushup(int x)
{
    if(T[x].t)
    {
        T[x].s=b[T[x].r+1]-b[T[x].l];
        T[x].m=T[x].lm=T[x].rm=1;
    }
    else
    {
        T[x].s=T[x<<1].s+T[x<<1|1].s;
        T[x].lm=T[x<<1].lm;
        T[x].rm=T[x<<1|1].rm;
        T[x].m=T[x<<1].m+T[x<<1|1].m-(T[x<<1].rm==1&&T[x<<1|1].lm==1);
    }
}
void build(int x,int l,int r)
{
    T[x].l=l;
    T[x].r=r;
    T[x].t=T[x].s=T[x].m=0;
    if(l==r) return;
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
}
void add(int x,ll l,ll r,int k)
{
    if(b[T[x].l]>=r||b[T[x].r+1]<=l) return;
    if(b[T[x].l]>=l&&b[T[x].r+1]<=r)
    {
        T[x].t+=k;
        pushup(x);
        return;
    }
    add(x<<1,l,r,k);
    add(x<<1|1,l,r,k);
    pushup(x);
}
ll sum(int x,ll l,ll r)
{
    if(b[T[x].l]>=r||b[T[x].r+1]<=l) return 0;
    if(b[T[x].l]>=l&&b[T[x].r+1]<=r)
    {
        return T[x].s;
    }
    if(T[x].t) return min(b[T[x].r+1],r)-max(b[T[x].l],l);
    return sum(x<<1,l,r)+sum(x<<1|1,l,r);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        ll x1,y1,x2,y2;
        scanf("%lld%lld%lld%lld",&x1,&y1,&x2,&y2);
        a[i*2-1]=(str){x1,x2,y1,1};
        a[i*2]=(str){x1,x2,y2,-1};
        b[i*2-1]=x1;
        b[i*2]=x2;
    }
    n<<=1;
    sort(a+1,a+n+1,cmp);
    sort(b+1,b+n+1);
    m=unique(b+1,b+n+1)-(b+1);
    build(1,1,m-1);
    ll s=0;
    a[n+1].h=a[n].h;
    for(int i=1;i<=n;++i)
    {
        ll z;
        if(a[i].k==1) z=sum(1,a[i].l,a[i].r);
        add(1,a[i].l,a[i].r,a[i].k);
        if(a[i].k==-1) z=sum(1,a[i].l,a[i].r);
        s+=T[1].m*(a[i+1].h-a[i].h)*2+(a[i].r-a[i].l)-z;
    }
    printf("%lld",s);
    return 0;
}