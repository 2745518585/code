#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=2000001;
const ll P=1e9+7;
int n,m;
ll jc[N];
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
    if(b>a) return 0;
    return (jc[a]*inv(jc[a-b]))%P;
}
ll C(ll a,ll b)
{
    if(b>a) return 0;
    return (jc[a]*inv(jc[a-b]*jc[b]%P))%P;
}
ll qpow(ll a,ll b)
{
    if(b<0) a=inv(a),b=-b;
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
    scanf("%d%d%*d%*d",&n,&m);
    jc[0]=1;
    for(int i=1;i<=max(n,m);++i) jc[i]=jc[i-1]*i%P;
    ll s=0;
    for(int i=1;i<=min(m,n-1);++i)
    {
        s=(s+C(m-1,i-1)*qpow(m,n-i-1)%P*A(n-2,i-1)%P*(i+1)%P*qpow(n,n-2-i)%P)%P;
        // printf("%d %lld\n",i,C(m-1,i-1)*qpow(m,n-i-1)%P*C(n-2,i-1)%P*(i+1)%P*qpow(n,n-2-i)%P);
    }
    printf("%lld",s);
    return 0;
}