#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,m,q,p=1,t[N],b[N];
struct tree
{
    int f,s,d,t,z,b,bm;
}T[N];
struct Segment_tree
{
    struct tree
    {
        int l,r,s;
    };
    tree T[N<<2];
    void pushup(int x)
    {
        T[x].s=T[x<<1].s^T[x<<1|1].s;
    }
    void build(int x,int l,int r)
    {
        T[x].l=l;
        T[x].r=r;
        if(l==r)
        {
            T[x].s=0;
            return;
        }
        int z=l+r>>1;
        build(x<<1,l,z);
        build(x<<1|1,z+1,r);
        pushup(x);
    }
    void change(int x,int q,int k)
    {
        if(T[x].l==T[x].r)
        {
            T[x].s=k;
            return;
        }
        int z=T[x].l+T[x].r>>1;
        if(q<=z) change(x<<1,q,k);
        else change(x<<1|1,q,k);
        pushup(x);
    }
    int sum(int x,int l,int r)
    {
        if(T[x].l>=l&&T[x].r<=r)
        {
            return T[x].s;
        }
        int z=T[x].l+T[x].r>>1,s=0;
        if(l<=z) s^=sum(x<<1,l,r);
        if(r>z) s^=sum(x<<1|1,l,r);
        return s;
    }
}T2;
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
int query(int x,int y)
{
    int s=0;
    while(T[x].t!=T[y].t)
    {
        if(T[T[x].t].d>=T[T[y].t].d)
        {
            s=(s^T2.sum(1,T[T[x].t].b,T[x].b));
            x=T[T[x].t].f;
        }
        else
        {
            s=(s^T2.sum(1,T[T[y].t].b,T[y].b));
            y=T[T[y].t].f;
        }
    }
    if(T[x].d<T[y].d) s=(s^T2.sum(1,T[x].b,T[y].b));
    else s=(s^T2.sum(1,T[y].b,T[x].b));
    return s;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&b[i]);
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
    T2.build(1,1,n);
    for(int i=1;i<=n;++i)
    {
        T2.change(1,T[i].b,b[i]);
    }
    for(int i=1;i<=m;++i)
    {
        int z;
        scanf("%d",&z);
        if(z==1)
        {
            int x,k;
            scanf("%d%d",&x,&k);
            T2.change(1,T[x].b,k);
        }
        else if(z==2)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            printf("%d\n",query(x,y));
        }
    }
    return 0;
}