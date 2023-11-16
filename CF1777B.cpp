#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const ll P=1e9+7;
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        ll n;
        scanf("%lld",&n);
        ll w=1;
        for(ll i=1;i<=n;++i) w=w*i%P;
        printf("%lld\n",n*(n-1)%P*w%P);
    }
    return 0;
}