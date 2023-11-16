#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=51;
const ll P=998244353;
int n,m;
ll f[N][N][N*N],C[N*N][N*N];
void exgcd(ll a,ll b,ll &x,ll &y)
{
    if(b==0) x=1,y=0;
    else exgcd(b,a%b,y,x),y-=a/b*x;
}
ll inv(ll a)
{
    a=(a%P+P)%P;
    ll x,y;
    exgcd(a,P,x,y);
    return (x%P+P)%P;
}
int main()
{
    scanf("%d%d",&n,&m);
    C[0][0]=1;
    for(int i=1;i<=n*n;++i)
    {
        C[i][0]=1;
        for(int j=1;j<=i;++j)
        {
            C[i][j]=(C[i-1][j-1]+C[i-1][j])%P;
        }
    }
    f[0][0][0]=1;
    for(int i=0;i<=n;++i)
    {
        for(int j=0;i+j<=n;++j)
        {
            for(int k=0;k<=n*n;++k)
            {
                for(int l=0;l<=i;++l)
                {
                    f[i+1][j][k+j+l]=(f[i+1][j][k+j+l]+f[i][j][k]*C[i][l])%P;
                }
                for(int l=0;l<=j;++l)
                {
                    f[i][j+1][k+l]=(f[i][j+1][k+l]+f[i][j][k]*C[j][l])%P;
                }
            }
        }
    }
    ll s=0;
    for(int i=0;i<=n-1;++i)
    {
        s=(s+f[i][n-i][m])%P;
    }
    printf("%lld",s);
    return 0;
}