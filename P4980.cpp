#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const ll P=1e9+7;
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
ll phi(ll x)
{
    ll z=x,s=x;
    for(ll i=2;i*i<=x;++i)
    {
        if(z%i==0)
        {
            s=s-s/i;
            while(z%i==0) z/=i;
        }
    }
    if(z>1) s=s-s/z;
    return s;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        ll n;
        scanf("%lld",&n);
        ll s=0;
        for(ll i=1;i*i<=n;++i)
        {
            if(n%i==0)
            {
                s=(s+qpow(n,i)*phi(n/i)%P)%P;
                if(n/i!=i) s=(s+qpow(n,n/i)*phi(i)%P)%P;
            }
        }
        printf("%lld\n",(s*qpow(n,P-2)%P+P)%P);
    }
    return 0;
}