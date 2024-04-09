#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=301;
const ll P=1e9+7;
int n,m;
ll C[N][N],pw[N*N][N],f[N],a1[N*N],a2[N*N],g[N*N];
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
void solve(int n)
{
    static ll b[N*N];
    for(int i=0;i<=n+1;++i) b[i]=0;
    b[0]=1;
    for(int i=1;i<=n;++i)
    {
        for(int j=i;j>=0;--j)
        {
            b[j]=(b[j]*(-a1[i])%P+(j>0?b[j-1]:0))%P;
        }
    }
    for(int i=1;i<=n;++i)
    {
        ll w=1;
        for(int j=1;j<=n;++j)
        {
            if(i!=j) w=w*(a1[i]-a1[j])%P;
        }
        w=a2[i]*inv(w)%P;
        if(a1[i]==0)
        {
            for(int j=0;j<=n-1;++j) g[j]=(g[j]+w*b[j+1]%P)%P;
            continue;
        }
        ll p=inv(-a1[i]),t=b[0]*p%P;
        for(int j=0;j<=n-1;++j)
        {
            g[j]=(g[j]+w*t%P)%P;
            t=(b[j+1]-t)*p%P;
        }
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    if(m>(n*(n+1)/2))
    {
        printf("0");
        return 0;
    }
    C[0][0]=1;
    for(int i=1;i<=n;++i)
    {
        C[i][0]=1;
        for(int j=1;j<=i;++j)
        {
            C[i][j]=(C[i-1][j-1]+C[i-1][j])%P;
        }
    }
    for(int i=1;i<=(n*(n+1)/2);++i)
    {
        pw[i][0]=1;
        for(int j=1;j<=n;++j) pw[i][j]=pw[i][j-1]*i%P;
    }
    for(int k=0;k<=(n*(n+1)/2);++k)
    {
        f[0]=1;
        for(int i=1;i<=n;++i)
        {
            f[i]=0;
            for(int j=1;j<=i;++j)
            {
                f[i]+=C[i-1][j-1]*f[j-1]%P*f[i-j]%P;
            }
            f[i]=f[i]%P*pw[k][i]%P;
        }
        a1[k+1]=k,a2[k+1]=f[n];
    }
    solve((n*(n+1)/2)+1);
    ll s=0;
    for(int i=m;i<=(n*(n+1)/2);++i) s=(s+g[i])%P;
    printf("%lld\n",(s%P+P)%P);
    return 0;
}