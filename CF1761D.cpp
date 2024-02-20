#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll P=1e9+7;
int n,k;
ll pw3[N],jc[N],ivjc[N];
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
    if(b>a||b<0) return 0;
    return (jc[a]*ivjc[a-b]%P*ivjc[b]%P)%P;
}
int main()
{
    scanf("%d%d",&n,&k);
    jc[0]=1;
    for(int i=1;i<=n;++i) jc[i]=jc[i-1]*i%P;
    ivjc[n]=inv(jc[n]);
    for(int i=n;i>=1;--i) ivjc[i-1]=ivjc[i]*i%P;
    pw3[0]=1;
    for(int i=1;i<=n;++i) pw3[i]=pw3[i-1]*3%P;
    if(k==0)
    {
        printf("%lld",pw3[n]);
        return 0;
    }
    ll s=0;
    for(int i=2;i<=n+1;++i)
    {
        s=(s+C(k-1,i/2-1)*C(n-k,(i-1)/2)%P*pw3[n-i+1]%P)%P;
    }
    printf("%lld\n",s);
    return 0;
}