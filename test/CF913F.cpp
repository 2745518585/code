#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=5001;
const ll P=998244353;
int n;
ll p,f[N],g[N],h[N][N],pw1[N],pw2[N];
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
    scanf("%d",&n);
    ll pa,pb;
    scanf("%lld%lld",&pa,&pb);
    p=pa*inv(pb)%P;
    pw1[0]=pw2[0]=1;
    for(int i=1;i<=n;++i) pw1[i]=pw1[i-1]*p%P;
    for(int i=1;i<=n;++i) pw2[i]=pw2[i-1]*(1-p)%P;
    h[0][0]=1;
    for(int i=1;i<=n;++i)
    {
        h[i][0]=1;
        for(int j=1;j<=i;++j)
        {
            h[i][j]=(pw2[j]*h[i-1][j]%P+pw1[i-j]*h[i-1][j-1]%P)%P;
        }
    }
    for(int i=1;i<=n;++i)
    {
        g[i]=1;
        for(int j=1;j<=i-1;++j)
        {
            g[i]=(g[i]-g[j]*h[i][j]%P)%P;
        }
    }
    for(int i=1;i<=n;++i)
    {
        f[i]=g[i]*h[i][i]%P*(i*(i-1)/2)%P;
        for(int j=1;j<=i-1;++j)
        {
            f[i]=(f[i]+g[j]*h[i][j]%P*(j*(i-j)+j*(j-1)/2+f[j]+f[i-j])%P)%P;
        }
        f[i]=f[i]*inv(1-g[i]*h[i][i]%P)%P;
    }
    printf("%lld",(f[n]%P+P)%P);
    return 0;
}