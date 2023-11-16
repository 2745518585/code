#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,p=1,t[N];
ll s,*f[N],*g[N],oo[N<<3],*o=oo;
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
    int f,d,md,z;
}T[N];
void dfs0(int x)
{
    T[x].d=T[T[x].f].d+1;
    T[x].md=1;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==T[x].f) continue;
        T[a[i].m].f=x;
        dfs0(a[i].m);
        if(T[a[i].m].md>T[T[x].z].md) T[x].z=a[i].m;
    }
    T[x].md=T[T[x].z].md+1;
}
void dfs(int x)
{
    if(f[x]==NULL)
    {
        f[x]=o;
        o+=T[x].md*2;
        g[x]=o;
        o+=T[x].md*2;
    }
    if(T[x].z!=0)
    {
        f[T[x].z]=f[x]+1;
        g[T[x].z]=g[x]-1;
        dfs(T[x].z);
    }
    f[x][0]=1;
    s+=g[x][0];
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==T[x].f||a[i].m==T[x].z) continue;
        dfs(a[i].m);
        for(int j=0;j<=T[a[i].m].md-1;++j)
        {
            if(j>=1) s+=f[x][j-1]*g[a[i].m][j];
            s+=g[x][j+1]*f[a[i].m][j];
        }
        for(int j=0;j<=T[a[i].m].md-1;++j)
        {
            g[x][j+1]+=f[x][j+1]*f[a[i].m][j];
            if(j>=1) g[x][j-1]+=g[a[i].m][j];
            f[x][j+1]+=f[a[i].m][j];
        }
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n-1;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        road(x,y);
        road(y,x);
    }
    dfs0(1);
    dfs(1);
    printf("%lld",s);
    return 0;
}