#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=100001;
int n,m,q,p=1,r,t[N],b[N],P;
struct tree
{
    int f,s,d,t,z,b,bm;
}T[N];struct Segment_tree
{
    struct tree
    {
        int l,r;
        ll s;
    };
    tree T[N<<2];
    void pushup(int x)
    {
        T[x].s=T[x<<1].s+T[x<<1|1].s;
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
    ll sum(int x,int l,int r)
    {
        if(T[x].l>=l&&T[x].r<=r)
        {
            return T[x].s;
        }
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
        T[a[i].m].f=x;
        dfs1(a[i].m);
        T[x].s+=T[a[i].m].s;
        if(T[a[i].m].s>T[T[x].z].s) T[x].z=a[i].m;
    }
}
void dfs2(int x,int k)
{
    T[x].b=++q;
    b[q]=x;
    T[x].t=k;
    if(T[x].z!=0) dfs2(T[x].z,k);
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==T[x].z) continue;
        dfs2(a[i].m,a[i].m);
    }
    T[x].bm=q;
}
int query(int x)
{
    while(x!=0)
    {
        if(T2.sum(1,T[T[x].t].b,T[x].b)!=0)
        {
            int l=T[T[x].t].b,r=T[x].b;
            while(l<r)
            {
                int z=l+r+1>>1;
                if(T2.sum(1,z,T[x].b)!=0) l=z;
                else r=z-1;
            }
            return b[l];
        }
        else x=T[T[x].t].f;
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
    }
    dfs1(1);
    dfs2(1,1);
    T2.build(1,1,n);
    T2.change(1,1,1);
    for(int i=1;i<=m;++i)
    {
        char z[10];
        scanf("%s",z);
        if(z[0]=='C')
        {
            int x;
            scanf("%d",&x);
            T2.change(1,T[x].b,1);
        }
        else if(z[0]=='Q')
        {
            int x;
            scanf("%d",&x);
            printf("%d\n",query(x));
        }
    }
    return 0;
}