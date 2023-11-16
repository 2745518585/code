#include<cstdio>
using namespace std;
typedef long long ll;
const int N=11;
int n;
ll a[N],b[N],m=1,s;
void exgcd(ll a,ll b,ll &x,ll &y)
{
    if(b==0) x=1,y=0;
    else exgcd(b,a%b,y,x),y-=a/b*x;
}
ll inv(ll a,ll P)
{
    ll x,y;
    exgcd(a,P,x,y);
    x=(x%P+P)%P;
    return x;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%lld%lld",&b[i],&a[i]);
        m*=b[i];
    }
    for(int i=1;i<=n;++i)
    {
        s+=a[i]*(m/b[i])*inv(m/b[i],b[i]);
    }
    printf("%lld",s%m);
    return 0;
}