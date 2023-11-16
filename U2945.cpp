#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2001;
const ll P=998244353;
int n,m,a[N],b[N];
ll jc[N],jc1[N],jc2[N],f[N][N],g[N][N],C[N][N],o[N];
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
ll qpow(ll a,ll b)
{
    ll x=1,y=a;
    while(b)
    {
        if(b&1) x=x*y%P;
        y=y*y%P;
        b>>=1;
    }
    return x;
}
ll sum(ll n,ll m)
{
    if(n<=m+2)
    {
        ll s=0;
        for(int i=1;i<=n;++i) s=(s+qpow(i,m))%P;
        return s;
    }
    jc[0]=jc1[0]=1;
    for(int i=1;i<=m+2;++i) jc[i]=jc[i-1]*i%P,jc1[i]=jc1[i-1]*(n-i)%P;
    jc2[m+3]=1;
    for(int i=m+2;i>=1;--i) jc2[i]=jc2[i+1]*(n-i)%P;
    ll s=0,w=(m==0);
    for(int i=1;i<=m+2;++i)
    {
        w=(w+qpow(i,m))%P;
        s=(s+w*jc1[i-1]%P*jc2[i+1]%P*inv(jc[i-1]%P*jc[(m+2)-i]%P)%P*(((m+2)-i)%2==0?1:-1)%P)%P;
    }
    return (s%P+P)%P;
}
int main()
{
    scanf("%d%d",&n,&m);
    ll p=1;
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d",&a[i],&b[i]);
        p=(p*(b[i]-a[i])%P*i%P)%P;
    }
    C[0][0]=1;
    for(int i=1;i<=n;++i)
    {
        C[i][0]=1;
        for(int j=1;j<=n;++j)
        {
            C[i][j]=(C[i-1][j-1]+C[i-1][j])%P;
        }
    }
    f[0][0]=1;
    for(int i=1;i<=n;++i)
    {
        for(int j=0;j<=m;++j) o[j]=(sum(b[i]-1,j)-sum(a[i]-1,j)+P)%P;
        for(int j=0;j<=m;++j)
        {
            for(int k=0;k<=j;++k)
            {
                f[i][j]=(f[i][j]+C[j][k]*f[i-1][j-k]%P*o[k]%P)%P;
            }
        }
    }
    g[1][1]=1;
    for(int i=2;i<=n;++i)
    {
        for(int j=1;j<=i;++j)
        {
            g[i][j]=(j*g[i-1][j]+(i-j+1)*g[i-1][j-1]%P)%P;
        }
    }
    ll s=0;
    for(int i=0;i<=n-1;++i)
    {
        o[0]=1;
        for(int j=1;j<=m;++j) o[j]=o[j-1]*i%P;
        for(int j=0;j<=m;++j) s=(s+g[n][i+1]*C[m][j]%P*f[n][m-j]%P*o[j]%P)%P;
    }
    printf("%lld",(s*inv(p)%P+P)%P);
    return 0;
}