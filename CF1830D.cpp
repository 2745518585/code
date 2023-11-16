#include<cstdio>
#include<algorithm>
#include<cmath>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000001;
int n;
ll *f[N][2],g[2][N];
vector<int> a[N];
struct tree
{
    int s,z;
}T[N];
void dfs0(int x,int fa)
{
    T[x].s=1;
    T[x].z=0;
    for(auto i:a[x])
    {
        if(i==fa) continue;
        dfs0(i,x);
        T[x].s+=T[i].s;
        if(T[i].s>T[T[x].z].s) T[x].z=i;
    }
}
void dfs(int x,int fa)
{
    int u=1;
    if(T[x].z)
    {
        f[T[x].z][0]=f[x][0]+1;
        f[T[x].z][1]=f[x][1]+1;
        dfs(T[x].z,x);
        int q=min((int)(sqrt(T[T[x].z].s)*3),T[T[x].z].s);
        for(int i=0;i<=1;++i)
        {
            for(int j=1;j<=q;++j)
            {
                f[x][i][1]=min(f[x][i][1],f[T[x].z][i^1][j]+(ll)j*(j+1)/2*((i^1)+1));
            }
        }
        u+=T[T[x].z].s;
    }
    else f[x][0][1]=f[x][1][1]=0;
    for(auto i:a[x])
    {
        if(i==fa||i==T[x].z) continue;
        f[i][0]=new ll[T[i].s+1],f[i][1]=new ll[T[i].s+1];
        for(int j=0;j<=1;++j) for(int k=0;k<=T[i].s;++k) f[i][j][k]=1e18;
        dfs(i,x);
        int q1=min((int)(sqrt(u)*3),u),q2=min((int)(sqrt(T[i].s)*3),T[i].s);
        for(int j=0;j<=1;++j) for(int k=1;k<=q1;++k) g[j][k]=f[x][j][k],f[x][j][k]=1e18;
        for(int j1=0;j1<=1;++j1)
        {
            for(int j2=0;j2<=1;++j2)
            {
                for(int k1=1;k1<=q1;++k1)
                {
                    for(int k2=1;k2<=q2;++k2)
                    {
                        if(j1!=j2) f[x][j1][k1]=min(f[x][j1][k1],g[j1][k1]+f[i][j2][k2]+(ll)k2*(k2+1)/2*(j2+1));
                        else f[x][j1][k1+k2]=min(f[x][j1][k1+k2],g[j1][k1]+f[i][j2][k2]);
                    }
                }
            }
        }
        u+=T[i].s;
    }
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i) a[i].clear();
        for(int i=1;i<=n-1;++i)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            a[x].push_back(y);
            a[y].push_back(x);
        }
        dfs0(1,0);
        f[1][0]=new ll[n+1],f[1][1]=new ll[n+1];
        for(int i=0;i<=1;++i) for(int j=0;j<=n;++j) f[1][i][j]=1e18;
        dfs(1,0);
        ll s=1e18;
        for(int i=0;i<=1;++i)
        {
            for(int j=1;j<=n;++j)
            {
                s=min(s,f[1][i][j]+(ll)j*(j+1)/2*(i+1));
            }
        }
        printf("%lld\n",(ll)n*(n+1)/2*2-s);
    }
    return 0;
}