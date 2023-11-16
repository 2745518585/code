#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=20001,M=201,K=21;
const ll P=1e9+7;
int n,k,d;
ll f[K][N],C[N][M];
int main()
{
    scanf("%d%d%d",&n,&k,&d);
    k/=2;
    ++d;
    C[0][0]=1;
    for(int i=1;i<=n;++i)
    {
        C[i][0]=1;
        for(int j=1;j<=k*2;++j)
        {
            C[i][j]=(C[i-1][j-1]+C[i-1][j])%P;
        }
    }
    f[0][0]=1;
    for(int i=1;i<=15;++i)
    {
        for(int j=0;j<=n;++j)
        {
            for(int l=0;(1<<(i-1))*l*d<=n&&l*d<=k;++l)
            {
                f[i][j+(1<<(i-1))*l*d]=(f[i][j+(1<<(i-1))*l*d]+f[i-1][j]*C[k][l*d])%P;
            }
        }
    }
    ll s=0;
    for(int i=0;i<=n-k;++i)
    {
        s=(s+f[15][i]*C[n-i-k][k]%P)%P;
    }
    printf("%lld",((C[n][k*2]-s)%P+P)%P);
    return 0;
}