#include<cstdio>
#include<algorithm>
using namespace std;
const int N=10001,M=50001;
int n,m,k,q,p=1,t[N],f[N];
struct tree
{
    int f,s,d,t,z,b;
}T[N];
struct tree2
{
    int l,r,s;
}T2[N<<2];
struct road
{
    int m,q,w;
}a[N<<1];
struct road2
{
    int x,y,s;
}b[M];
bool cmp(road2 a,road2 b)
{
    return a.s>b.s;
}
int fa(int x)
{
    if(f[x]==x) return x;
    return f[x]=fa(f[x]);
}
void pushup(int x)
{
    T2[x].s=min(T2[x<<1].s,T2[x<<1|1].s);
}
void build(int x,int l,int r)
{
    T2[x].l=l;
    T2[x].r=r;
    T2[x].s=0;
    if(l==r) return;
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    pushup(x);
}
void add(int x,int q,int k)
{
    if(T2[x].l==T2[x].r)
    {
        T2[x].s=k;
        return;
    }
    int z=T2[x].l+T2[x].r>>1;
    if(q<=z) add(x<<1,q,k);
    else add(x<<1|1,q,k);
    pushup(x);
}
int sum(int x,int l,int r)
{
    if(T2[x].l>=l&&T2[x].r<=r)
    {
        return T2[x].s;
    }
    int z=T2[x].l+T2[x].r>>1,s=1e9;
    if(l<=z) s=min(s,sum(x<<1,l,r));
    if(r>z) s=min(s,sum(x<<1|1,l,r));
    return s;
}
void road(int x,int y,int w)
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
    int s=1e9;
    while(T[x].t!=T[y].t)
    {
        if(T[T[x].t].d>=T[T[y].t].d)
        {
            s=min(s,sum(1,T[T[x].t].b,T[x].b));
            x=T[T[x].t].f;
        }
        else
        {
            s=min(s,sum(1,T[T[y].t].b,T[y].b));
            y=T[T[y].t].f;
        }
    }
    if(T[x].d<T[y].d) s=min(s,sum(1,T[x].b+1,T[y].b));
    else s=min(s,sum(1,T[y].b+1,T[x].b));
    return s;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i)
    {
        scanf("%d%d%d",&b[i].x,&b[i].y,&b[i].s);
    }
    sort(b+1,b+m+1,cmp);
    for(int i=1;i<=n;++i) f[i]=i;
    for(int i=1;i<=m;++i)
    {
        if(fa(b[i].x)!=fa(b[i].y))
        {
            f[fa(b[i].x)]=fa(b[i].y);
            road(b[i].x,b[i].y,b[i].s);
            road(b[i].y,b[i].x,b[i].s);
        }
    }
    T[1].f=1;
    dfs1(1);
    dfs2(1,1);
    build(1,1,n);
    add(1,1,1e9);
    for(int i=2;i<=n;++i)
    {
        for(int j=t[T[i].f];j!=0;j=a[j].q)
        {
            if(a[j].m==i)
            {
                add(1,T[i].b,a[j].w);
                break;
            }
        }
    }
    scanf("%d",&k);
    for(int i=1;i<=k;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        if(fa(x)!=fa(y)) printf("-1\n");
        else printf("%d\n",query(x,y));
    }
    return 0;
}