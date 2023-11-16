#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const ll P=1e9+7;
const int N=3001;
int n,m,p=1,t[N];
ll f[N][N],g[N][N],h[N],C[N][N];
struct road
{
    int m,q;
}a[N];
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
void dfs(int x)
{
    for(int i=1;i<=n;++i) f[x][i]=1;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        dfs(a[i].m);
        for(int j=1;j<=n;++j) f[x][j]=f[x][j]*g[a[i].m][j]%P;
    }
    for(int i=1;i<=n;++i) g[x][i]=(g[x][i-1]+f[x][i])%P;
}
void exgcd(ll a,ll b,ll &x,ll &y)
{
    if(b==0) x=1,y=0;
    else exgcd(b,a%b,y,x),y-=a/b*x;
}
ll inv(ll a)
{
    ll x,y;
    exgcd(a,P,x,y);
    x=(x%P+P)%P;
    return x;
}
ll binom(ll a,ll b)
{
    if(b>a) return 0;
    ll s=1,w=1;
    for(ll i=a-b+1;i<=a;++i) s=(s*i)%P;
    for(ll i=1;i<=b;++i) w=(w*i)%P;
    return s*inv(w)%P;
}
int main()
{
    scanf("%d%d",&n,&m);
    C[0][0]=1;
    for(int i=1;i<=n;++i)
    {
        C[i][0]=1;
        for(int j=1;j<=i;++j)
        {
            C[i][j]=(C[i-1][j-1]+C[i-1][j])%P;
        }
    }
    for(int i=2;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        road(x,i);
    }
    dfs(1);
    for(int i=1;i<=n;++i)
    {
        h[i]=f[1][i];
        for(int j=1;j<=i-1;++j)
        {
            h[i]=(h[i]-C[i-1][j-1]*h[j]%P+P)%P;
        }
    }
    ll s=0;
    for(int i=1;i<=n;++i)
    {
        s=(s+h[i]*binom(m,i)%P)%P;
    }
    printf("%lld",(s%P+P)%P);
    return 0;
}