#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=5001;
int n,a[N],b[N][N];
ll f[N][N],g[N][N];
void solve()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    for(int i=0;i<=n+1;++i)
    {
        for(int j=0;j<=n+1;++j) b[i][j]=0;
    }
    for(int i=1;i<=n;++i)
    {
        b[i][i]=a[i];
        for(int j=i+1;j<=n;++j)
        {
            b[i][j]=max(b[i][j-1],a[j]);
        }
    }
    for(int i=0;i<=n+1;++i)
    {
        for(int j=0;j<=n+1;++j) f[i][j]=g[i][j]=1e18;
    }
    for(int i=1;i<=n+1;++i) g[i][i-1]=0,f[i][i]=0;
    for(int p=2;p<=n;++p)
    {
        for(int i=1,j=i+p-1;j<=n;++i,++j)
        {
            for(int k=i+1;k<=j;++k)
            {
                f[i][j]=min(f[i][j],g[i+1][k-1]+f[k][j]+(b[i][j]-a[i])+(b[i][j]-b[k][j]));
                g[i][j]=min(g[i][j],g[i][k-1]+g[k][j]);
            }
            g[i][j]=min(g[i][j],f[i][j]);
        }
    }
    printf("%lld\n",g[1][n]);
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--) solve();
    return 0;
}