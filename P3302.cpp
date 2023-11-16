#include<cstdio>
#include<algorithm>
using namespace std;
const int N=100001;
int n,m,q,o,tot,p=1,t[N],b[N],c[N],rt[N],fa[N],ga[N];
struct tree
{
    int f,s,d,t,z;
}T[N];
struct tree2
{
    int l,r,s;
}T2[N*200];
struct road
{
    int m,q;
}a[N<<1];
int find(int x)
{
    if(fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
void pushup(int x)
{
    T2[x].s=T2[T2[x].l].s+T2[T2[x].r].s;
}
void add(int &x,int ls,int rs,int q)
{
    T2[++tot]=T2[x];
    x=tot;
    if(ls==rs)
    {
        ++T2[x].s;
        return;
    }
    int z=ls+rs>>1;
    if(q<=z) add(T2[x].l,ls,z,q);
    else add(T2[x].r,z+1,rs,q);
    pushup(x);
}
int sum(int x1,int x2,int x3,int x4,int ls,int rs,int k)
{
    if(ls==rs) return ls;
    int z=ls+rs>>1,p=T2[T2[x1].l].s+T2[T2[x2].l].s-T2[T2[x3].l].s-T2[T2[x4].l].s;
    if(k<=p) return sum(T2[x1].l,T2[x2].l,T2[x3].l,T2[x4].l,ls,z,k);
    else return sum(T2[x1].r,T2[x2].r,T2[x3].r,T2[x4].r,z+1,rs,k-p);
}
void dfs1(int x)
{
    rt[x]=rt[T[x].f];
    add(rt[x],1,o,b[x]);
    T[x].s=1;
    T[x].d=T[T[x].f].d+1;
    T[x].z=0;
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
int main()
{
    scanf("%*d%d%d%d",&n,&m,&q);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&b[i]);
        c[i]=b[i];
    }
    sort(c+1,c+n+1);
    o=unique(c+1,c+n+1)-c-1;
    for(int i=1;i<=n;++i)
    {
        b[i]=lower_bound(c+1,c+o+1,b[i])-c;
    }
    for(int i=1;i<=n;++i) fa[i]=i,ga[i]=1;
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        road(x,y);
        road(y,x);
        ga[find(x)]+=ga[find(y)];
        ga[find(y)]=0;
        fa[find(y)]=find(x);
    }
    for(int i=1;i<=n;++i)
    {
        if(find(i)==i)
        {
            dfs1(i);
            dfs2(i,i);
        }
    }
    int las=0;
    for(int i=1;i<=q;++i)
    {
        char z[10];
        scanf("%s",z);
        if(z[0]=='L')
        {
            int x,y;
            scanf("%d%d",&x,&y);
            x^=las,y^=las;
            if(ga[find(x)]<ga[find(y)]) swap(x,y);
            road(x,y);
            road(y,x);
            T[y].f=x;
            dfs1(y);
            if(T[x].z==0) T[x].z=y,dfs2(y,T[x].t);
            else dfs2(y,y);
            ga[find(x)]+=ga[find(y)];
            ga[find(y)]=0;
            fa[find(y)]=find(x);
        }
        else if(z[0]=='Q')
        {
            int x,y,k;
            scanf("%d%d%d",&x,&y,&k);
            x^=las,y^=las,k^=las;
            int z=LCA(x,y);
            printf("%d\n",las=c[sum(rt[x],rt[y],rt[z],rt[T[z].f],1,o,k)]);
        }
    }
    return 0;
}