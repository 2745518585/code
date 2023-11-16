#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=100001;
int n,m,k;
struct str
{
    int x,y,r;
}a[N];
struct tree
{
    int l,r,k;
    ll s;
}T[N<<2];
void pushup(int x)
{
    T[x].s=T[x<<1].s+T[x<<1|1].s;
}
void pushdown(int x)
{
    if(T[x].k==-1) return;
    T[x<<1].k=T[x].k;
    T[x<<1].s=(T[x<<1].r-T[x<<1].l+1)*T[x].k;
    T[x<<1|1].k=T[x].k;
    T[x<<1|1].s=(T[x<<1|1].r-T[x<<1|1].l+1)*T[x].k;
    T[x].k=-1;
}
void build(int x,int l,int r)
{
    T[x].l=l;
    T[x].r=r;
    T[x].k=-1;
    if(l==r)
    {
        T[x].s=0;
        return;
    }
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    pushup(x);
}
void add(int x,int l,int r,int k)
{
    if(T[x].l>=l&&T[x].r<=r)
    {
        T[x].k=k;
        T[x].s=(T[x].r-T[x].l+1)*k;
        return;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    if(l<=z) add(x<<1,l,r,k);
    if(r>z) add(x<<1|1,l,r,k);
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
int sum1(int x,int t)
{
    return a[t].y-int(sqrt(a[t].r*a[t].r-(a[t].x-x)*(a[t].x-x)));
}
int sum2(int x,int t)
{
    return a[t].y+int(sqrt(a[t].r*a[t].r-(a[t].x-x)*(a[t].x-x)));
}
int main()
{
    scanf("%d%d%d",&m,&n,&k);
    for(int i=1;i<=k;++i)
    {
        scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].r);
    }
    build(1,1,n);
    ll s=0;
    for(int i=1;i<=m;++i)
    {
        add(1,1,n,0);
        for(int j=1;j<=k;++j)
        {
            if(abs(a[j].x-i)<=a[j].r) add(1,sum1(i,j),sum2(i,j),j);
        }
        s+=k*n-sum(1,1,n);
    }
    printf("%lld",s);
    return 0;
}