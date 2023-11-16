#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=7001;
int n;
ll P,f[N][N<<1];
int main()
{
    scanf("%d%lld",&n,&P);
    n*=3;
    f[0][0+n]=1;
    for(int i=0;i<=n-1;++i)
    {
        for(int j=-i;j<=i;++j)
        {
            f[i+1][j+1+n]=(f[i+1][j+1+n]+f[i][j+n])%P;
            f[i+2][j-1+n]=(f[i+2][j-1+n]+f[i][j+n]*(i+1)%P)%P;
            f[i+3][j+n]=(f[i+3][j+n]+f[i][j+n]*(i+1)%P*(i+2)%P)%P;
        }
    }
    ll s=0;
    for(int i=0;i<=n;++i) s=(s+f[n][i+n])%P;
    printf("%lld",s);
    return 0;
}