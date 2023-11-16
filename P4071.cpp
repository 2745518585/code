#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=2000001;
const ll P=1e9+7;
ll jc[N],d[N];
void init_jc(int x)
{
    jc[0]=1;
    for(int i=1;i<=x;++i) jc[i]=(jc[i-1]*i)%P;
}
void inv0(ll a,ll b,ll &x,ll &y)
{
    if(b==0) x=1,y=0;
    else inv0(b,a%b,y,x),y-=a/b*x;
}
ll inv(ll a)
{
    ll x,y;
    inv0(a,P,x,y);
    x=(x%P+P)%P;
    return x;
}
ll A(ll a,ll b)
{
    if(a>b) return 0;
    return (jc[b]*inv(jc[b-a]))%P;
}
ll C(ll a,ll b)
{
    if(a>b) return 0;
    return (jc[b]*inv(jc[b-a]*jc[a]%P))%P;
}
void init(int x)
{
    d[0]=1,d[1]=0,d[2]=1;
    for(int i=3;i<=x;++i)
    {
        d[i]=(i-1)*(d[i-1]+d[i-2])%P;
    }
}
int main()
{
    init_jc(N);
    init(N);
    int T;
    scanf("%d",&T);
    while(T--)
    {
        ll a,b;
        scanf("%lld%lld",&a,&b);
        printf("%lld\n",C(b,a)*d[a-b]%P);
    }
    return 0;
}