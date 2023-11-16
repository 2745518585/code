#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,a[N],b[N],c[N],d[N];
struct tree
{
    int l,r;
    ll s,k;
}T[N<<2];
void pushup(int x)
{
    T[x].s=max(T[x<<1].s,T[x<<1|1].s);
}
void pushdown(int x)
{
    if(T[x].k==0) return;
    T[x<<1].s+=T[x].k;
    T[x<<1].k+=T[x].k;
    T[x<<1|1].s+=T[x].k;
    T[x<<1|1].k+=T[x].k;
    T[x].k=0;
}
void build(int x,int l,int r)
{
    T[x].l=l;
    T[x].r=r;
    if(l==r) return;
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    pushup(x);
}
void add(int x,int l,int r,ll k)
{
    if(l>r) return;
    if(T[x].l>=l&&T[x].r<=r)
    {
        T[x].s+=k;
        T[x].k+=k;
        return;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    if(l<=z) add(x<<1,l,r,k);
    if(r>z) add(x<<1|1,l,r,k);
    pushup(x);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=m;++i)
    {
        scanf("%d",&b[i]);
    }
    build(1,1,n);
    ll s=0;
    for(int i=1;i<=n;++i)
    {
        add(1,c[a[i]]+1,d[a[i]],-b[a[i]]);
        add(1,d[a[i]]+1,i,b[a[i]]);
        s=max(s,T[1].s);
        c[a[i]]=d[a[i]];
        d[a[i]]=i;
    }
    printf("%lld",s);
    return 0;
}