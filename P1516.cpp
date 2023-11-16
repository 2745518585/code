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
int main()
{
    ll x,y,m,n,L;
    scanf("%lld%lld%lld%lld%lld",&x,&y,&m,&n,&L);
    ll a=((m-n)%L+L)%L,b=((y-x)%L+L)%L,d=gcd(a,L);
    if(b%gcd(a,L)!=0) printf("Impossible");
    else
    {
        ll x,y;
        a/=d,L/=d;
        exgcd(a,L,x,y);
        x=(x*(b/d)%L+L)%L;
        printf("%lld",x);
    }
    return 0;
}