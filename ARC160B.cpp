#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll P=998244353;
ll n,f1[N],f2[N];
ll &sum(ll x)
{
    if(x*x<=n) return f1[n/(n/x)];
    return f2[n/x];
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%lld",&n);
        ll p=sqrt(n)+100;
        for(ll i=0;i<=p;++i) f1[i]=f2[i]=0;
        for(ll i=1;i<=n;++i)
        {
            ll j=n/(n/i);
            if(i>1) sum(j)=sum(n/(n/(i-1)));
            else sum(j)=0;
            ll z=min(n/i,j);
            sum(j)=(sum(j)+(j-i+1)*z*2%P-max(z-i+1,0ll)+P)%P;
            i=j;
        }
        ll s=0;
        for(ll i=1;i<=n;++i)
        {
            ll j=n/(n/i);
            s=(s+(j-i+1)*sum(n/i)%P)%P;
            i=j;
        }
        printf("%lld\n",s);
    }
    return 0;
}