#include<cstdio>
#include<algorithm>
using namespace std;
const int N=100001;
int n,m,b[N];
namespace sgt
{
    int tot,rt[N],a1[N],a2[N],t1,t2;
    struct tree
    {
        int l,r,s;
    }T[N<<8];
    void pushup(int x)
    {
        T[x].s=T[T[x].l].s+T[T[x].r].s;
    }
    void modify(int &x,int l,int r,int q,int k)
    {
        if(x==0) x=++tot;
        if(l==r)
        {
            T[x].s+=k;
            return;
        }
        int z=l+r>>1;
        if(q<=z) modify(T[x].l,l,z,q,k);
        else modify(T[x].r,z+1,r,q,k);
        pushup(x);
    }
    void add(int x,int t,int k)
    {
        modify(rt[x],-1,1e8,t,k);
        while(x<=n)
        {
            x+=x&-x;
            modify(rt[x],-1,1e8,t,k);
        }
    }
    int sum(int l,int r,int k)
    {
        if(l==r) return l;
        int z=l+r>>1,s=0;
        for(int i=1;i<=t2;++i) s+=T[T[a2[i]].r].s;
        for(int i=1;i<=t1;++i) s-=T[T[a1[i]].r].s;
        if(k<=s)
        {
            for(int i=1;i<=t2;++i) a2[i]=T[a2[i]].r;
            for(int i=1;i<=t1;++i) a1[i]=T[a1[i]].r;
            return sum(z+1,r,k);
        }
        else
        {
            for(int i=1;i<=t2;++i) a2[i]=T[a2[i]].l;
            for(int i=1;i<=t1;++i) a1[i]=T[a1[i]].l;
            return sum(l,z,k-s);
        }
    }
    void init(int x,int y)
    {
        --x;
        a1[++t1]=rt[x];
        while(x>=1)
        {
            x-=x&-x;
            a1[++t1]=rt[x];
        }
        a2[++t2]=rt[y];
        while(y>=1)
        {
            y-=y&-y;
            a2[++t2]=rt[y];
        }
    }
}
int p=1,t[N],tot;
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
    int f,s,d,t,z,b;
}T[N];
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
    T[x].b=++tot;
    sgt::add(T[x].b,b[x],1);
    T[x].t=k;
    if(T[x].z!=0) dfs2(T[x].z,k);
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==T[x].f||a[i].m==T[x].z) continue;
        dfs2(a[i].m,a[i].m);
    }
}
void query(int x,int y)
{
    while(T[x].t!=T[y].t)
    {
        if(T[T[x].t].d>=T[T[y].t].d)
        {
            sgt::init(T[T[x].t].b,T[x].b);
            x=T[T[x].t].f;
        }
        else
        {
            sgt::init(T[T[y].t].b,T[y].b);
            y=T[T[y].t].f;
        }
    }
    if(T[x].d<T[y].d) sgt::init(T[x].b,T[y].b);
    else sgt::init(T[y].b,T[x].b);
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
    dfs1(1);
    dfs2(1,1);
    for(int i=1;i<=m;++i)
    {
        int z,x,y;
        scanf("%d%d%d",&z,&x,&y);
        if(z==0)
        {
            sgt::add(T[x].b,b[x],-1);
            b[x]=y;
            sgt::add(T[x].b,b[x],1);
        }
        else
        {
            sgt::t1=sgt::t2=0;
            query(x,y);
            int p=sgt::sum(-1,1e8,z);
            if(p==-1)
            {
                printf("invalid request!\n");
                continue;
            }
            printf("%d\n",p);
        }
    }
    return 0;
}