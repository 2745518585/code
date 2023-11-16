#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=10000001;
int n,m;
ll b[N],t1,t2;
struct tree
{
    int l,r,k;
    ll s;
}T[N<<2];
struct str
{
    ll x,y;
    int k;
}a[N];
void pushup(int x)
{
    T[x].s=T[x<<1].s+T[x<<1|1].s;
}
void pushdown(int x)
{
    if(T[x].k==0) return;
    if(T[x].k==1)
    {
        T[x<<1].s=b[T[x<<1].r+1]-b[T[x<<1].l];
        T[x<<1].k=1;
        T[x<<1|1].s=b[T[x<<1|1].r+1]-b[T[x<<1|1].l];
        T[x<<1|1].k=1;
    }
    else if(T[x].k==-1)
    {
        T[x<<1].s=0;
        T[x<<1].k=-1;
        T[x<<1|1].s=0;
        T[x<<1|1].k=-1;
    }
    T[x].k=0;
}
void build(int x,int l,int r)
{
    T[x].l=l;
    T[x].r=r;
    T[x].k=T[x].s=0;
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
        T[x].k=k;
        if(k==1) T[x].s=b[T[x].r+1]-b[T[x].l];
        else if(k==-1) T[x].s=0;
        return;
    }
    pushdown(x);
    add(x<<1,l,r,k);
    add(x<<1|1,l,r,k);
    pushup(x);
}
int main()
{
    scanf("%lld%lld%d",&t1,&t2,&m);
    n=0;
    for(int i=1;i<=m;++i)
    {
        scanf("%lld%lld%d",&a[i].k,&a[i].x,&a[i].y);
        b[++n]=a[i].x;
        b[++n]=a[i].y;
    }
    sort(b+1,b+n+1);
    n=unique(b+1,b+n+1)-b-1;
    build(1,1,n-1);
    for(int i=1;i<=m;++i)
    {
        add(1,a[i].x,a[i].y,a[i].k==0?1:-1);
        printf("%lld\n",T[1].s);
    }
    return 0;
}