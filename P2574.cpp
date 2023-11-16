#include<cstdio>
using namespace std;
typedef long long ll;
int n,m,a[100001];
struct tree
{
    int l,r,k;
    ll s;
}T[1000001];
void pushup(int x)
{
    T[x].s=T[x<<1].s+T[x<<1|1].s;
}
void pushdown(int x)
{
    if(T[x].k==0) return;
    T[x<<1].s=(T[x<<1].r-T[x<<1].l+1)-T[x<<1].s;
    T[x<<1].k^=T[x].k;
    T[x<<1|1].s=(T[x<<1|1].r-T[x<<1|1].l+1)-T[x<<1|1].s;
    T[x<<1|1].k^=T[x].k;
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
    pushup(x);
}
void modify(int x,int l,int r)
{
    if(T[x].l>=l&&T[x].r<=r)
    {
        T[x].s=(T[x].r-T[x].l+1)-T[x].s;
        T[x].k^=1;
        return;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    if(l<=z) modify(x<<1,l,r);
    if(r>z) modify(x<<1|1,l,r);
    pushup(x);
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
    scanf("%d %d\n",&n,&m);
    for(int i=1;i<=n;++i)
    {
        a[i]=getchar()-'0';
    }
    build(1,1,n);
    for(int i=1;i<=m;++i)
    {
        int z;
        scanf("%d",&z);
        if(z==0)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            modify(1,x,y);
        }
        else if(z==1)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            printf("%lld\n",sum(1,x,y));
        }
    }
    return 0;
}