#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=101;
const ll P=998244353;
int n;
ll k,jc[N],f[N];
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
ll C(ll a,ll b)
{
    if(a<b) return 0;
    return jc[a]*inv(jc[b]*jc[a-b]%P)%P;
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
ll solve(int x)
{
    ll s=0;
    for(int i=1;i<=n;++i)
    {
        for(int j=0;j<=i-1;++j)
        {
            for(int l=j+1;l<=n-i;++l)
            {
                s=(s+C(i-1,j)*qpow(x-1,j)%P*qpow(k-x+1,i-1-j)%P*C(n-i,l)%P*qpow(k-x,l)%P*qpow(x,n-i-l)%P)%P;
            }
        }
    }
    return s*x%P;
}
int main()
{
    scanf("%d%lld",&n,&k);
    jc[0]=1;
    for(int i=1;i<=n;++i) jc[i]=jc[i-1]*i%P;
    for(int i=1;i<=n+2;++i) f[i]=solve(i);
    for(int i=1;i<=n+2;++i) f[i]=(f[i]+f[i-1])%P;
    ll s=0;
    for(int i=1;i<=n+2;++i)
    {
        ll w=1;
        for(int j=1;j<=n+2;++j)
        {
            if(i!=j) w=(w*(k-j)%P*inv(i-j)%P)%P;
        }
        s=(s+w*f[i]%P)%P;
    }
    printf("%lld",(s%P+P)%P);
    return 0;
}