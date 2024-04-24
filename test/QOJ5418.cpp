#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000001,M=31;
int n,b[N],*g[N];
ll *f[N];
vector<int> a[N];
namespace ST
{
    int a[N][M],lg[N];
    void init()
    {
        for(int i=1;i<=n;++i) a[i][0]=b[i];
        for(int i=1;i<=20;++i)
        {
            for(int j=(1<<i);j<=min((1<<(i+1))-1,n);++j) lg[j]=i;
        }
        for(int i=1;i<=20;++i)
        {
            for(int j=1;j<=n;++j)
            {
                if(j+(1<<i)-1<=n) a[j][i]=min(a[j][i-1],a[j+(1<<(i-1))][i-1]);
            }
        }
    }
    int sum(int x,int y)
    {
        return min(a[x][lg[y-x]],a[y-(1<<lg[y-x])+1][lg[y-x]]);
    }
}
struct tree
{
    int md,z;
}T[N];
void dfs0(int x,int fa)
{
    T[x].md=1;
    T[x].z=0;
    for(auto i:a[x])
    {
        if(i==fa) continue;
        dfs0(i,x);
        T[x].md=max(T[x].md,T[i].md+1);
        if(T[i].md>T[T[x].z].md) T[x].z=i;
    }
}
void dfs(int x,int fa)
{
    if(T[x].z)
    {
        f[T[x].z]=f[x]+1;
        g[T[x].z]=g[x]+1;
        dfs(T[x].z,x);
    }
    for(auto i:a[x])
    {
        if(i==fa||i==T[x].z) continue;
        f[i]=new ll[T[i].md+2];
        g[i]=new int[T[i].md+2];
        for(int j=0;j<=T[i].md+1;++j) f[i][j]=g[i][j]=0;
        dfs(i,x);
        for(int j=0;j<=T[i].md;++j)
        {
            if(g[i][j]<j) f[i][j]=min(f[i][j],(ll)ST::sum(g[i][j]+1,j)),g[i][j]=j;
        }
        for(int j=1;j<=T[i].md+1;++j)
        {
            if(g[x][j]<j) f[x][j]=min(f[x][j],(ll)ST::sum(g[x][j]+1,j)),g[x][j]=j;
            f[x][j]=min(f[x][j]+f[i][j-1],(ll)b[j]);
        }
    }
    f[x][0]=b[0];
    g[x][0]=0;
}
int main()
{
    int TOT;
    scanf("%d",&TOT);
    while(TOT--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i) a[i].clear();
        for(int i=0;i<=n-1;++i)
        {
            scanf("%d",&b[i]);
        }
        for(int i=1;i<=n-1;++i)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            a[x].push_back(y);
            a[y].push_back(x);
        }
        ST::init();
        dfs0(1,0);
        f[1]=new ll[T[1].md+2];
        g[1]=new int[T[1].md+2];
        for(int i=0;i<=T[1].md+1;++i) f[1][i]=g[1][i]=0;
        dfs(1,0);
        for(int i=1;i<=T[1].md+1;++i)
        {
            if(g[1][i]<i) f[1][i]=min(f[1][i],(ll)ST::sum(g[1][i]+1,i)),g[1][i]=i;
        }
        ll s=0;
        for(int i=0;i<=T[1].md;++i) s+=f[1][i];
        printf("%lld\n",s);
    }
    return 0;
}