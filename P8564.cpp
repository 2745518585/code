#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=6001;
int n,m,p=1,t[N],b[N],h[N];
ll f[N][N],g[N];
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
void dfs(int x,int fa)
{
    h[x]=1;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa) continue;
        dfs(a[i].m,x);
        for(int j=1;j<=h[x]+h[a[i].m];++j) g[j]=f[x][j],f[x][j]=1e9;
        for(int j=1;j<=h[x];++j)
        {
            for(int k=1;k<=h[a[i].m];++k)
            {
                f[x][j+k]=min(f[x][j+k],g[j]+f[a[i].m][k]);
            }
        }
        h[x]+=h[a[i].m];
    }
    for(int i=1;i<=h[x];++i)
    {
        f[x][1]=min(f[x][1],f[x][i]+b[i-1]);
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n-1;++i)
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
    dfs(1,0);
    printf("%lld",f[1][1]);
    return 0;
}