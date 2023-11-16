#include<cstdio>
#include<algorithm>
#include<cmath>
#include<map>
using namespace std;
typedef long long ll;
const int N=1000001;
ll a,b,P,k,s=1e18;
map<ll,ll> Map;
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
ll qpow(ll a,ll b)
{
    ll x=1,y=a;
    while(b)
    {
        if(b&1) x=(x*y)%P;
        y=(y*y)%P;
        b>>=1;
    }
    return x;
}
int main()
{
    scanf("%lld%lld%lld",&P,&a,&b);
    k=sqrt(P);
    for(ll i=0;i<=k-1;++i)
    {
        Map[b*qpow(a,i)%P]=i;
    }
    for(int i=0;i<=k;++i)
    {
        ll z=qpow(a,i*k)%P;
        if(Map.count(z))
        {
            if(i*k-Map[z]>=0) s=min(s,i*k-Map[z]);
        }
    }
    if(s!=1e18) printf("%lld",s);
    else printf("no solution");
    return 0;
}