#include<cstdio>
#include<algorithm>
using namespace std;
const int N=500001;
int n,m,p=1,t[N];
struct tree
{
    int f,l,d,t,z,h,w;
}T[N];
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
    T[x].l=1;
    T[x].d=T[T[x].f].d+1;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==T[x].f) continue;
        T[a[i].m].f=x;
        T[a[i].m].h=T[x].h+a[i].w;
        dfs1(a[i].m);
        if(T[a[i].m].l+1>T[x].l)
        {
            T[x].l=T[a[i].m].l+1;
            T[x].z=a[i].m;
        }
    }
}
void dfs2(int x,int k)
{
    T[x].t=k;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==T[x].f) continue;
        if(a[i].m==T[x].z) dfs2(a[i].m,k);
        else dfs2(a[i].m,a[i].m);
    }
}
int LCA(int x,int y)
{
    while(T[x].t!=T[y].t)
    {
        if(T[T[x].t].d>=T[T[y].t].d) x=T[T[x].t].f;
        else y=T[T[y].t].f;
    }
    if(T[x].d<T[y].d) return x;
    else return y;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n-1;++i)
    {
        int x,y,w;
        scanf("%d%d%d",&x,&y,&w);
        road(x,y,w);
        road(y,x,w);
    }
    dfs1(1);
    dfs2(1,1);
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        printf("%d\n",T[x].h+T[y].h-T[LCA(x,y)].h*2);
    }
    return 0;
}