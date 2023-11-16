#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const ll P=998244353;
ll n,m,k;
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
    ll s=1;
    for(ll i=a-b+1;i<=a;++i) s=s*(i%P)%P;
    for(ll i=1;i<=b;++i) s=s*inv(i%P)%P;
    return s;
}
int main()
{
    scanf("%lld%lld%lld",&n,&m,&k);
    if(m%k!=0)
    {
        printf("0");
        return 0;
    }
    m/=k;
    ll s=0;
    for(ll i=0;i<=n-k+1;++i)
    {
        if(i%2==0) s=(s+C(n-k+1,i)*C(m-i*k+n*2-k,n*2-k)%P)%P;
        else s=(s-C(n-k+1,i)*C(m-i*k+n*2-k,n*2-k)%P)%P;
    }
    printf("%lld",(s%P+P)%P);
    return 0;
}