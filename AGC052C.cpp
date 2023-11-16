#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=6001;
const ll P=998244353;
int n;
ll m,C[N][N],f[N][N],g[N];
ll qpow(ll a,ll b)
{
    ll x=1,y=a;
    while(b)
    {
        if(b&1) x=x*y%P;
        y=y*y%P;
        b>>=1;
    }
    return x;
}
int main()
{
    scanf("%d%lld",&n,&m);
    C[0][0]=1;
    for(int i=1;i<=n;++i)
    {
        C[i][0]=1;
        for(int j=1;j<=i;++j)
        {
            C[i][j]=(C[i-1][j-1]+C[i-1][j])%P;
        }
    }
    f[0][0]=1;
    for(int i=0;i<=n;++i) g[i]=1;
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(j-m+1>=0) f[i][j]=(g[j-1]-g[j-m+1])%P;
            else f[i][j]=g[j-1];
        }
        g[0]=0;
        for(int j=1;j<=n;++j) g[j]=(g[j-1]+f[i][j])%P;
    }
    ll s=0;
    for(int i=0;i<=n;++i)
    {
        for(int j=0;j<=n;++j)
        {
            if(n-i>=j+m&&(n-i)%m!=j%m)
            {
                s=(s+f[i][j]*C[n][i]%P)%P;
            }
        }
    }
    s=s*(m-1)%P;
    s=(s+(qpow(m-1,n)+(n%2?-1:1)*(m-1))*qpow(m,P-2)%P)%P;
    printf("%lld\n",((qpow(m-1,n)-s)%P+P)%P);
    return 0;
}