#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=1000001;
int n,m,tot,fa[N],c[N];
vector<int> a[N];
struct road
{
    int x,y,w;
}b[N];
bool cmp(road a,road b)
{
    return a.w<b.w;
}
int find(int x)
{
    if(fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}
struct tree
{
    int f,s,d,t,z,b;
}T[N];
namespace tc
{
    void dfs1(int x)
    {
        T[x].s=1;
        T[x].d=T[T[x].f].d+1;
        for(auto i:a[x])
        {
            if(i==T[x].f) continue;
            T[i].f=x;
            dfs1(i);
            T[x].s+=T[i].s;
            if(T[i].s>T[T[x].z].s) T[x].z=i;
        }
    }
    void dfs2(int x,int k)
    {
        if(x<=n) T[x].b=++tot;
        T[x].t=k;
        if(T[x].z) dfs2(T[x].z,k);
        for(auto i:a[x])
        {
            if(i==T[x].f||i==T[x].z) continue;
            dfs2(i,i);
        }
    }
    int LCA(int x,int y)
    {
        while(T[x].t!=T[y].t)
        {
            if(T[T[x].t].d>T[T[y].t].d) x=T[T[x].t].f;
            else y=T[T[y].t].f;
        }
        if(T[x].d<T[y].d) return x;
        else return y;
    }
}
namespace sgt
{
    struct tree
    {
        int l,r,s1,s2,t1,t2,k;
    }T[N<<2];
    void pushup(int x)
    {
        T[x].s1=min(T[x<<1].s1,T[x<<1|1].s1);
        T[x].s2=max(T[x<<1].s2,T[x<<1|1].s2);
        T[x].t1=min(T[x<<1].t1,T[x<<1|1].t1);
        T[x].t2=max(T[x<<1].t2,T[x<<1|1].t2);
    }
    void make_tag(int x,int k)
    {
        if(k==1) T[x].s1=T[x].t1,T[x].s2=T[x].t2;
        else T[x].s1=n+1,T[x].s2=0;
        T[x].k=k;
    }
    void pushdown(int x)
    {
        if(T[x].k==0) return;
        make_tag(x<<1,T[x].k);
        make_tag(x<<1|1,T[x].k);
        T[x].k=0;
    }
    void build(int x,int l,int r)
    {
        T[x].l=l;
        T[x].r=r;
        if(l==r)
        {
            T[x].s1=n+1;
            T[x].s2=0;
            T[x].t1=T[x].t2=::T[l].b;
            return;
        }
        int z=l+r>>1;
        build(x<<1,l,z);
        build(x<<1|1,z+1,r);
        pushup(x);
    }
    void add(int x,int l,int r,int k)
    {
        if(T[x].l>=l&&T[x].r<=r)
        {
            make_tag(x,k);
            return;
        }
        pushdown(x);
        int z=T[x].l+T[x].r>>1;
        if(l<=z) add(x<<1,l,r,k);
        if(r>z) add(x<<1|1,l,r,k);
        pushup(x);
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n-1;++i)
    {
        scanf("%d%d%d",&b[i].x,&b[i].y,&b[i].w);
    }
    sort(b+1,b+n,cmp);
    for(int i=1;i<=n*2-1;++i) fa[i]=i;
    for(int i=1;i<=n-1;++i)
    {
        a[n+i].push_back(find(b[i].x));
        a[n+i].push_back(find(b[i].y));
        fa[find(b[i].x)]=n+i;
        fa[find(b[i].y)]=n+i;
    }
    tc::dfs1(find(1));
    tc::dfs2(find(1),find(1));
    sgt::build(1,1,n);
    for(int i=1;i<=n;++i) c[T[i].b]=i;
    for(int i=1;i<=m;++i)
    {
        int z;
        scanf("%d",&z);
        if(z==1)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            sgt::add(1,x,y,1);
        }
        else if(z==2)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            sgt::add(1,x,y,2);
        }
        else if(z==3)
        {
            int x;
            scanf("%d",&x);
            int z1=sgt::T[1].s1,z2=sgt::T[1].s2;
            if(z1==n+1)
            {
                printf("-1\n");
                continue;
            }
            int z=tc::LCA(x,tc::LCA(c[z1],c[z2]));
            // printf("%d %d %d %d\n",x,z1,z2,z);
            if(z<=n)
            {
                printf("-1\n");
                continue;
            }
            printf("%d\n",b[z-n].w);
        }
    }
    return 0;
}