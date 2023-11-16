#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,m,q,p=1,t[N],b[N],c[N];
struct tree
{
    int f,s,d,t,z;
}T[N];
struct tree2
{
    int l,r,s,k,cl,cr;
}T2[N<<2];
struct road
{
    int m,q;
}a[N<<1];
void pushup(int x)
{
    T2[x].s=T2[x<<1].s+T2[x<<1|1].s;
    if(T2[x<<1].cr==T2[x<<1|1].cl&&T2[x<<1].cr!=0) --T2[x].s;
    T2[x].cl=T2[x<<1].cl;
    T2[x].cr=T2[x<<1|1].cr;
}
void pushdown(int x)
{
    if(T2[x].k==0) return;
    T2[x<<1].s=1;
    T2[x<<1].cl=T2[x<<1].cr=T2[x<<1].k=T2[x].k;
    T2[x<<1|1].s=1;
    T2[x<<1|1].cl=T2[x<<1|1].cr=T2[x<<1|1].k=T2[x].k;
    T2[x].k=0;
}
void build(int x,int l,int r)
{
    T2[x].l=l;
    T2[x].r=r;
    T2[x].s=T2[x].k=T2[x].cl=T2[x].cr=0;
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
        T2[x].s=1;
        T2[x].cl=T2[x].cr=T2[x].k=k;
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
    if(l<=z) s+=sum(x<<1,l,r);
    if(r>z) s+=sum(x<<1|1,l,r);
    if(l<=z&&r>z&&T2[x<<1].cr==T2[x<<1|1].cl&&T2[x<<1].cr!=0) --s;
    return s;
}
int num(int x,int q)
{
    if(T2[x].l==T2[x].r)
    {
        return T2[x].cl;
    }
    pushdown(x);
    int z=T2[x].l+T2[x].r>>1;
    if(q<=z) return num(x<<1,q);
    else return num(x<<1|1,q);
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
int query(int x,int y)
{
    int s=0,z1=0,z2=0;
    while(T[x].t!=T[y].t)
    {
        if(T[T[x].t].d>=T[T[y].t].d)
        {
            s+=sum(1,b[T[x].t],b[x]);
            if(num(1,b[x])==z1) --s;
            z1=num(1,b[T[x].t]);
            x=T[T[x].t].f;
        }
        else
        {
            s+=sum(1,b[T[y].t],b[y]);
            if(num(1,b[y])==z2) --s;
            z2=num(1,b[T[y].t]);
            y=T[T[y].t].f;
        }
    }
    if(T[x].d<T[y].d)
    {
        s+=sum(1,b[x],b[y]);
        if(num(1,b[x])==z1) --s;
        if(num(1,b[y])==z2) --s;
        return s;
    }
    else
    {
        s+=sum(1,b[y],b[x]);
        if(num(1,b[x])==z1) --s;
        if(num(1,b[y])==z2) --s;
        return s;
    }
}
void change(int x,int y,int k)
{
    while(T[x].t!=T[y].t)
    {
        if(T[T[x].t].d>=T[T[y].t].d)
        {
            add(1,b[T[x].t],b[x],k);
            x=T[T[x].t].f;
        }
        else
        {
            add(1,b[T[y].t],b[y],k);
            y=T[T[y].t].f;
        }
    }
    if(T[x].d<T[y].d) add(1,b[x],b[y],k);
    else add(1,b[y],b[x],k);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&c[i]);
    }
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
        add(1,b[i],b[i],c[i]);
    }
    for(int i=1;i<=m;++i)
    {
        char z[20];
        scanf("%s",z);
        if(z[0]=='C')
        {
            int x,y,k;
            scanf("%d%d%d",&x,&y,&k);
            change(x,y,k);
        }
        else
        {
            int x,y;
            scanf("%d%d",&x,&y);
            printf("%d\n",query(x,y));
        }
    }
    return 0;
}