#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=5001;
const ll P=1e9+7;
int n,k;
ll pow2[N],f[N],g[N][N];
int main()
{
    scanf("%d%d",&n,&k);
    pow2[0]=1;
    for(int i=1;i<=n;++i) pow2[i]=pow2[i-1]*2%P;
    g[0][n]=1;
    for(int i=1;i<=k-1;++i)
    {
        for(int j=n-i+1;j>=1;--j)
        {
            g[i][j]=(g[i][j+1]+g[i-1][j])%P;
        }
    }
    ll s=0;
    for(int i=1;i<=n-k+1;++i) s=(s+g[k-1][i])%P;
    if(n-k-1>=0) s=(s*pow2[n-k-1])%P;
    printf("%lld",s);
    return 0;
}