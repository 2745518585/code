#include<cstdio>
#include<algorithm>
#include<cmath>
#include<map>
using namespace std;
typedef long long ll;
ll a,b,P;
map<ll,ll> Map;
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
    scanf("%lld%lld%lld",&P,&a,&b);
    ll k=sqrt(P);
    for(ll i=1;i<=k;++i)
    {
        Map[b*qpow(a,i)%P]=i;
    }
    ll s=1e18;
    for(ll i=1;i<=k;++i)
    {
        ll z=qpow(a,i*k);
        if(Map.count(z)) s=min(s,i*k-Map[z]);
    }
    if(s!=1e18) printf("%lld",s);
    else printf("no solution");
    return 0;
}