#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=100001,M=300001;
struct Segment_tree
{
    struct tree
    {
        int l,r,s,k;
    }T[N<<2];
    ll a[N];
    void pushup(int x)
    {
        T[x].s=max(T[x<<1].s,T[x<<1|1].s);
    }
    void build(int x,int l,int r)
    {
        T[x].l=l;
        T[x].r=r;
        T[x].k=1e9;
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
    void add(int x,int l,int r,int k)
    {
        if(T[x].l>=l&&T[x].r<=r)
        {
            T[x].k=min(T[x].k,k);
            return;
        }
        int z=T[x].l+T[x].r>>1;
        if(l<=z) add(x<<1,l,r,k);
        if(r>z) add(x<<1|1,l,r,k);
    }
    int sum(int x,int l,int r)
    {
        if(T[x].l>=l&&T[x].r<=r)
        {
            return T[x].s;
        }
        int z=T[x].l+T[x].r>>1,s=0;
        if(l<=z) s=max(s,sum(x<<1,l,r));
        if(r>z) s=max(s,sum(x<<1|1,l,r));
        return s;
    }
    int num(int x,int q)
    {
        if(T[x].l==T[x].r)
        {
            return T[x].k;
        }
        int z=T[x].l+T[x].r>>1;
        if(q<=z) return min(T[x].k,num(x<<1,q));
        else return min(T[x].k,num(x<<1|1,q));
    }
}T2;
int n,m,q,p=1,t[N],fa[N],b[N],c[M];
ll r;
bool g[M],h[M];
struct tree
{
    int f,d,s,z,t,b;
}T[N];
struct road
{
    int m,q;
    ll w;
}a[N<<1];
struct road2
{
    int x,y,t;
    ll w;
}a2[M];
bool cmp(road2 a,road2 b)
{
    return a.w<b.w;
}
int find(int x)
{
    if(fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}
void road(int x,int y,ll w)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].w=w;
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
    T[x].b=++q;
    T[x].t=k;
    if(T[x].z!=0) dfs2(T[x].z,k);
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==T[x].f||a[i].m==T[x].z) continue;
        dfs2(a[i].m,a[i].m);
    }
}
int query(int x,int y)
{
    int s=0;
    while(T[x].t!=T[y].t)
    {
        if(T[T[x].t].d>=T[T[y].t].d)
        {
            s=max(s,T2.sum(1,T[T[x].t].b,T[x].b));
            x=T[T[x].t].f;
        }
        else
        {
            s=max(s,T2.sum(1,T[T[y].t].b,T[y].b));
            y=T[T[y].t].f;
        }
    }
    if(T[x].d<=T[y].d) s=max(s,T2.sum(1,T[x].b+1,T[y].b));
    else s=max(s,T2.sum(1,T[y].b+1,T[x].b));
    return s;
}
void change(int x,int y,int k)
{
    while(T[x].t!=T[y].t)
    {
        if(T[T[x].t].d>=T[T[y].t].d)
        {
            T2.add(1,T[T[x].t].b,T[x].b,k);
            x=T[T[x].t].f;
        }
        else
        {
            T2.add(1,T[T[y].t].b,T[y].b,k);
            y=T[T[y].t].f;
        }
    }
    if(T[x].d<=T[y].d) T2.add(1,T[x].b+1,T[y].b,k);
    else T2.add(1,T[y].b+1,T[x].b,k);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i)
    {
        scanf("%d%d%lld",&a2[i].x,&a2[i].y,&a2[i].w);
        a2[i].t=i;
        if(a2[i].x==a2[i].y) --i,--m;
    }
    sort(a2+1,a2+m+1,cmp);
    int z=0;
    for(int i=1;i<=n;++i) fa[i]=i;
    for(int i=1;i<=m;++i)
    {
        b[a2[i].t]=i;
        if(find(a2[i].x)!=find(a2[i].y))
        {
            fa[find(a2[i].x)]=find(a2[i].y);
            h[i]=true;
            r+=a2[i].w;
            road(a2[i].x,a2[i].y,a2[i].w);
            c[i]=p;
            road(a2[i].y,a2[i].x,a2[i].w);
            ++z;
            if(z==n-1) break;
        }
    }
    dfs1(1);
    dfs2(1,1);
    for(int i=2;i<=p;i+=2)
    {
        if(T[a[i].m].f==a[i^1].m)
        {
            T2.a[T[a[i].m].b]=a[i].w;
        }
        else
        {
            T2.a[T[a[i^1].m].b]=a[i].w;
        }
    }
    T2.build(1,1,n);
    for(int i=1;i<=m;++i)
    {
        if(h[i]==true) continue;
        int k=query(a2[i].x,a2[i].y);
        if(a2[i].w==k)
        {
            g[a2[i].t]=true;
            change(a2[i].x,a2[i].y,a2[i].w);
        }
    }
    for(int i=1;i<=m;++i)
    {
        if(h[i]==false) continue;
        int z;
        if(T[a[c[i]].m].f==a[c[i]+1].m)
        {
            z=T2.num(1,T[a[c[i]].m].b);
        }
        else
        {
            z=T2.num(1,T[a[c[i]+1].m].b);
        }
        if(z>a2[i].w) g[a2[i].t]=true;
    }
    for(int i=1;i<=m;++i)
    {
        if(h[b[i]]==false&&g[i]==false) printf("none\n");
        else if(h[b[i]]==true&&g[i]==true) printf("any\n");
        else printf("at least one\n");
    }
    return 0;
}