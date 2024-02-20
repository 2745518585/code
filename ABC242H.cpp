#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1001;
const ll P=998244353;
int n,m,g[N][N];
ll f[N][N];
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
    x=(x%P+P)%P;
    return x;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        ++g[l][r];
    }
    for(int i=n;i>=1;--i)
    {
        for(int j=1;j<=n;++j) g[i][j]+=g[i+1][j];
    }
    for(int i=n;i>=1;--i)
    {
        for(int j=1;j<=n;++j) g[i][j]+=g[i][j-1];
    }
    f[0][0]=1;
    for(int i=1;i<=n+1;++i)
    {
        for(int j=0;j<=m;++j)
        {
            for(int k=0;k<=i-1;++k)
            {
                if(j>=g[k+1][i-1]) f[i][j]=(f[i][j]-f[k][j-g[k+1][i-1]])%P;
            }
        }
    }
    ll s=0;
    for(int i=0;i<=m;++i)
    {
        s=(s+f[n+1][i]*m%P*inv(m-i)%P)%P;
    }
    printf("%lld",(s%P+P)%P);
    return 0;
}