#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=200001;
int n,m,p=1,t[N];
ll f[N],g[N],b[N];
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
int LCA2(int x,int y)
{
    int p=x;
    while(T[x].t!=T[y].t)
    {
        if(T[T[x].t].d>=T[T[y].t].d) x=T[p=T[x].t].f;
        else y=T[p=T[y].t].f;
    }
    if(x==y) return p;
    if(T[x].d>T[y].d) swap(x,y);
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==T[x].f) continue;
        if(T[a[i].m].t==T[y].t) return a[i].m;
    }
}
void dfs3(int x)
{
    b[x]=1;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==T[x].f) continue;
        dfs3(a[i].m);
        b[x]+=b[a[i].m];
        f[x]+=f[a[i].m]+b[a[i].m];
    }
}
void dfs4(int x)
{
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==T[x].f) continue;
        g[a[i].m]+=(f[x]-(f[a[i].m]+b[a[i].m]))+g[x]+(n-b[a[i].m]);
        dfs4(a[i].m);
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
        road(y,x);
    }
    dfs1(1);
    dfs2(1,1);
    dfs3(1);
    dfs4(1);
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        int z=LCA(x,y),k=T[x].d+T[y].d-T[z].d*2;
        if(x==z||y==z)
        {
            int z2=LCA2(x,y);
            if(x==z) printf("%.8lf\n",((double)g[z2]/(n-b[z2])+(double)f[y]/b[y])+k);
            else printf("%.8lf\n",((double)f[x]/b[x]+(double)g[z2]/(n-b[z2]))+k);
        }
        else printf("%.8lf\n",((double)f[x]/b[x]+(double)f[y]/b[y])+k+1);
    }
    return 0;
}