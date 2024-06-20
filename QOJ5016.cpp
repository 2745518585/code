#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=201;
const ll P=998244353;
int n,m,k;
ll f[N][N][N];
bool g[N][N];
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
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        g[x][y]=true;
    }
    for(int i=n;i>=1;--i)
    {
        for(int j=i;j<=n;++j)
        {
            bool u=false;
            for(int k=i;k<=j;++k)
            {
                u|=g[k+1][j];
                g[i][j]|=g[i][k]&u;
            }
        }
    }
    for(int i=1;i<=n+1;++i)
    {
        g[i][i-1]=true;
        for(int j=0;j<=n;++j) f[i][i-1][j]=1;
    }
    for(int i=n;i>=1;--i)
    {
        for(int j=i;j<=n;++j)
        {
            for(int k=1;k<=n;++k)
            {
                if(g[i][j]) f[i][j][k]=f[i][j][k-1];
                for(int l=i;l<=j;++l)
                {
                    if(g[i][l-1]) f[i][j][k]=(f[i][j][k]+f[i][l-1][k-1]*f[l+1][j][k]%P)%P;
                }
            }
        }
    }
    ll s=0;
    for(int i=0;i<=n;++i)
    {
        ll w1=1,w2=1;
        for(int j=0;j<=n;++j)
        {
            if(i==j) continue;
            w1=w1*(k-j)%P;
            w2=w2*(i-j)%P;
        }
        s=(s+f[1][n][i]*w1%P*inv(w2)%P)%P;
    }
    printf("%lld",(s%P+P)%P);
    return 0;
}