#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=10000001;
int n,m;
long long a[N];
struct tree
{
    int l,r;
    ll s,m;
}T[N];
void pushup(int x)
{
    T[x].m=max(T[x<<1].m,T[x<<1|1].m);
    T[x].s=T[x<<1].s+T[x<<1|1].s;
}
void build(int x,int l,int r)
{
    T[x].l=l;
    T[x].r=r;
    if(l==r)
    {
        T[x].m=T[x].s=a[l];
        return;
    }
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    pushup(x);
}
void modify(int x,int l,int r)
{
    if(T[x].l==T[x].r)
    {
        T[x].s=sqrt(T[x].s);
        T[x].m=sqrt(T[x].m);
        return;
    }
    int z=T[x].l+T[x].r>>1;
    if(l<=z&&T[x<<1].m>1) modify(x<<1,l,r);
    if(r>z&&T[x<<1|1].m>1) modify(x<<1|1,l,r);
    pushup(x);
}
long long sum(int x,int l,int r)
{
    if(T[x].l>=l&&T[x].r<=r)
    {
        return T[x].s;
    }
    int z=T[x].l+T[x].r>>1;
    long long s=0;
    if(l<=z) s+=sum(x<<1,l,r);
    if(r>z) s+=sum(x<<1|1,l,r);
    return s;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&a[i]);
    }
    build(1,1,n);
    scanf("%d",&m);
    for(int i=1;i<=m;++i)
    {
        int x,y,z;
        scanf("%d%d%d",&z,&x,&y);
        if(z==1)
        {
            if(x>y) swap(x,y);
            printf("%lld\n",sum(1,x,y));
        }
        else if(z==2)
        {
            if(x>y) swap(x,y);
            modify(1,x,y);
        }
    }
    return 0;
}