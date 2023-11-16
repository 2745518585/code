#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll P=1e9+7;
int n,g[N][4],h[N];
ll f[N];
char a[N];
int main()
{
    scanf("%d%s",&n,a+1);
    bool u=true;
    for(int i=1;i<=n;++i)
    {
        h[i]=h[i-1]^(a[i]-'A'+1);
        if(i>=2&&a[i]!=a[i-1]) u=false;
    }
    if(u)
    {
        printf("1");
        return 0;
    }
    g[n+1][0]=g[n+1][1]=g[n+1][2]=g[n+1][3]=1;
    for(int i=n;i>=1;--i)
    {
        for(int j=1;j<=3;++j)
        {
            if(a[i]-'A'+1==j) g[i][j]=1;
            else g[i][j]=g[i+1][j^(a[i]-'A'+1)]+1;
        }
    }
    f[0]=1;
    for(int i=0;i<=n;++i)
    {
        for(int j=1;j<=3;++j) f[i+g[i+1][j]]=(f[i+g[i+1][j]]+f[i])%P;
    }
    ll s=0;
    for(int i=1;i<=n;++i)
    {
        if(h[i]==h[n]) s=(s+f[i])%P;
    }
    printf("%lld",s);
    return 0;
}