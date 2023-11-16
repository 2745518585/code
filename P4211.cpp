#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=50001;
const ll P=201314;
int n,m,tot,p=1,t[N],rt[N];
ll c[N];
struct str
{
    int x,u,t;
};
vector<str> b[N];
namespace Segment_tree
{
    struct tree
    {
        int l,r,s,k;
    }T[N<<2];
    struct road
    {
        int m,q;
    }a[N<<1];
    void pushup(int x)
    {
        T[x].s=T[x<<1].s+T[x<<1|1].s;
    }
    void pushdown(int x)
    {
        if(T[x].k==0) return;
        T[x<<1].s=(T[x<<1].s+(T[x<<1].r-T[x<<1].l+1)*T[x].k%P)%P;
        T[x<<1].k=(T[x<<1].k+T[x].k)%P;
        T[x<<1|1].s=(T[x<<1|1].s+(T[x<<1|1].r-T[x<<1|1].l+1)*T[x].k%P)%P;
        T[x<<1|1].k=(T[x<<1|1].k+T[x].k)%P;
        T[x].k=0;
    }
    void build(int x,int l,int r)
    {
        T[x].l=l;
        T[x].r=r;
        T[x].s=T[x].k=0;
        if(l==r) return;
        int z=l+r>>1;
        build(x<<1,l,z);
        build(x<<1|1,z+1,r);
        pushup(x);
    }
    void add(int x,int l,int r,int k)
    {
        if(T[x].l>=l&&T[x].r<=r)
        {
            T[x].s=(T[x].s+(T[x].r-T[x].l+1)*k%P)%P;
            T[x].k=(T[x].k+k)%P;
            return;
        }
        pushdown(x);
        int z=T[x].l+T[x].r>>1;
        if(l<=z) add(x<<1,l,r,k);
        if(r>z) add(x<<1|1,l,r,k);
        pushup(x);
    }
    int sum(int x,int l,int r)
    {
        if(T[x].l>=l&&T[x].r<=r)
        {
            return T[x].s;
        }
        pushdown(x);
        int z=T[x].l+T[x].r>>1,s=0;
        if(l<=z) s=(s+sum(x<<1,l,r))%P;
        if(r>z) s=(s+sum(x<<1|1,l,r))%P;
        return s;
    }
}
struct tree
{
    int f,s,d,t,z,b;
}T[N];
struct road
{
    int m,q;
}a[N<<1];
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
void dfs1(int x)
{
    T[x].s=1;
    T[x].d=T[T[x].f].d+1;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==T[x].f) continue;
        T[a[i].m].f=x;
        dfs1(a[i].m);
        T[x].s+=T[a[i].m].s;
        if(T[a[i].m].s>T[T[x].z].s) T[x].z=a[i].m;
    }
}
void dfs2(int x,int k)
{
    T[x].b=++tot;
    T[x].t=k;
    if(T[x].z!=0) dfs2(T[x].z,k);
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==T[x].f||a[i].m==T[x].z) continue;
        dfs2(a[i].m,a[i].m);
    }
}
void change(int x)
{
    while(x!=0)
    {
        Segment_tree::add(1,T[T[x].t].b,T[x].b,1);
        x=T[T[x].t].f;
    }
}
ll query(int x)
{
    ll s=0;
    while(x!=0)
    {
        s=(s+Segment_tree::sum(1,T[T[x].t].b,T[x].b))%P;
        x=T[T[x].t].f;
    }
    return s;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=2;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        ++x;
        road(x,i);
        road(i,x);
    }
    dfs1(1);
    dfs2(1,1);
    Segment_tree::build(1,1,n);
    for(int i=1;i<=m;++i)
    {
        int l,r,k;
        scanf("%d%d%d",&l,&r,&k);
        ++l,++r,++k;
        b[l-1].push_back((str){k,-1,i});
        b[r].push_back((str){k,1,i});
    }
    for(int i=1;i<=n;++i)
    {
        change(i);
        for(int j=0;j<b[i].size();++j)
        {
            c[b[i][j].t]+=b[i][j].u*query(b[i][j].x);
        }
    }
    for(int i=1;i<=m;++i)
    {
        printf("%lld\n",(c[i]%P+P)%P);
    }
    return 0;
}