#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1000001;
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
    ll s;
}T[N<<2];
bool cmp(str a,str b)
{
    if(a.h!=b.h) return a.h<b.h;
    return a.k<b.k;
}
void pushup(int x)
{
    if(T[x].t) T[x].s=b[T[x].r+1]-b[T[x].l]; 
    else T[x].s=T[x<<1].s+T[x<<1|1].s;
}
void build(int x,int l,int r)
{
    T[x].l=l;
    T[x].r=r;
    T[x].t=T[x].s=0;
    if(l==r) return;
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    pushup(x);
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
int main()
{
    scanf("%d%d",&n,&n);
    for(int i=1;i<=n;++i)
    {
        ll x1,y1,x2,y2;
        scanf("%lld%lld%lld%lld",&x1,&y1,&x2,&y2);
        if(x1>x2) swap(x1,y2);
        a[i*2-1]=(str){x1,x2,y1,1};
        a[i*2]=(str){x1,x2,y2,-1};
        b[i*2-1]=x1;
        b[i*2]=x2;
    }
    sort(a+1,a+n*2+1,cmp);
    sort(b+1,b+n*2+1);
    m=unique(b+1,b+n*2+1)-b-1;
    build(1,1,m-1);
    ll s=0;
    for(int i=1;i<=n*2;++i)
    {
        add(1,a[i].l,a[i].r,a[i].k);
        s+=T[1].s*(a[i+1].h-a[i].h);
    }
    printf("%lld",s);
    return 0;
}