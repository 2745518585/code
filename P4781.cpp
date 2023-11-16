#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=10001;
const ll P=998244353;
int n;
ll k,a[N],b[N];
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
int main()
{
    scanf("%d%lld",&n,&k);
    for(int i=1;i<=n;++i)
    {
        scanf("%lld%lld",&a[i],&b[i]);
    }
    ll s=0;
    for(int i=1;i<=n;++i)
    {
        ll w1=1,w2=1;
        for(int j=1;j<=n;++j)
        {
            if(i==j) continue;
            w1=w1*(k-a[j])%P;
            w2=w2*(a[i]-a[j])%P;
        }
        s=(s+w1*inv(w2)%P*b[i]%P)%P;
    }
    printf("%lld",(s%P+P)%P);
    return 0;
}