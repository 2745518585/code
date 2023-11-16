#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
ll gcd(ll a,ll b)
{
    if(b==0) return a;
    return gcd(b,a%b);
}
void exgcd(ll a,ll b,ll &x,ll &y)
{
    if(b==0) x=1,y=0;
    else exgcd(b,a%b,y,x),y-=a/b*x;
}
ll mul(ll a,ll b,ll P)
{
    ll x=0;
    while(b!=0)
    {
        if(b&1) x=(x+a)%P;
        a=(a+a)%P;
        b>>=1;
    }
    return x;
}
ll solve(ll x1,ll y1,ll x2,ll y2)
{
    ll p=(x2-x1%y2+y2)%y2,k1,k2,z=gcd(y1,y2);
    if(p%z!=0) return -1e18;
    exgcd(y1,y2,k1,k2);
    k1=mul(k1,(p/z),(y2/z));
    return (x1+y1*k1)%(y1/z*y2);
}
ll a,b;
int main()
{
    int n;
    scanf("%d",&n);
    scanf("%lld%lld",&b,&a);
    for(int i=2;i<=n;++i)
    {
        ll c,d;
        scanf("%lld%lld",&d,&c);
        a=solve(a,b,c,d);
        b=b/gcd(b,d)*d;
    }
    printf("%lld",(a%b+b)%b);
    return 0;
}