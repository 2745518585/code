#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=20000001;
ll n,m;
bool h[N];
int sum(ll x)
{
    int s=0;
    ll z=x;
    for(ll i=2;i*i<=z;++i)
    {
        if(x%i==0) ++s,x/=i;
        if(x%i==0) return 0;
    }
    if(x!=1) ++s;
    if(s%2==1) return -1;
    return 1;
}
ll qpow(ll a,ll b)
{
    ll x=1,y=a;
    while(b)
    {
        if(b&1) x=x*y;
        y=y*y;
        b>>=1;
    }
    return x;
}
int main()
{
    scanf("%lld%lld",&n,&m);
    ll s=0;
    for(ll i=1;i*i<=m;++i)
    {
        if(m%i==0)
        {
            s+=sum(i)*qpow(m/i,n);
            if(m/i!=i) s+=sum(m/i)*qpow(m/(m/i),n);
        }
    }
    printf("%lld",s);
    return 0;
}