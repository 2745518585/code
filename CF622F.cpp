#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=2000001;
const ll P=1e9+7;
ll n,jc[N],jc1[N],jc2[N];
int m;
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
int main()
{
    scanf("%lld%d",&n,&m);
    if(n<=m+2)
    {
        ll s=0;
        for(int i=1;i<=n;++i)
        {
            s=(s+qpow(i,m))%P;
        }
        printf("%lld",s);
        return 0;
    }
    jc[0]=jc1[0]=1;
    for(int i=1;i<=m+2;++i) jc[i]=jc[i-1]*i%P,jc1[i]=jc1[i-1]*(n-i)%P;
    jc2[m+3]=1;
    for(int i=m+2;i>=1;--i) jc2[i]=jc2[i+1]*(n-i)%P;
    ll s=0,w=0;
    for(int i=1;i<=m+2;++i)
    {
        w=(w+qpow(i,m))%P;
        s=(s+w*jc1[i-1]%P*jc2[i+1]%P*inv(jc[i-1]%P*jc[(m+2)-i]%P)%P*(((m+2)-i)%2==0?1:-1)%P)%P;
    }
    printf("%lld",(s%P+P)%P);
    return 0;
}