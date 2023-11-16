#include<cstdio>
using namespace std;
typedef long long ll;
int n,m,p,a[10000001];
struct tree
{
    int l,r;
    ll s,k1,k2;
}T[100000001];
void plus(int x,ll k1,ll k2)
{
    T[x].s=(T[x].s*k1+(T[x].r-T[x].l+1)*k2)%p;
    T[x].k1=(T[x].k1*k1)%p;
    T[x].k2=(T[x].k2*k1+k2)%p;
}
void pushdown(int x)
{
    plus(x<<1,T[x].k1,T[x].k2);
    plus(x<<1|1,T[x].k1,T[x].k2);
    T[x].k1=1;
    T[x].k2=0;
}
void pushup(int x)
{
    T[x].s=(T[x<<1].s+T[x<<1|1].s)%p;
}
void build(int x,int l,int r)
{
    T[x].l=l;
    T[x].r=r;
    T[x].k1=1;
    T[x].k2=0;
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
void modify1(int x,int l,int r,int k)
{
    if(T[x].l>=l&&T[x].r<=r)
    {
        T[x].s=T[x].s*k%p;
        T[x].k1=T[x].k1*k%p;
        T[x].k2=T[x].k2*k%p;
        return;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    if(l<=z) modify1(x<<1,l,r,k);
    if(r>z) modify1(x<<1|1,l,r,k);
    pushup(x);
}
void modify2(int x,int l,int r,int k)
{
    if(T[x].l>=l&&T[x].r<=r)
    {
        T[x].s=(T[x].s+(T[x].r-T[x].l+1)*k)%p;
        T[x].k2=(T[x].k2+k)%p;
        return;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    if(l<=z) modify2(x<<1,l,r,k);
    if(r>z) modify2(x<<1|1,l,r,k);
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
    if(l<=z) s=(s+sum(x<<1,l,r))%p;
    if(r>z) s=(s+sum(x<<1|1,l,r))%p;
    return s;
}
int main()
{
    scanf("%d%d%d",&n,&m,&p);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    build(1,1,n);
    for(int i=1;i<=m;++i)
    {
        int z;
        scanf("%d",&z);
        if(z==1)
        {
            int x,y,k;
            scanf("%d%d%d",&x,&y,&k);
            modify1(1,x,y,k);
        }
        if(z==2)
        {
            int x,y,k;
            scanf("%d%d%d",&x,&y,&k);
            modify2(1,x,y,k);
        }
        if(z==3)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            printf("%lld\n",sum(1,x,y));
        }
        // for(int i=1;i<=n*2;++i)
        // {
        //     printf("%d %d %d %lld %lld %lld\n",i,T[i].l,T[i].r,T[i].s,T[i].k1,T[i].k2);
        // }
        // printf("\n");
    }
}