#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=5001;
const ll P=998244353;
int n,k,a[N];
ll jc[N],C[N][N],g[N];
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    jc[0]=1;
    for(int i=1;i<=n;++i) jc[i]=jc[i-1]*i%P;
    C[0][0]=1;
    for(int i=1;i<=n;++i)
    {
        C[i][0]=1;
        for(int j=1;j<=i;++j)
        {
            C[i][j]=(C[i-1][j-1]+C[i-1][j])%P;
        }
    }
    sort(a+1,a+n+1);
    for(int i=1;i<=n;++i)
    {
        ll w=0;
        for(int j=1;j<=k;++j) w=(w+C[n-j][i-1])%P;
        w=w*jc[i]%P*jc[n-i]%P*(i-1)%P;
        g[i]=w;
    }
    ll s=0;
    for(int i=2;i<=n;++i) s=(s+(g[i]-g[i-1])*a[i]%P)%P;
    printf("%lld",(s%P+P)%P);
    return 0;
}