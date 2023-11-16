#include<cstdio>
#include<algorithm>
#include<ctime>
using namespace std;
typedef long long ll;
const int N=3000001;
int n,m,tot,p=1,t[N],rt[N],b[N];
ll c[N];
namespace sgt
{
    int tot;
    struct tree
    {
        int l,r;
        ll s;
    }T[N<<4];
    void pushup(int x)
    {
        T[x].s=T[T[x].l].s^T[T[x].r].s;
    }
    void add(int &x,int ls,int rs,int q,ll k)
    {
        T[++tot]=T[x];
        x=tot;
        if(ls==rs)
        {
            T[x].s^=k;
            return;
        }
        int z=ls+rs>>1;
        if(q<=z) add(T[x].l,ls,z,q,k);
        else add(T[x].r,z+1,rs,q,k);
        pushup(x);
    }
    ll sum(int x,int ls,int rs,int l,int r)
    {
        if(x==0||l>rs||r<ls) return 0;
        if(ls>=l&&rs<=r)
        {
            return T[x].s;
        }
        int z=ls+rs>>1;
        ll s=0;
        if(l<=z) s^=sum(T[x].l,ls,z,l,r);
        if(r>z) s^=sum(T[x].r,z+1,rs,l,r);
        return s;
    }
    int find(int x1,int x2,int x3,int x4,int ls,int rs,int l,int r)
    {
        if(ls==rs)
        {
            if((T[x1].s^T[x2].s^T[x3].s^T[x4].s)==0) return -1;
            return ls;
        }
        int z=ls+rs>>1;
        if(l<=z&&(r<=z||(sum(T[x1].l,ls,z,l,r)^sum(T[x2].l,ls,z,l,r)^sum(T[x3].l,ls,z,l,r)^sum(T[x4].l,ls,z,l,r))!=0)) return find(T[x1].l,T[x2].l,T[x3].l,T[x4].l,ls,z,l,r);
        else return find(T[x1].r,T[x2].r,T[x3].r,T[x4].r,z+1,rs,l,r);
    }
}
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
struct tree
{
    int f,s,d,t,z;
}T[N];
void dfs1(int x)
{
    T[x].s=1;
    T[x].d=T[T[x].f].d+1;
    rt[x]=rt[T[x].f];
    sgt::add(rt[x],1,n,b[x],c[b[x]]);
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
    if(T[x].z) dfs2(T[x].z,k);
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==T[x].f||a[i].m==T[x].z) continue;
        dfs2(a[i].m,a[i].m);
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
int main()
{
    scanf("%d%d",&n,&m);
    srand(n*m*time(NULL));
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&b[i]);
    }
    for(int i=1;i<=n;++i) c[i]=((ll)rand()<<48)+((ll)rand()<<32)+((ll)rand()<<16)+rand();
    for(int i=1;i<=n-1;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        road(x,y);
        road(y,x);
    }
    dfs1(1);
    dfs2(1,1);
    for(int i=1;i<=m;++i)
    {
        int x,y,l,r;
        scanf("%d%d%d%d",&x,&y,&l,&r);
        int z=LCA(x,y);
        printf("%d\n",sgt::find(rt[x],rt[y],rt[z],rt[T[z].f],1,n,l,r));
    }
    return 0;
}