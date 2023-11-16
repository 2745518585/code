#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=201;
int m,n,k;
ll P,C[N][N],f1[N][N],f2[N][N],g1[N][N][N],g2[N][N][N];
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
    scanf("%d%d%d%lld",&m,&n,&k,&P);
    C[0][0]=1;
    for(int i=1;i<=m+n;++i)
    {
        C[i][0]=1;
        for(int j=1;j<=m+n;++j)
        {
            C[i][j]=(C[i-1][j-1]+C[i-1][j])%P;
        }
    }
    for(int i=1;i<=k;++i)
    {
        for(int j=0;j<=n;++j)
        {
            ll w=qpow(k-i+1,j)*(qpow(i,n-j)-qpow(i-1,n-j))%P;
            g1[i][j][0]=1;
            for(int l=1;l<=m;++l)
            {
                g1[i][j][l]=g1[i][j][l-1]*w%P;
            }
        }
    }
    for(int i=1;i<=k;++i)
    {
        for(int j=0;j<=m;++j)
        {
            ll w=qpow(i,m-j)*(qpow(k-i+1,j)-qpow(k-i,j))%P;
            g2[i][j][0]=1;
            for(int l=1;l<=n;++l)
            {
                g2[i][j][l]=g2[i][j][l-1]*w%P;
            }
        }
    }
    f1[0][0]=1;
    for(int i=1;i<=k;++i)
    {
        for(int j=0;j<=m;++j)
        {
            for(int l=0;l<=n;++l)
            {
                f2[j][l]=0;
                for(int p=0;p<=j;++p)
                {
                    f2[j][l]=(f2[j][l]+C[m-(j-p)][p]*f1[j-p][l]%P*g1[i][l][p]%P)%P;
                }
            }
        }
        for(int j=0;j<=m;++j)
        {
            for(int l=0;l<=n;++l)
            {
                f1[j][l]=0;
                for(int p=0;p<=l;++p)
                {
                    f1[j][l]=(f1[j][l]+C[n-(l-p)][p]*f2[j][l-p]%P*g2[i][j][p]%P)%P;
                }
            }
        }
    }
    printf("%lld",(f1[m][n]%P+P)%P);
    return 0;
}