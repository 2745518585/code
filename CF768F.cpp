#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll P=1e9+7;
ll jc[N],n,m,k,s,w;
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
    if(b>a) return 0;
    if(a<0) return 1;
    return (jc[a]*inv(jc[a-b]*jc[b]%P))%P;
}
int main()
{
    scanf("%lld%lld%lld",&m,&n,&k);
    init_jc(n+m);
    for(int i=1;i<=n;++i)
    {
        w=(w+C(n-1,i-1)*(C(m-1,i-1)*2+C(m-1,i-2)+C(m-1,i))%P)%P;
        s=(s+C(n-k*i-1,i-1)*(C(m-1,i-1)*2+C(m-1,i-2)+C(m-1,i))%P)%P;
    }
    if(w==0&&s==0) printf("1");
    else printf("%lld",(s*inv(w)%P+P)%P);
    return 0;
}