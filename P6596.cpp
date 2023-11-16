#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=101;
const ll P=1e9+7; 
int n,m;
ll f[N][N],g[N][N][N],h[N][N],d[N],powb[N][N*N],C[N][N];
int main()
{
    scanf("%d%d",&n,&m);
    m=min(m+1,n);
    for(int i=1;i<=n;++i)
    {
        powb[i][0]=1;
        for(int j=1;j<=n*n;++j) powb[i][j]=powb[i][j-1]*i%P;
    }
    C[0][0]=1;
    for(int i=1;i<=n;++i)
    {
        C[i][0]=1;
        for(int j=1;j<=i;++j)
        {
            C[i][j]=(C[i-1][j-1]+C[i-1][j])%P;
        }
    }
    for(int i=1;i<=n;++i)
    {
        d[i]=powb[2][i*(i-1)/2];
        for(int j=1;j<=i-1;++j)
        {
            d[i]=(d[i]-d[j]*powb[2][(i-j)*(i-j-1)/2]%P*C[i-1][j-1]%P)%P;
        }
    }
    for(int i=1;i<=n;++i) h[1][i]=d[i]*i%P;
    for(int i=2;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            for(int k=1;k<=j-1;++k)
            {
                h[i][j]=(h[i][j]+h[1][k]*h[i-1][j-k]%P*C[j-1][k-1]%P)%P;
            }
        }
    }
    for(int i=1;i<=n;++i)
    {
        f[1][i]=d[i];
        for(int j=1;j<=i-1;++j)
        {
            for(int k=1;k<=i-j;++k)
            {
                f[1][i]=(f[1][i]-f[1][j]*h[k][i-j]%P*powb[j][k]%P*C[i-1][j-1]%P)%P;
            }
        }
    }
    for(int i=1;i<=n;++i) g[1][i][1]=f[1][i]*i%P;
    for(int i=2;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            for(int k=1;k<=j-1;++k)
            {
                for(int l=1;l<=j-k;++l)
                {
                    f[i][j]=(f[i][j]+f[1][k]*powb[k][l]%P*g[i-1][j-k][l]%P*C[j-1][k-1]%P)%P;
                }
            }
        }
        for(int j=1;j<=n;++j) g[i][j][1]=f[i][j]*j%P;
        for(int j=1;j<=i-1;++j)
        {
            for(int k=1;k<=n;++k)
            {
                for(int l=1;l<=k-1;++l)
                {
                    for(int o=2;o<=n;++o)
                    {
                        g[i][k][o]=(g[i][k][o]+g[j][l][1]*g[i-j][k-l][o-1]%P*C[k-1][l-1]%P)%P;
                    }
                }
            }
        }
    }
    ll s=0;
    for(int i=0;i<=m;++i) s=(s+f[i][n])%P;
    printf("%lld",(s%P+P)%P);
    return 0;
}