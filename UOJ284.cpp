#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=300001;
int n,m,q,tot,b[N],b2[N],d[N],f[N],g[N],h[N];
ll e[N];
struct str
{
    int x,t;
    str(){}
    str(int x,int t):x(x),t(t){}
};
vector<int> a[N];
vector<str> c[N];
namespace sgt
{
    struct tree
    {
        int l,r,k,s;
    }T[N<<2];
    void pushup(int x)
    {
        T[x].s=max(T[x<<1].s,T[x<<1|1].s);
    }
    void pushdown(int x)
    {
        if(T[x].k==0) return;
        T[x<<1].s=max(T[x<<1].s,T[x].k);
        T[x<<1].k=max(T[x<<1].k,T[x].k);
        T[x<<1|1].s=max(T[x<<1|1].s,T[x].k);
        T[x<<1|1].k=max(T[x<<1|1].k,T[x].k);
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
    }
    void add(int x,int l,int r,int k)
    {
        if(T[x].l>=l&&T[x].r<=r)
        {
            T[x].s=max(T[x].s,k);
            T[x].k=max(T[x].k,k);
            return;
        }
        pushdown(x);
        int z=T[x].l+T[x].r>>1;
        if(l<=z) add(x<<1,l,r,k);
        if(r>z) add(x<<1|1,l,r,k);
        pushup(x);
    }
    ll sum(int x,int q)
    {
        if(T[x].l==T[x].r)
        {
            return T[x].s;
        }
        pushdown(x);
        int z=T[x].l+T[x].r>>1;
        if(q<=z) return sum(x<<1,q);
        else return sum(x<<1|1,q);
    }
}
struct tree
{
    int l,r,t,k;
    ll s;
}T[N<<2];
void pushup(int x)
{
    T[x].s=T[x<<1].s+T[x<<1|1].s;
    T[x].t=max(T[x<<1].t,T[x<<1|1].t);
}
void pushdown(int x)
{
    if(T[x].k==0) return;
    T[x<<1].s=(ll)T[x].k*(b2[T[x<<1].r]-b2[T[x<<1].l-1]);
    T[x<<1].t=T[x].k;
    T[x<<1].k=T[x].k;
    T[x<<1|1].s=(ll)T[x].k*(b2[T[x<<1|1].r]-b2[T[x<<1|1].l-1]);
    T[x<<1|1].t=T[x].k;
    T[x<<1|1].k=T[x].k;
    T[x].k=0;
}
void build(int x,int l,int r)
{
    T[x].l=l;
    T[x].r=r;
    if(l==r)
    {
        T[x].s=(ll)(n+1)*(b2[r]-b2[l-1]);
        T[x].t=n+1;
        T[x].k=0;
        return;
    }
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
        T[x].s=(ll)k*(b2[T[x].r]-b2[T[x].l-1]);
        T[x].t=k;
        T[x].k=k;
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
int sum2(int x,int k)
{
    if(T[x].l==T[x].r)
    {
        if(T[x].t>k) return T[x].l;
        return q+1;
    }
    pushdown(x);
    if(T[x<<1].t>k) return sum2(x<<1,k);
    return sum2(x<<1|1,k);
}
void dfs0(int x)
{
    g[x]=++tot;
    f[x]=1;
    for(auto i:a[x])
    {
        d[i]=d[x]+1;
        dfs0(i);
        f[x]+=f[i];
    }
    for(auto i:c[x])
    {
        h[i.t]=sgt::sum(1,g[i.x]);
    }
    sgt::add(1,g[x]+1,tot,b[x]);
}
void dfs2(int x)
{
    for(auto i:a[x]) dfs2(i);
    add(1,sum2(1,d[x]),b[x],d[x]);
}
void dfs(int x)
{
    int u=0;
    for(auto i:a[x])
    {
        if(f[i]>f[u]) u=i;
    }
    for(auto i:a[x])
    {
        if(i==u) continue;
        dfs(i);
        add(1,1,q,n+1);
    }
    if(u) dfs(u);
    for(auto i:a[x])
    {
        if(i==u) continue;
        dfs2(i);
    }
    for(auto i:c[x])
    {
        int z=h[i.t];
        e[i.t]=(sum(1,1,z)-(ll)d[x]*b2[z])+d[i.x]-d[x];
    }
    int z=sum2(1,d[x]);
    add(1,z,b[x],d[x]);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&b[i]);
        b2[++q]=b[i];
    }
    sort(b2+1,b2+q+1);
    q=unique(b2+1,b2+q+1)-b2-1;
    for(int i=1;i<=n;++i)
    {
        b[i]=lower_bound(b2+1,b2+q+1,b[i])-b2;
    }
    for(int i=2;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        a[x].push_back(i);
    }
    scanf("%d",&m);
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        c[x].push_back(str(y,i));
    }
    sgt::build(1,1,n);
    build(1,1,q);
    d[1]=1;
    dfs0(1);
    dfs(1);
    for(int i=1;i<=m;++i)
    {
        printf("%lld\n",e[i]);
    }
    return 0;
}