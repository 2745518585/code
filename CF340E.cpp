#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,a[N];
ll s;
ll gcd(ll a,ll b)
{
    if(b==0) return a;
    return gcd(b,a%b);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    sort(a+1,a+n+1);
    ll w=0;
    for(int i=1;i<=n;++i)
    {
        s=s+((ll)a[i]*(2*i-1)-w*2);
        w+=a[i];
    }
    ll z=gcd(s,n);
    printf("%lld %lld",s/z,n/z);
    return 0;
}