#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=5001;
const ll P=998244353;
int n,m,a[N];
ll f[N][N];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    if(n<=m)
    {
        ll s=1;
        for(int i=1;i<=n;++i)
        {
            if(a[i]==0) s=s*m%P;
        }
        printf("%lld",s);
        return 0;
    }
    f[0][0]=1;
    for(int i=1;i<=n;++i)
    {
        if(a[i]==0)
        {
            for(int j=1;j<=m+1;++j)
            {
                f[i][j]=(f[i-1][j]*j%P+(m-j+1)*f[i-1][j-1]%P)%P;
            }
        }
        else
        {
            for(int j=1;j<=m+1;++j) f[i][j]=f[i-1][j-1];
        }
    }
    ll s=0;
    for(int i=0;i<=m+1;++i) s=(s+f[n][i])%P;
    printf("%lld",s);
    return 0;
}