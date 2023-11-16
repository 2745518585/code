#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
ll a,P;
void exgcd(ll a,ll b,ll &x,ll &y)
{
    if(b==0) x=1,y=0;
    else exgcd(b,a%b,y,x),y-=a/b*x;
}
ll inv(ll a)
{
    a=(a%P+P)%P;
    ll x,y;
    exgcd(a,P,x,y);
    x=(x%P+P)%P;
    return x;
}
int main()
{
    scanf("%lld%lld",&a,&P);
    printf("%lld",inv(a));
    return 0;
}