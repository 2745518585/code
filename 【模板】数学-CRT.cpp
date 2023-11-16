#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n;
ll a[N],b[N];
void exgcd(ll a,ll b,ll &x,ll &y)
{
    if(b==0) x=1,y=0;
    else exgcd(b,a%b,y,x),y-=a/b*x;
}
ll inv(ll a,ll P)
{
    a=(a%P+P)%P;
    ll x,y;
    exgcd(a,P,x,y);
    return (x%P+P)%P;
}
int main()
{
    scanf("%d",&n);
    ll m=1;
    for(int i=1;i<=n;++i)
    {
        scanf("%lld%lld",&a[i],&b[i]);
        m*=a[i];
    }
    ll s=0;
    for(int i=1;i<=n;++i)
    {
        s+=b[i]*(m/a[i])%m*inv(m/a[i],a[i])%m;
    }
    printf("%lld",(s%m+m)%m);
    return 0;
}