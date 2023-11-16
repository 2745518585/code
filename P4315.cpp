#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,q,p=1,t[N],b[N];
struct tree
{
    int f,s,d,t,z,b,bm;
}T[N];
struct Segment_tree
{
    struct tree
    {
        int l,r;
        ll s,k1,k2;
    };
    tree T[N<<2];
    int a[N];
    void pushup(int x)
    {
        T[x].s=max(T[x<<1].s,T[x<<1|1].s);
    }
    void pushdown(int x)
    {
        if(T[x].k1!=0)
        {
            T[x<<1].k1=T[x].k1;
            T[x<<1].k2=0;
            T[x<<1].s=T[x].k1;
            T[x<<1|1].k1=T[x].k1;
            T[x<<1|1].k2=0;
            T[x<<1|1].s=T[x].k1;
            T[x].k1=0;
        }
        if(T[x].k2!=0)
        {
            T[x<<1].k2+=T[x].k2;
            T[x<<1].s+=T[x].k2;
            T[x<<1|1].k2+=T[x].k2;
            T[x<<1|1].s+=T[x].k2;
            T[x].k2=0;
        }
    }
    void build(int x,int l,int r)
    {
        T[x].l=l;
        T[x].r=r;
        T[x].k1=T[x].k2=0;
        if(l==r)
        {
            T[x].s=a[l];
            return;
        }
        int z=l+r>>1;
        build(x<<1,l,z);
        build(x<<1|1,z+1,r);
        pushup(x);
    }
    void change(int x,int l,int r,int k)
    {
        if(T[x].l>=l&&T[x].r<=r)
        {
            T[x].k1=k;
            T[x].k2=0;
            T[x].s=k;
            return;
        }
        pushdown(x);
        int z=T[x].l+T[x].r>>1;
        if(l<=z) change(x<<1,l,r,k);
        if(r>z) change(x<<1|1,l,r,k);
        pushup(x);
    }
    void add(int x,int l,int r,int k)
    {
        if(T[x].l>=l&&T[x].r<=r)
        {
            T[x].k2+=k;
            T[x].s+=k;
            return;
        }
        pushdown(x);
        int z=T[x].l+T[x].r>>1;
        if(l<=z) add(x<<1,l,r,k);
        if(r>z) add(x<<1|1,l,r,k);
        pushup(x);
    }
    ll sum(int x,int l,int r)
    {
        if(T[x].l>=l&&T[x].r<=r)
        {
            return T[x].s;
        }
        pushdown(x);
        int z=T[x].l+T[x].r>>1;
        ll s=-1e18;
        if(l<=z) s=max(s,sum(x<<1,l,r));
        if(r>z) s=max(s,sum(x<<1|1,l,r));
        return s;
    }
}T2;
struct road
{
    int m,q,w;
}a[N<<1];
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
        b[i/2]=a[i].m;
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
            T2.change(1,T[T[x].t].b,T[x].b,k);
            x=T[T[x].t].f;
        }
        else
        {
            T2.change(1,T[T[y].t].b,T[y].b,k);
            y=T[T[y].t].f;
        }
    }
    if(T[x].d<T[y].d) T2.change(1,T[x].b+1,T[y].b,k);
    else T2.change(1,T[y].b+1,T[x].b,k);
}
void add(int x,int y,int k)
{
    while(T[x].t!=T[y].t)
    {
        if(T[T[x].t].d>=T[T[y].t].d)
        {
            T2.add(1,T[T[x].t].b,T[x].b,k);
            x=T[T[x].t].f;
        }
        else
        {
            T2.add(1,T[T[y].t].b,T[y].b,k);
            y=T[T[y].t].f;
        }
    }
    if(T[x].d<T[y].d) T2.add(1,T[x].b+1,T[y].b,k);
    else T2.add(1,T[y].b+1,T[x].b,k);
}
int query(int x,int y)
{
    ll s=-1e18;
    while(T[x].t!=T[y].t)
    {
        if(T[T[x].t].d>=T[T[y].t].d)
        {
            s=max(s,T2.sum(1,T[T[x].t].b,T[x].b));
            x=T[T[x].t].f;
        }
        else
        {
            s=max(s,T2.sum(1,T[T[y].t].b,T[y].b));
            y=T[T[y].t].f;
        }
    }
    if(T[x].d<T[y].d) s=max(s,T2.sum(1,T[x].b+1,T[y].b));
    else s=max(s,T2.sum(1,T[y].b+1,T[x].b));
    return s;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n-1;++i)
    {
        int x,y,w;
        scanf("%d%d%d",&x,&y,&w);
        road(x,y,w);
        road(y,x,w);
    }
    dfs1(1);
    dfs2(1,1);
    for(int i=1;i<=n-1;++i)
    {
        T2.a[T[b[i]].b]=a[i*2].w;
    }
    T2.build(1,1,n);
    while(true)
    {
        char z[10];
        scanf("%s",z);
        if(z[0]=='C'&&z[1]=='h')
        {
            int x,k;
            scanf("%d%d",&x,&k);
            T2.change(1,T[b[x]].b,T[b[x]].b,k);
        }
        else if(z[0]=='C'&&z[1]=='o')
        {
            int x,y,k;
            scanf("%d%d%d",&x,&y,&k);
            change(x,y,k);
        }
        else if(z[0]=='A')
        {
            int x,y,k;
            scanf("%d%d%d",&x,&y,&k);
            add(x,y,k);
        }
        else if(z[0]=='M')
        {
            int x,y;
            scanf("%d%d",&x,&y);
            printf("%d\n",query(x,y));
        }
        else if(z[0]=='S') break;
        // for(int i=1;i<=n;++i)
        // {
        //     printf("%d ",T2.sum(1,T[i].b,T[i].b));
        // }
        // printf("\n");
    }
    return 0;
}