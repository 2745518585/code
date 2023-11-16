#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1001;
const ll P=1e9+7;
int n,m,a[N];
ll g[N][N];
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
    ll s=0;
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        s=(s+(m+1-a[i]))%P;
    }
    for(int i=1;i<=n-1;++i)
    {
        g[a[i]][a[i+1]]=(g[a[i]][a[i+1]]+1)%P;
    }
    ll w=inv(2);
    for(int i=1;i<=m;++i)
    {
        s=(s-g[i][i]*(m+1-i)%P)%P;
        for(int j=i+1;j<=m;++j)
        {
            g[i+1][j]=(g[i+1][j]+g[i][j]*w%P)%P;
            g[i][j+1]=(g[i][j+1]+g[i][j]*w%P)%P;
        }
    }
    printf("%lld\n",(s%P+P)%P);
    return 0;
}