#include<cstdio>
#include<algorithm>
typedef long long ll;
const ll P=1ll<<30;
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
ll solve(ll a,ll b,ll d)
{
    int c=a|b;
    ll x,y,k=gcd(P,d);
    exgcd(P,d,x,y);
    if(c%k!=0) return -1;
    y=((y%P+P)%P)*(c/k)%P;
    return d*y;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        ll a,b,d;
        scanf("%lld%lld%lld",&a,&b,&d);
        printf("%lld\n",solve(a,b,d));
    }
    return 0;
}
