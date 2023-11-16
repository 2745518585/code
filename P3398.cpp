#include<cstdio>
#include<algorithm>
using namespace std;
const int N=500001;
int n,m,p=1,t[N];
struct tree
{
    int f,s,d,t,z;
}T[N];
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
    T[x].t=k;
    if(T[x].z!=0) dfs2(T[x].z,k);
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==T[x].f||a[i].m==T[x].z) continue;
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
        int x,y;
        scanf("%d%d",&x,&y);
        road(x,y);
        road(y,x);
    }
    dfs1(1);
    dfs2(1,1);
    for(int i=1;i<=m;++i)
    {
        int x1,y1,x2,y2;
        scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
        int k1=LCA(x1,y1),k2=LCA(x2,y2);
        if(k1==k2) printf("Y\n");
        else if(T[k1].d<T[k2].d)
        {
            if(LCA(k1,k2)==k1&&(LCA(k2,x1)==k2||LCA(k2,y1)==k2))
            {
                printf("Y\n");
            }
            else printf("N\n");
        }
        else
        {
            if(LCA(k1,k2)==k2&&(LCA(k1,x2)==k1||LCA(k1,y2)==k1))
            {
                printf("Y\n");
            }
            else printf("N\n");
        }
    }
    return 0;
}