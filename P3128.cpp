#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,m,q,p=1,t[N];
struct tree
{
    int f,s,d,t,z,b,bm;
}T[N];
struct tree2
{
    int l,r,s,k;
}T2[N<<2];
struct road
{
    int m,q;
}a[N<<1];
void pushup(int x)
{
    T2[x].s=max(T2[x<<1].s,T2[x<<1|1].s);
}
void pushdown(int x)
{
    if(T2[x].k==0) return;
    T2[x<<1].s+=T2[x].k;
    T2[x<<1].k+=T2[x].k;
    T2[x<<1|1].s+=T2[x].k;
    T2[x<<1|1].k+=T2[x].k;
    T2[x].k=0;
}
void build(int x,int l,int r)
{
    T2[x].l=l;
    T2[x].r=r;
    T2[x].s=T2[x].k=0;
    if(l==r) return;
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    pushup(x);
}
void add(int x,int l,int r,int k)
{
    if(T2[x].l>=l&&T2[x].r<=r)
    {
        T2[x].s+=k;
        T2[x].k+=k;
        return;
    }
    pushdown(x);
    int z=T2[x].l+T2[x].r>>1;
    if(l<=z) add(x<<1,l,r,k);
    if(r>z) add(x<<1|1,l,r,k);
    pushup(x);
}
int sum(int x,int l,int r)
{
    if(T2[x].l>=l&&T2[x].r<=r)
    {
        return T2[x].s;
    }
    pushdown(x);
    int z=T2[x].l+T2[x].r>>1,s=0;
    if(l<=z) s=max(s,sum(x<<1,l,r));
    if(r>z) s=max(s,sum(x<<1|1,l,r));
    return s;
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
    T[x].b=++q;
    T[x].t=k;
    if(T[x].z!=0) dfs2(T[x].z,k);
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==T[x].f||a[i].m==T[x].z) continue;
        dfs2(a[i].m,a[i].m);
    }
    T[x].bm=q;
}
void change(int x,int y,int k)
{
    while(T[x].t!=T[y].t)
    {
        if(T[T[x].t].d>=T[T[y].t].d)
        {
            add(1,T[T[x].t].b,T[x].b,k);
            x=T[T[x].t].f;
        }
        else
        {
            add(1,T[T[y].t].b,T[y].b,k);
            y=T[T[y].t].f;
        }
    }
    if(T[x].d<T[y].d) add(1,T[x].b,T[y].b,k);
    else add(1,T[y].b,T[x].b,k);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n-1;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        road(x,y);
        road(y,x);
    }
    T[1].f=1;
    dfs1(1);
    dfs2(1,1);
    build(1,1,n);
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        change(x,y,1);
    }
    printf("%d",sum(1,1,n));
    return 0;
}