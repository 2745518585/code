#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=2001,M=51;
const ll P=1e9+7;
int n,a[N],b[N];
ll jc[N],ivjc[N],pw[N*N],ivpw[N*N],f[N],g[N];
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
ll A(ll a,ll b)
{
    if(a<b) return 0;
    return jc[a]*ivjc[a-b]%P;
}
ll C(ll a,ll b)
{
    if(a<b) return 0;
    return jc[a]*ivjc[a-b]%P*ivjc[b]%P;
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
int main()
{
    int n;
    scanf("%d",&n);
    jc[0]=1;
    for(int i=1;i<=n;++i) jc[i]=jc[i-1]*i%P;
    ivjc[n]=inv(jc[n]);
    for(int i=n;i>=1;--i) ivjc[i-1]=ivjc[i]*i%P;
    pw[0]=1;
    for(int i=1;i<=n*50;++i) pw[i]=pw[i-1]*2%P;
    ivpw[n*50]=inv(pw[n*50]);
    for(int i=n*50;i>=1;--i) ivpw[i-1]=ivpw[i]*2%P;
    for(int i=1;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        ++a[x];
    }
    for(int i=50;i>=0;--i)
    {
        a[i]+=a[i+1];
        b[i]=b[i+1]+a[i];
    }
    ll s=0;
    for(int i=0;i<=n;++i)
    {
        f[i]=1;
        for(int j=0;j<=min(n,i);++j)
        {
            f[i]=(f[i]-(j&1?-1:1)*C(n,j)%P*qpow(i-j,n)%P*ivjc[n]%P)%P;
        }
    }
    for(int i=0;i<=n;++i) f[i]=(f[i]-f[i+1])%P;
    for(int i=0;i<=50;++i)
    {
        for(int j=0;j<=n+1;++j) g[j]=f[j],f[j]=0;
        for(int j=0;j<=n+1;++j)
        {
            for(int k=0;k<=a[i];++k)
            {
                f[(j+k)/2]=(f[(j+k)/2]+g[j]*C(a[i],k)%P*ivpw[a[i]]%P)%P;
            }
        }
        for(int j=0;j<=n+1;++j) f[j]=(f[j]%P+P)%P;
        s=(s+f[0]*ivpw[b[i+1]]%P*(a[i]-a[i+1])%P)%P;
    }
    printf("%lld",((1-s)%P+P)%P);
    return 0;
}