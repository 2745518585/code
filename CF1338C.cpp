#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
ll solve1(ll n)
{
    ll x=1;
    while(n>x) n-=x,x*=4;
    return x+n-1;
}
ll sum2(ll n,ll t)
{
    if(t==1) return 0;
    t/=4;
    if(n<=t) return sum2(n,t);
    else if(n<=t*2) return sum2(n-t,t)+t*2;
    else if(n<=t*3) return sum2(n-t*2,t)+t*3;
    else return sum2(n-t*3,t)+t;
}
ll solve2(ll n)
{
    ll x=1;
    while(n>x) n-=x,x*=4;
    return x*2+sum2(n,x);
}
ll sum3(ll n,ll t)
{
    if(t==1) return 0;
    t/=4;
    if(n<=t) return sum3(n,t);
    else if(n<=t*2) return sum3(n-t,t)+t*3;
    else if(n<=t*3) return sum3(n-t*2,t)+t;
    else return sum3(n-t*3,t)+t*2;
}
ll solve3(ll n)
{
    ll x=1;
    while(n>x) n-=x,x*=4;
    return x*3+sum3(n,x);
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        ll x;
        scanf("%lld",&x);
        if(x%3==1) printf("%lld\n",solve1((x+2)/3));
        else if(x%3==2) printf("%lld\n",solve2((x+2)/3));
        else if(x%3==0) printf("%lld\n",solve3((x+2)/3));
    }
    return 0;
}