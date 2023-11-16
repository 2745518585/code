#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,q,p=1,t[N];
struct tree
{
    int f,s,d,t,z,b,bm;
}T[N];
struct Segment_tree
{
    struct tree
    {
        int l,r,k;
        ll s;
    };
    tree T[N<<2];
    void pushup(int x)
    {
        T[x].s=T[x<<1].s+T[x<<1|1].s;
    }
    void pushdown(int x)
    {
        if(T[x].k==0) return;
        T[x<<1].k+=T[x].k;
        T[x<<1].s+=(T[x<<1].r-T[x<<1].l+1)*T[x].k;
        T[x<<1|1].k+=T[x].k;
        T[x<<1|1].s+=(T[x<<1|1].r-T[x<<1|1].l+1)*T[x].k;
        T[x].k=0;
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
            T[x].s+=k;
            return;
        }
        pushdown(x);
        int z=T[x].l+T[x].r>>1;
        if(q<=z) change(x<<1,q,k);
        else change(x<<1|1,q,k);
        pushup(x);
    }
    void add(int x,int l,int r,int k)
    {
        if(T[x].l>=l&&T[x].r<=r)
        {
            T[x].k+=k;
            T[x].s+=(T[x].r-T[x].l+1)*k;
            return;
        }
        pushdown(x);
        int z=T[x].l+T[x].r>>1;
        if(l<=z) add(x<<1,l,r,k);
        if(r>z) add(x<<1|1,l,r,k);
        pushup(x);
    }
    ll num(int x,int q)
    {
        if(T[x].l==T[x].r)
        {
            return T[x].s;
        }
        pushdown(x);
        int z=T[x].l+T[x].r>>1;
        ll s=0;
        if(q<=z) return num(x<<1,q);
        else return num(x<<1|1,q);
    }
    ll sum(int x,int l,int r)
    {
        if(T[x].l>=l&&T[x].r<=r)
        {
            return T[x].s;
        }
        pushdown(x);
        int z=T[x].l+T[x].r>>1;
        ll s=0;
        if(l<=z) s+=sum(x<<1,l,r);
        if(r>z) s+=sum(x<<1|1,l,r);
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
void change(int x,int y)
{
    while(T[x].t!=T[y].t)
    {
        if(T[T[x].t].d>=T[T[y].t].d)
        {
            T2.add(1,T[T[x].t].b,T[x].b,1);
            x=T[T[x].t].f;
        }
        else
        {
            T2.add(1,T[T[y].t].b,T[y].b,1);
            y=T[T[y].t].f;
        }
    }
    if(T[x].d<T[y].d) T2.add(1,T[x].b+1,T[y].b,1);
    else T2.add(1,T[y].b+1,T[x].b,1);
}
int query(int x,int y)
{
    int s=0;
    while(T[x].t!=T[y].t)
    {
        if(T[T[x].t].d>=T[T[y].t].d)
        {
            s=(s+T2.sum(1,T[T[x].t].b,T[x].b));
            x=T[T[x].t].f;
        }
        else
        {
            s=(s+T2.sum(1,T[T[y].t].b,T[y].b));
            y=T[T[y].t].f;
        }
    }
    if(T[x].d<T[y].d) s=(s+T2.sum(1,T[x].b+1,T[y].b));
    else s=(s+T2.sum(1,T[y].b+1,T[x].b));
    return s;
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
    T2.build(1,1,n);
    for(int i=1;i<=m;++i)
    {
        char z[10];
        scanf("%s",z);
        if(z[0]=='P')
        {
            int x,y;
            scanf("%d%d",&x,&y);
            change(x,y);
        }
        else if(z[0]=='Q')
        {
            int x,y;
            scanf("%d%d",&x,&y);
            printf("%d\n",query(x,y));
        }
    }
    return 0;
}