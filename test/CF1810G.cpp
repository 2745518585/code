#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=6001;
const ll P=1e9+7;
int n;
ll a[N],f[2][N],g[2][N];
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
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
        {
            ll x,y;
            scanf("%lld%lld",&x,&y);
            a[i]=x*inv(y)%P;
        }
        for(int i=0;i<=n+1;++i) f[0][i]=g[0][i]=0;
        scanf("%lld",&g[0][0]);
        for(int i=1;i<=n;++i)
        {
            scanf("%lld",&f[0][i]);
        }
        for(int i=1;i<=n;++i)
        {
            int t=i&1;
            for(int j=0;j<=n+1;++j) f[t][j]=g[t][j]=0;
            g[t][0]=(g[t][0]+f[t^1][1]*a[i]+g[t^1][1]*a[i])%P;
            for(int j=1;j<=n;++j)
            {
                g[t][j]=(g[t][j]+g[t^1][j-1]*(1-a[i])+g[t^1][j+1]*a[i])%P;
                f[t][j]=(f[t][j]+f[t^1][j-1]*(1-a[i])+f[t^1][j+1]*a[i])%P;
            }
            ll s=0;
            for(int j=0;j<=n;++j) s=(s+g[t][j]);
            printf("%lld ",(s%P+P)%P);
        }
        printf("\n");
    }
    return 0;
}