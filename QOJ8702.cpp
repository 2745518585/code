#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=201;
const ll P=1e9+7;
int n,p;
ll f[N][N*N][2];
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
ll sum(ll x)
{
    return x*(x+1)/2;
}
int main()
{
    scanf("%d%d",&n,&p);
    p=n-p+1;
    f[0][0][0]=1;
    for(int i=1;i<=n+1;++i)
    {
        if(i==p) continue;
        for(int j=0;j<=i-1;++j)
        {
            for(int k=0;k<=n*n;++k)
            {
                for(int l:{0,1})
                {
                    f[i][k+sum(i-j-1)][l]=(f[i][k+sum(i-j-1)][l]-f[j][k][l])%P;
                }
                f[i][k+sum(i-j-1)][1]=(f[i][k+sum(i-j-1)][1]-f[j][k][0]*(i-j-1-(j<p&&p<i))%P)%P;
            }
        }
    }
    ll s=0;
    for(int i=0;i<=n*n;++i)
    {
        s=(s+f[n+1][i][1]*inv(1-i*inv(sum(n))%P)%P)%P;
    }
    printf("%lld",(s*inv(n-1)%P+P)%P);
    return 0;
}