#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=200001,M=301;
const ll P=998244353;
int n,k;
ll f[N][M],g[N][M];
char a[N];
ll solve(int x)
{
    for(int i=0;i<=n;++i)
    {
        for(int j=0;j<=k+1;++j) f[i][j]=g[i][j]=0;
    }
    f[1][x*k]=1;
    g[1][x*k]=1;
    for(int i=2;i<=n;++i)
    {
        if(a[i]!='1')
        {
            for(int j=0;j<=k-1;++j)
            {
                f[i][j]=(f[i][j]+f[i-1][j+1])%P;
                g[i][j]=(g[i][j]+g[i-1][j+1])%P;
            }
            f[i][0]=(f[i][0]+f[i-1][0]+g[i-1][0])%P;
            g[i][0]=(g[i][0]+g[i-1][0])%P;
        }
        if(a[i]!='0')
        {
            for(int j=1;j<=k;++j)
            {
                f[i][j]=(f[i][j]+f[i-1][j-1])%P;
                g[i][j]=(g[i][j]+g[i-1][j-1])%P;
            }
            f[i][k]=(f[i][k]+f[i-1][k]+g[i-1][k])%P;
            g[i][k]=(g[i][k]+g[i-1][k])%P;
        }
    }
    ll s=0;
    for(int i=0;i<=k;++i) s=(s+f[n][i])%P;
    return s;
}
int main()
{
    scanf("%d%d%s",&n,&k,a+1);
    ll s=0;
    if(a[1]!='1') s=(s+solve(0))%P;
    if(a[1]!='0') s=(s+solve(1))%P;
    printf("%lld",(s%P+P)%P);
    return 0;
}