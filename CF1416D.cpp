#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,m,q,tot,b[N],d[N],fa[N],g[N][2],r[N],rm[N];
bool h[N];
struct road
{
    int x,y;
}a[N];
struct query
{
    int z,x;
}c[N];
int find(int x)
{
    if(fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}
int dmax(int x,int y)
{
    return b[x]>b[y]?x:y;
}
struct tree
{
    int l,r,s;
}T[N<<2];
void pushup(int x)
{
    T[x].s=dmax(T[x<<1].s,T[x<<1|1].s);
}
void build(int x,int l,int r)
{
    T[x].l=l;
    T[x].r=r;
    if(l==r) return;
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    pushup(x);
}
void add(int x,int q,int k)
{
    if(T[x].l==T[x].r)
    {
        T[x].s=k;
        return;
    }
    int z=T[x].l+T[x].r>>1;
    if(q<=z) add(x<<1,q,k);
    else add(x<<1|1,q,k);
    pushup(x);
}
int sum(int x,int l,int r)
{
    if(T[x].l>=l&&T[x].r<=r)
    {
        return T[x].s;
    }
    int z=T[x].l+T[x].r>>1,s=0;
    if(l<=z) s=dmax(s,sum(x<<1,l,r));
    if(r>z) s=dmax(s,sum(x<<1|1,l,r));
    return s;
}
void dfs(int x)
{
    if(x==0) return;
    if(x<=n) r[x]=rm[x]=++tot;
    else
    {
        r[x]=tot+1;
        dfs(g[x][0]);
        dfs(g[x][1]);
        rm[x]=tot;
    }
}
int main()
{
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&b[i]);
    }
    for(int i=1;i<=m;++i)
    {
        scanf("%d%d",&a[i].x,&a[i].y);
    }
    for(int i=1;i<=q;++i)
    {
        scanf("%d%d",&c[i].z,&c[i].x);
        if(c[i].z==2) h[c[i].x]=true;
    }
    for(int i=1;i<=n+m;++i) fa[i]=i;
    for(int i=1;i<=m;++i)
    {
        if(h[i]) continue;
        int x=find(a[i].x),y=find(a[i].y);
        if(x!=y)
        {
            g[n+i][0]=x;
            g[n+i][1]=y;
            fa[x]=n+i;
            fa[y]=n+i;
        }
    }
    for(int i=q;i>=1;--i)
    {
        if(c[i].z==1) d[i]=find(c[i].x);
        else
        {
            int x=find(a[c[i].x].x),y=find(a[c[i].x].y);
            if(x!=y)
            {
                g[n+c[i].x][0]=x;
                g[n+c[i].x][1]=y;
                fa[x]=n+c[i].x;
                fa[y]=n+c[i].x;
            }
        }
    }
    for(int i=1;i<=n+m;++i)
    {
        if(find(i)==i) dfs(i);
    }
    build(1,1,n);
    for(int i=1;i<=n;++i) add(1,r[i],i);
    for(int i=1;i<=q;++i)
    {
        if(c[i].z==1)
        {
            int z=sum(1,r[d[i]],rm[d[i]]);
            printf("%d\n",b[z]);
            b[z]=0;
            add(1,r[z],z);
        }
    }
    return 0;
}