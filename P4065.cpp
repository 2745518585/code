#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,a[N],b[N],c[N];
struct tree
{
    int l,r,k,s,s2;
}T[N<<2];
void pushup(int x)
{
    T[x].s=T[x<<1].s+T[x<<1|1].s;
    T[x].s2=max(T[x<<1].s2,T[x<<1|1].s2);
}
void pushdown(int x)
{
    if(T[x].k==0) return;
    T[x<<1].k=1;
    T[x<<1].s=0;
    T[x<<1|1].k=1;
    T[x<<1|1].s=0;
    T[x].k=0;
}
void build(int x,int l,int r)
{
    T[x].l=l;
    T[x].r=r;
    T[x].k=0;
    if(l==r)
    {
        T[x].s=1;
        T[x].s2=0;
        return;
    }
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    pushup(x);
}
void add(int x,int l,int r)
{
    if(l>r) return;
    if(T[x].l>=l&&T[x].r<=r)
    {
        T[x].k=1;
        T[x].s=0;
        return;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    if(l<=z) add(x<<1,l,r);
    if(r>z) add(x<<1|1,l,r);
    pushup(x);
}
void add2(int x,int q,int k)
{
    if(T[x].l==T[x].r)
    {
        T[x].s2=k;
        return;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    if(q<=z) add2(x<<1,q,k);
    else add2(x<<1|1,q,k);
    pushup(x);
}
int sum(int x,int l,int r)
{
    if(l>r) return 0;
    if(T[x].l>=l&&T[x].r<=r)
    {
        return T[x].s;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1,s=0;
    if(l<=z) s+=sum(x<<1,l,r);
    if(r>z) s+=sum(x<<1|1,l,r);
    return s;
}
int sum2(int x,int l,int r)
{
    if(T[x].l>=l&&T[x].r<=r)
    {
        return T[x].s2;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1,s=0;
    if(l<=z) s=max(s,sum2(x<<1,l,r));
    if(r>z) s=max(s,sum2(x<<1|1,l,r));
    return s;
}
void abc()
{
    scanf("%d",&n);
    build(1,1,n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        b[i]=c[i]=0;
    }
    for(int i=1;i<=n;++i)
    {
        b[a[i]]=i;
        if(c[a[i]]==0) c[a[i]]=i;
    }
    ll s=0;
    for(int i=1;i<=n;++i)
    {
        if(b[a[i]]==i)
        {
            add(1,c[a[i]]+1,i);
            add2(1,a[i],0);
        }
        else add2(1,a[i],i);
        s+=sum(1,T[1].s2+1,i);
    }
    printf("%lld\n",s);
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--) abc();
    return 0;
}