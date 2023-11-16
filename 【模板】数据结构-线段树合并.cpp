#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=10000001,M=100000;
struct str
{
    int x,s;
    friend str max(str a,str b)
    {
        if(a.s!=b.s) return a.s>b.s?a:b;
        return a.x<b.x?a:b;
    }
};
int n,m,rt[N],tot,p=1,t[N];
struct tree
{
    int f,s,d,t,z;
}T[N];
struct tree2
{
    int l,r;
    str s;
}T2[N];
struct road
{
    int m,q;
}a[N<<1];
void pushup(int x)
{
    T2[x].s=max(T2[T2[x].l].s,T2[T2[x].r].s);
}
void add(int &x,int l,int r,int q,int k)
{
    if(x==0)
    {
        x=++tot;
        if(l==r) T2[x].s=(str){l,0};
    }
    if(l==r)
    {
        T2[x].s.s+=k;
        return;
    }
    int z=l+r>>1;
    if(q<=z) add(T2[x].l,l,z,q,k);
    else add(T2[x].r,z+1,r,q,k);
    pushup(x);
}
int merge(int x1,int x2,int l,int r)
{
    if(x1==0) return x2;
    if(x2==0) return x1;
    if(l==r)
    {
        T2[x1].s.s=T2[x1].s.s+T2[x2].s.s;
        return x1;
    }
    int z=l+r>>1;
    T2[x1].l=merge(T2[x1].l,T2[x2].l,l,z);
    T2[x1].r=merge(T2[x1].r,T2[x2].r,z+1,r);
    pushup(x1);
    return x1;
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
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==T[x].f) continue;
        dfs(a[i].m);
        rt[x]=merge(rt[x],rt[a[i].m],1,M);
    }
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
    dfs1(1);
    dfs2(1,1);
    for(int i=1;i<=n;++i) rt[i]=++tot;
    for(int i=1;i<=m;++i)
    {
        int x,y,k;
        scanf("%d%d%d",&x,&y,&k);
        int z=LCA(x,y);
        if(T[z].f) add(rt[T[z].f],1,M,k,-1);
        add(rt[z],1,M,k,-1);
        add(rt[x],1,M,k,1);
        add(rt[y],1,M,k,1);
    }
    dfs(1);
    for(int i=1;i<=n;++i)
    {
        printf("%d\n",T2[rt[i]].s.x);
    }
    return 0;
}