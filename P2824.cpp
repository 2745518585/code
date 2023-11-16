#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
struct tree
{
    int l,r,k;
    ll s;
}T[N<<2];
int a[N],b[N];
struct str
{
    int l,r,k;
}c[N];
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
    if(l==r) return;
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    pushup(x);
}
void add(int x,int l,int r,int k)
{
    if(l>r) return;
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
    if(l>r) return 0;
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
int n,m,k;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        b[i]=a[i];
    }
    sort(b+1,b+n+1);
    for(int i=1;i<=m;++i)
    {
        scanf("%d%d%d",&c[i].k,&c[i].l,&c[i].r);
    }
    scanf("%d",&k);
    build(1,1,n);
    int l=1,r=n;
    while(l<r)
    {
        int z=l+r>>1;
        for(int i=1;i<=n;++i)
        {
            add(1,i,i,a[i]<=b[z]);
        }
        for(int i=1;i<=m;++i)
        {
            int k=sum(1,c[i].l,c[i].r);
            if(c[i].k==0)
            {
                add(1,c[i].l,c[i].l+k-1,1);
                add(1,c[i].l+k,c[i].r,0);
            }
            else
            {
                add(1,c[i].r-k+1,c[i].r,1);
                add(1,c[i].l,c[i].r-k,0);
            }
        }
        if(sum(1,k,k)==1) r=z;
        else l=z+1;
    }
    printf("%d",b[l]);
    return 0;
}