#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=100001;
ll jc[N],P;
void init_jc(int x)
{
    jc[0]=1;
    for(int i=1;i<=x;++i)
    {
        jc[i]=(jc[i-1]*i)%P;
    }
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
ll C0(ll a,ll b)
{
    if(a>b) return 0;
    return jc[b]*inv(jc[b-a]*jc[a]%P)%P;
}
ll C(ll a,ll b)
{
    if(a==0) return 1;
    return C(a/P,b/P)*C0(a%P,b%P)%P;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        ll a,b;
        scanf("%lld%lld%lld",&a,&b,&P);
        init_jc(P-1);
        printf("%lld\n",C(a,a+b)%P);
    }
    return 0;
}