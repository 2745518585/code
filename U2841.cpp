#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1001;
int n,m;
ll P,f[N],g[N][N],h[N],C[N][N];
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
    scanf("%d%d",&n,&P);
    h[0]=h[1]=h[2]=0;
    h[3]=1;
    for(int i=4;i<=n;++i) h[i]=h[i-1]*(i-1)%P;
    C[0][0]=1;
    for(int i=1;i<=n;++i)
    {
        C[i][0]=1;
        for(int j=1;j<=n;++j)
        {
            C[i][j]=(C[i-1][j-1]+C[i-1][j])%P;
        }
    }
    f[1]=f[2]=1;
    g[0][0]=g[1][1]=1,g[2][1]=2,g[2][2]=1;
    for(int i=3;i<=n;++i)
    {
        for(int j=1;j<=i-1;++j)
        {
            f[i]=(f[i]+g[i-1][j])%P;
        }
        for(int j=3;j<=i-1;++j)
        {
            ll w=0;
            for(int k=1;k<=i-j;++k)
            {
                w=(w+g[i-j][k]*qpow(j,k)%P)%P;
            }
            f[i]=(f[i]+h[j]*C[i-1][j-1]%P*w%P)%P;
        }
        f[i]=(f[i]+h[i])%P;
        for(int j=1;j<=i;++j)
        {
            for(int k=1;k<=i-j+1;++k)
            {
                g[i][j]=(g[i][j]+(g[i-k][j-1]*k%P*C[i-1][k-1]%P*f[k]%P))%P;
            }
        }
    }
    printf("%lld",(f[n]%P+P)%P);
    return 0;
}