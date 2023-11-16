#include<cstdio>
#include<algorithm>
using namespace std;
const int N=30001;
int n,m,q,p=1,t[N],b[N];
struct tree
{
    int f,s,d,t,z;
}T[N];
struct tree2
{
    int l,r;
    int s,s2;
}T2[N<<2];
struct road
{
    int m,q;
}a[N<<1];
void pushup(int x)
{
    T2[x].s=T2[x<<1].s+T2[x<<1|1].s;
    T2[x].s2=max(T2[x<<1].s2,T2[x<<1|1].s2);
}
void build(int x,int l,int r)
{
    T2[x].l=l;
    T2[x].r=r;
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
        T2[x].s=T2[x].s2=k;
        return;
    }
    int z=T2[x].l+T2[x].r>>1;
    if(q<=z) add(x<<1,q,k);
    else add(x<<1|1,q,k);
    pushup(x);
}
int sum1(int x,int l,int r)
{
    if(T2[x].l>=l&&T2[x].r<=r)
    {
        return T2[x].s;
    }
    int z=T2[x].l+T2[x].r>>1,s=0;
    if(l<=z) s+=sum1(x<<1,l,r);
    if(r>z) s+=sum1(x<<1|1,l,r);
    return s;
}
int sum2(int x,int l,int r)
{
    if(T2[x].l>=l&&T2[x].r<=r)
    {
        return T2[x].s2;
    }
    int z=T2[x].l+T2[x].r>>1,s=-1e9;
    if(l<=z) s=max(s,sum2(x<<1,l,r));
    if(r>z) s=max(s,sum2(x<<1|1,l,r));
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
    b[x]=++q;
    T[x].t=k;
    if(T[x].z!=0) dfs2(T[x].z,k);
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==T[x].f||a[i].m==T[x].z) continue;
        dfs2(a[i].m,a[i].m);
    }
}
int LCA1(int x,int y)
{
    int s=0;
    while(T[x].t!=T[y].t)
    {
        if(T[T[x].t].d>=T[T[y].t].d)
        {
            s+=sum1(1,b[T[x].t],b[x]);
            x=T[T[x].t].f;
        }
        else
        {
            s+=sum1(1,b[T[y].t],b[y]);
            y=T[T[y].t].f;
        }
    }
    if(T[x].d<T[y].d) s+=sum1(1,b[x],b[y]);
    else s+=sum1(1,b[y],b[x]);
    return s;
}
int LCA2(int x,int y)
{
    int s=-1e9;
    while(T[x].t!=T[y].t)
    {
        if(T[T[x].t].d>=T[T[y].t].d)
        {
            s=max(s,sum2(1,b[T[x].t],b[x]));
            x=T[T[x].t].f;
        }
        else
        {
            s=max(s,sum2(1,b[T[y].t],b[y]));
            y=T[T[y].t].f;
        }
    }
    if(T[x].d<T[y].d) s=max(s,sum2(1,b[x],b[y]));
    else s=max(s,sum2(1,b[y],b[x]));
    return s;
}
int main()
{
    scanf("%d",&n);
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
    for(int i=1;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        add(1,b[i],x);
    }
    scanf("%d",&m);
    for(int i=1;i<=m;++i)
    {
        char z[10];
        int x,y;
        scanf("%s%d%d",z,&x,&y);
        if(z[1]=='H') add(1,b[x],y);
        else if(z[1]=='S') printf("%d\n",LCA1(x,y));
        else if(z[1]=='M') printf("%d\n",LCA2(x,y));
    }
    return 0;
}