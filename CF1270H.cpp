#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,m,a[N],b[N],c1[N],c2[N],g[N];
bool h[N];
struct tree
{
    int l,r,s,t,k;
}T[N<<2];
void pushup(int x)
{
    if(T[x<<1].t==T[x<<1|1].t)
    {
        T[x].s=T[x<<1].s+T[x<<1|1].s;
        T[x].t=T[x<<1].t;
    }
    else if((T[x<<1].s?T[x<<1].t:1e9)<(T[x<<1|1].s?T[x<<1|1].t:1e9))
    {
        T[x].s=T[x<<1].s;
        T[x].t=T[x<<1].t;
    }
    else
    {
        T[x].s=T[x<<1|1].s;
        T[x].t=T[x<<1|1].t;
    }
}
void pushdown(int x)
{
    if(T[x].k==0) return;
    T[x<<1].t+=T[x].k;
    T[x<<1].k+=T[x].k;
    T[x<<1|1].t+=T[x].k;
    T[x<<1|1].k+=T[x].k;
    T[x].k=0;
}
void build(int x,int l,int r)
{
    T[x].l=l;
    T[x].r=r;
    T[x].s=T[x].t=T[x].k=0;
    if(l==r) return;
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    pushup(x);
}
void add1(int x,int l,int r,int k)
{
    if(T[x].l>=l&&T[x].r<=r)
    {
        T[x].t+=k;
        T[x].k+=k;
        return;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    if(l<=z) add1(x<<1,l,r,k);
    if(r>z) add1(x<<1|1,l,r,k);
    pushup(x);
}
void add2(int x,int q,int k)
{
    if(T[x].l==T[x].r)
    {
        T[x].s=k;
        return;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    if(q<=z) add2(x<<1,q,k);
    else add2(x<<1|1,q,k);
    pushup(x);
}
tree sum(int x,int q)
{
    if(T[x].l==T[x].r) return T[x];
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    if(q<=z) return sum(x<<1,q);
    else return sum(x<<1|1,q);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        b[++m]=a[i];
    }
    a[0]=1e9,a[n+1]=-1e9;
    b[++m]=a[0],b[++m]=a[n+1];
    for(int i=1;i<=m;++i)
    {
        scanf("%d%d",&c1[i],&c2[i]);
        b[++m]=c2[i];
    }
    sort(b+1,b+m+1);
    m=unique(b+1,b+m+1)-b-1;
    for(int i=0;i<=n+1;++i)
    {
        a[i]=lower_bound(b+1,b+m+1,a[i])-b;
    }
    for(int i=1;i<=m;++i)
    {
        c2[i]=lower_bound(b+1,b+m+1,c2[i])-b;
    }
    build(1,1,m);
    for(int i=1;i<=n;++i) add2(1,a[i],1);
    for(int i=0;i<=n;++i)
    {
        if(a[i]>a[i+1]) add1(1,a[i+1],a[i]-1,1);
    }
    for(int i=1;i<=m;++i)
    {
        int x=c1[i];
        if(a[x-1]>a[x]) add1(1,a[x],a[x-1]-1,-1);
        if(a[x]>a[x+1]) add1(1,a[x+1],a[x]-1,-1);
        add2(1,a[x],0);
        a[x]=c2[i];
        if(a[x-1]>a[x]) add1(1,a[x],a[x-1]-1,1);
        if(a[x]>a[x+1]) add1(1,a[x+1],a[x]-1,1);
        add2(1,a[x],1);
        if(T[1].t==1) printf("%d\n",T[1].s);
        else printf("0\n");
    }
    return 0;
}