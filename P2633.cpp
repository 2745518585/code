#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,m,p=0,q,tot,b[N],c[N],rt[N],t[N];
struct road
{
    int m,q;
}a[N<<1];
struct tree
{
    int f,s,d,t,z;
}T[N];
struct tree2
{
    int l,r,s;
}T2[N<<2];
void pushup(int x)
{
    T2[x].s=T2[T2[x].l].s+T2[T2[x].r].s;
}
void build(int &x,int l,int r)
{
    x=++tot;
    if(l==r) return;
    int z=l+r>>1;
    build(T2[x].l,l,z);
    build(T2[x].r,z+1,r);
}
void modify(int &x,int l,int r,int q)
{
    T2[++tot]=T2[x];
    ++T2[tot].s;
    x=tot;
    if(l==r) return;
    int z=l+r>>1;
    if(q<=z) modify(T2[x].l,l,z,q);
    else modify(T2[x].r,z+1,r,q);
}
int sum(int x1,int x2,int x3,int x4,int l,int r,int q)
{
    if(l==r) return c[l];
    int z=l+r>>1,k=T2[T2[x1].l].s+T2[T2[x2].l].s-T2[T2[x3].l].s-T2[T2[x4].l].s;
    if(q<=k) return sum(T2[x1].l,T2[x2].l,T2[x3].l,T2[x4].l,l,z,q);
    else return sum(T2[x1].r,T2[x2].r,T2[x3].r,T2[x4].r,z+1,r,q-k);
}
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
    T[x].t=k;
    if(T[x].z!=0) dfs2(T[x].z,k);
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==T[x].f||a[i].m==T[x].z) continue;
        else dfs2(a[i].m,a[i].m);
    }
}
int LCA(int x,int y)
{
    while(T[x].t!=T[y].t)
    {
        if(T[T[x].t].d>=T[T[y].t].d) x=T[T[x].t].f;
        else y=T[T[y].t].f;
    }
    if(T[x].d<T[y].d) return x;
    else return y;
}
void dfs(int x)
{
    rt[x]=rt[T[x].f];
    modify(rt[x],1,q,b[x]);
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==T[x].f) continue;
        dfs(a[i].m);
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&b[i]);
        c[i]=b[i];
    }
    sort(c+1,c+n+1);
    q=unique(c+1,c+n+1)-c-1;
    for(int i=1;i<=n;++i)
    {
        b[i]=lower_bound(c+1,c+q+1,b[i])-c;
    }
    build(rt[0],1,q);
    for(int i=1;i<=n-1;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        road(x,y);
        road(y,x);
    }
    dfs1(1);
    dfs2(1,1);
    dfs(1);
    int las=0;
    for(int i=1;i<=m;++i)
    {
        int x,y,k;
        scanf("%d%d%d",&x,&y,&k);
        x^=las;
        int z=LCA(x,y);
        printf("%d\n",las=sum(rt[x],rt[y],rt[z],rt[T[z].f],1,q,k));
    }
    return 0;
}