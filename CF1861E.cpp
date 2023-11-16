#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=5001;
const ll P=998244353;
int n,k;
int f[N][N],g[N][N],f2[N][N],g2[N][N];
int main()
{
    scanf("%d%d",&n,&k);
    g[0][0]=1;
    for(int i=1;i<=n;++i)
    {
        for(int j=0;j<=k-1;++j)
        {
            g[i][j+1]=((ll)g[i][j+1]+(ll)g[i-1][j]*(k-j)%P)%P;
            f[i][j+1]=((ll)f[i][j+1]+(ll)f[i-1][j]*(k-j)%P)%P;
        }
        for(int j=0;j<=k-1;++j)
        {
            g[i][j]=((ll)g[i][j]+g2[i-1][j])%P;
            f[i][j]=((ll)f[i][j]+f2[i-1][j])%P;
        }
        g[i][0]=((ll)g[i][0]+g[i][k])%P;
        f[i][0]=((ll)f[i][0]+f[i][k]+g[i][k])%P;
        f2[i][k]=g2[i][k]=0;
        for(int j=k-1;j>=1;--j)
        {
            f2[i][j]=((ll)f2[i][j+1]+f[i][j])%P;
            g2[i][j]=((ll)g2[i][j+1]+g[i][j])%P;
        }
    }
    ll s=0;
    for(int i=0;i<=k-1;++i)
    {
        s=(s+f[n][i])%P;
    }
    printf("%lld",(s%P+P)%P);
    return 0;
}