#include<cstdio>
using namespace std;
typedef long long ll;
const int P=1e9+7;
ll a,b;
ll qpow(ll x,ll y)
{
    ll a=1,b=x;
    while(y!=0)
    {
        if(y&1) a=(a*b)%P;
        b=(b*b)%P;
        y/=2;
    }
    return a;
}
int main()
{
    ll a,b;
    scanf("%lld%lld",&a,&b);
    printf("%lld",qpow(a,b));
    return 0;
}