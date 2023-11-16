#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=201;
const ll P=1e9+7;
int n,b[N],c[N],b2[N],c2[N];
ll f[N][N*N];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&c[i]);
    }
    for(int i=2;i<=n;++i)
    {
        scanf("%d",&b[i]);
    }
    scanf("%*d%d",&b[1]);
    for(int i=2;i<=n;++i) b[i]+=b[i-1];
    for(int i=1;i<=n;++i)
    {
        b2[i]=b2[i-1]+b[i];
        c2[i]=c2[i-1]+c[i];
    }
    f[0][0]=1;
    for(int i=1;i<=n;++i)
    {
        for(int j=max(b2[i-1],0);j<=c2[i-1];++j)
        {
            for(int k=0;k<=c[i];++k) f[i][j+k]=(f[i][j+k]+f[i-1][j])%P;
        }
    }
    ll s=0;
    for(int i=max(b2[n],0);i<=c2[n];++i) s=(s+f[n][i])%P;
    printf("%lld",s);
    return 0;
}