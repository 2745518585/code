#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=10001;
const ll P=1e9+7;
ll jc[N],a,b;
void init_jc(int x)
{
    jc[0]=1;
    for(int i=1;i<=x;++i) jc[i]=(jc[i-1]*i)%P;
}
void exgcd(ll a,ll b,ll &x,ll &y)
{
    if(b==0) x=1,y=0;
    else exgcd(b,a%b,y,x),y-=a/b*x;
}
ll inv(ll a)
{
    ll x,y;
    exgcd(a,P,x,y);
    x=(x%P+P)%P;
    return x;
}
ll A(ll a,ll b)
{
    if(b>a) return 0;
    return (jc[a]*inv(jc[a-b]))%P;
}
ll C(ll a,ll b)
{
    if(b>a) return 0;
    return (jc[a]*inv(jc[a-b]*jc[b]%P))%P;
}
int main()
{
    scanf("%lld%lld",&a,&b);
    init_jc(b);
    printf("%lld %lld",A(a,b),C(a,b));
    return 0;
}