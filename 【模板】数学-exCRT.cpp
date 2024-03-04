#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
typedef __int128_t lll;
lll gcd(lll a,lll b)
{
    if(b==0) return a;
    return gcd(b,a%b);
}
void exgcd(lll a,lll b,lll &x,lll &y)
{
    if(b==0) x=1,y=0;
    else exgcd(b,a%b,y,x),y-=a/b*x;
}
lll solve(lll x1,lll y1,lll x2,lll y2)
{
    lll p=((x2-x1)%y2+y2)%y2,k1,k2,z=gcd(y1,y2);
    if(p%z!=0) return -1e18;
    exgcd(y1,y2,k1,k2);
    k1=k1*(p/z)%(y2/z);
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