#include<cstdio>
#include<algorithm>
#define ll long long 
using namespace std;
struct str
{
    int l,r,k;
    ll s;
}T[10000001];
int n,m,a[10000001];
void pushdown(int x)
{
    T[x<<1].k+=T[x].k;
    T[x<<1].s+=(T[x<<1].r-T[x<<1].l+1)*T[x].k;
    T[x<<1|1].k+=T[x].k;
    T[x<<1|1].s+=(T[x<<1|1].r-T[x<<1|1].l+1)*T[x].k;
    T[x].k=0;
}
void build(int x,int l,int r)
{
    T[x].l=l;
    T[x].r=r;
    if(l==r)
    {
        T[x].s=a[l];
        return;
    }
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    T[x].s=T[x<<1].s+T[x<<1|1].s;
}
void check(int x,int l,int r,int k)
{
    if(T[x].l>=l&&T[x].r<=r)
    {
        T[x].k+=k;
        T[x].s+=(T[x].r-T[x].l+1)*k;
        return;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    if(l<=z) check(x<<1,l,min(z,r),k);
    if(r>z) check(x<<1|1,max(z+1,l),r,k);
    T[x].s=T[x<<1].s+T[x<<1|1].s;
}
ll sum(int x,int l,int r)
{
    if(T[x].l>=l&&T[x].r<=r)
    {
        return T[x].s;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    ll s=0;
    if(l<=z) s+=sum(x<<1,l,r);
    if(r>z) s+=sum(x<<1|1,l,r);
    return s;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    build(1,1,n);
    for(int i=1;i<=m;++i)
    {
        int z,x,y;
        scanf("%d%d%d",&z,&x,&y);
        if(z==1)
        {
            int k;
            scanf("%d",&k);
            check(1,x,y,k);
        }
        else
        {
            printf("%lld\n",sum(1,x,y));
        }
    }
    return 0;
}