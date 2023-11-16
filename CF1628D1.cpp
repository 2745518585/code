#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=3001;
const ll P=1e9+7;
int n,m;
ll k,f[N][N];
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
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d",&n,&m,&k);
        for(int i=1;i<=n;++i)
        {
            f[i][i]=k*i%P;
            f[i][0]=0;
            for(int j=1;j<=i-1;++j)
            {
                f[i][j]=(f[i-1][j]+f[i-1][j-1])*inv(2)%P;
            }
        }
        printf("%lld\n",f[n][m]);
    }
    return 0;
}