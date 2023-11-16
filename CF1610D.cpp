#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll P=1e9+7;
int n,h[N];
int sum(int x)
{
    int s=0;
    while(x%2==0)
    {
        ++s;
        x/=2;
    }
    return s;
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
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        ++h[sum(x)];
    }
    int w=0;
    ll s=0;
    for(int i=30;i>=1;--i)
    {
        if(h[i]>=2) s=(s+(qpow(2,h[i]-1)-1)*qpow(2,w))%P;
        w+=h[i];
    }
    s=(s+(qpow(2,h[0])+P-1)*qpow(2,w))%P;
    printf("%lld",s);
    return 0;
}