#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=2000001;
const ll P=1e9+7;
int a,b,n;
ll jc[N],s;
void init_jc(int x)
{
    jc[0]=1;
    for(int i=1;i<=x;++i) jc[i]=jc[i-1]*i%P;
}
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
ll C(ll a,ll b)
{
    if(a<b) return 0;
    return jc[a]*inv(jc[b]*jc[a-b]%P)%P;
}
bool check(int x)
{
    while(x)
    {
        if(x%10!=a&&x%10!=b) return false;
        x/=10;
    }
    return true;
}
int main()
{
    scanf("%d%d%d",&a,&b,&n);
    init_jc(n);
    for(int i=0;i<=n;++i)
    {
        if(check(a*i+b*(n-i))) s=(s+C(n,i))%P;
    }
    printf("%lld",s);
    return 0;
}