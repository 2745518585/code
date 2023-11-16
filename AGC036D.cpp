#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=2001;
int n;
ll a[N][N],f[N][N],g1[N][N],g2[N][N];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(i==j) continue;
            scanf("%lld",&a[i][j]);
            if(i<j) g1[i][j]=a[i][j];
            else g2[i][j]=a[i][j];
        }
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            g1[i][j]=g1[i][j-1]+g1[i-1][j]+g1[i][j]-g1[i-1][j-1];
            g2[i][j]=g2[i][j-1]+g2[i-1][j]+g2[i][j]-g2[i-1][j-1];
        }
    }
    for(int i=0;i<=n+1;++i)
    {
        for(int j=0;j<=n+1;++j) f[i][j]=1e18;
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=i;j<=n;++j)
        {
            if(i==1) f[i][j]=g1[j][j]-g1[i-1][j]-g1[j][i-1]+g1[i-1][i-1];
            for(int k=1;k<=i-1;++k)
            {
                f[i][j]=min(f[i][j],f[k][i-1]+(g1[j][j]-g1[i-1][j]-g1[j][i-1]+g1[i-1][i-1])+(g2[j][k-1]-g2[i-1][k-1]));
            }
        }
    }
    ll s=1e18;
    for(int i=1;i<=n;++i)
    {
        s=min(s,f[i][n]);
    }
    printf("%lld",s);
    return 0;
}