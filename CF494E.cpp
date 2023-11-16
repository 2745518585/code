#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=2000001;
int n,m,k;
ll b[N];
struct square
{
    int x1,y1,x2,y2;
}d[N];
struct str
{
    ll l,r,h;
    int k;
}a[N];
struct tree
{
    int l,r,t;
    ll s;
}T[N];
bool cmp(str a,str b)
{
    return a.h<b.h;
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
    if(l==r)
    {
        T[x<<1].s=T[x<<1|1].s=0;
        return;
    }
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
ll solve(int x)
{
    for(int i=1;i<=n;++i)
    {
        ll x1=(d[i].x1-1)/x,y1=(d[i].y1-1)/x,x2=d[i].x2/x,y2=d[i].y2/x;
        a[i*2-1]=(str){x1,x2,y1,1};
        a[i*2]=(str){x1,x2,y2,-1};
        b[i*2-1]=x1;
        b[i*2]=x2;
    }
    sort(a+1,a+n*2+1,cmp);
    sort(b+1,b+n*2+1);
    m=unique(b+1,b+n*2+1)-b-1;
    if(m==1) return 0;
    build(1,1,m-1);
    ll s=0;
    for(int i=1;i<n*2;++i)
    {
        add(1,a[i].l,a[i].r,a[i].k);
        s+=T[1].s*(a[i+1].h-a[i].h);
    }
    return s;
}
int main()
{
    scanf("%*d%d%d",&n,&k);
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d%d%d",&d[i].x1,&d[i].y1,&d[i].x2,&d[i].y2);
    }
    for(int i=0;(1<<i)<=k;++i)
    {
        if(solve(1<<i)%2==1)
        {
            printf("Hamed");
            return 0;
        }
    }
    printf("Malek");
    return 0;
}