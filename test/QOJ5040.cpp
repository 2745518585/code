#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
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
void mul(ll *a,ll *b,ll *c)
{
    static ll z[N];
    for(int i=1;i<=n;++i) z[i]=0;
    for(int i=1;i<=n;++i)
    {
        for(int j=1;i*j<=n;++j) z[i*j]=(z[i*j]+a[i]*b[j])%P;
    }
    for(int i=1;i<=n;++i) c[i]=z[i];
}
int main()
{
    scanf("%d%lld",&n,&k);
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&b[i]);
    }
    a[1]=1;
    k=inv(k);
    while(k)
    {
        if(k&1) mul(a,b,a);
        mul(b,b,b);
        k>>=1;
    }
    for(int i=1;i<=n;++i)
    {
        printf("%lld ",(a[i]%P+P)%P);
    }
    return 0;
}