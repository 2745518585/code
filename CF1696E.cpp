#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll P=1e9+7;
ll jc[N];
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
ll C(ll a,ll b)
{
    if(b>a) return 0;
    return (jc[a]*inv(jc[a-b]*jc[b]%P))%P;
}
int main()
{
    init_jc(500000);
    int n;
    scanf("%d",&n);
    ll s=0;
    for(int i=0;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        s=(s+C(i+x,x-1))%P;
    }
    printf("%lld\n",(s%P+P)%P);
    return 0;
}