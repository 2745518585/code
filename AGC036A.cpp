#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
ll k;
int main()
{
    scanf("%lld",&k);
    ll t=(ll)ceil(sqrt(k));
    printf("%lld %lld %lld %lld %lld %lld\n",0,t*t-k,t,0,t-1,t);
    return 0;
}