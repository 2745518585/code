#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=2101;
const ll P=998244353;
int n,m;
ll p[N<<1],pw[N<<1],a[N][N<<1],b[N][N<<1],c[N][N<<1],d[N][N<<1],c2[N][N<<1],d2[N][N<<1];
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
    ll w=0;
    for(int i=0;i<=m-1;++i)
    {
        scanf("%lld",&p[i]);
        w=(w+p[i])%P;
    }
    for(int i=0;i<=m-1;++i) p[i]=p[i]*inv(w)%P;
    pw[0]=1;
    for(int i=1;i<=n+m-1;++i) pw[i]=pw[i-1]*2%P;
    for(int i=1;i<=n;++i)
    {
        for(int j=0;j<=n+m-1;++j)
        {
            a[i][j]=(p[j]+a[i-1][j-1]*a[i][j-1]%P)%P;
        }
        for(int j=0;j<=n+m-1;++j)
        {
            b[i][j]=(a[i][j-1]*b[i-1][j-1]%P+a[i-1][j-1]*b[i][j-1]%P+a[i-1][j-1]*a[i][j-1]%P*pw[j]%P)%P;
        }
        for(int j=0;j<=n+m-1;++j)
        {
            c[i][j]=((1-a[i-1][j])*b[i][j]%P+a[i][j]*(c2[i-1][j-1]+d2[i-1][j+1]%P)%P);
        }
        for(int j=n+m-1;j>=0;--j)
        {
            d[i][j]=(c2[i-1][j-1]+(a[i-1][j]*(d[i][j+1]+pw[j+1])%P+b[i-1][j])+d2[i-1][j+1]%P)%P;
        }
        for(int j=0;j<=n+m-1;++j) c2[i][j]=(c2[i][j-1]+c[i][j])%P;
        for(int j=n+m-1;j>=0;--j) d2[i][j]=(d2[i][j+1]+p[j]*d[i][j]%P)%P;
    }
    // for(int i=1;i<=n;++i)
    // {
    //     for(int j=0;j<=n+m-1;++j)
    //     {
    //         printf("%d %d: %lld %lld %lld %lld\n",i,j,(a[i][j]%P+P)%P,(b[i][j]%P+P)%P,(c[i][j]%P+P)%P,(d[i][j]%P+P)%P);
    //     }
    // }
    ll s=0;
    for(int i=0;i<=n+m-1;++i)
    {
        s=(s+c[n][i]%P)%P;
    }
    printf("%lld",(s%P+P)%P);
    return 0;
}