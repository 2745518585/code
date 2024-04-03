#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1001;
const ll P=998244353;
int n;
ll p,f[N][N],C[N][N];
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
    scanf("%d%lld",&n,&p);
    p=p*inv(10000)%P;
    C[0][0]=1;
    for(int i=1;i<=n;++i)
    {
        C[i][0]=1;
        for(int j=1;j<=i;++j)
        {
            C[i][j]=(C[i-1][j-1]+C[i-1][j])%P;
        }
    }
    for(int i=0;i<=n;++i) f[0][i]=1;
    for(int i=1;i<=n;++i)
    {
        for(int j=0;j<=n;++j)
        {
            for(int k=0;k<=i-1;++k)
            {
                f[i][j]+=p*f[k][j+1]%P*f[i-k-1][j]%P*C[i][k+1]%P;
                if(j>0) f[i][j]+=(1-p)*f[k][j-1]%P*f[i-k-1][j]%P*C[i][k+1]%P;
            }
            f[i][j]%=P;
        }
    }
    ll s=1;
    for(int i=1;i<=n;++i) s=s*(i*2-1)%P;
    printf("%lld\n",(f[n][0]*inv(s)%P+P)%P);
    return 0;
}