#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=2000001;
const ll P=1e9+7;
int n,m;
ll k,jc[N];
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
    return (x%P+P)%P;
}
ll C(ll a,ll b)
{
    if(a<b) return 0;
    return jc[a]*inv(jc[b]*jc[a-b]%P)%P;
}
ll qpow(ll a,ll b)
{
    ll x=1,y=a;
    while(b)
    {
        if(b&1) x=x*y%P;
        y=y*y%P;
        b>>=1;
    }
    return x;
}
int main()
{
    jc[0]=1;
    for(int i=1;i<=1000000;++i) jc[i]=jc[i-1]*i%P;
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d",&n,&m,&k);
        if(m==0)
        {
            printf("0\n");
            continue;
        }
        if(m==n)
        {
            printf("%lld\n",n*k%P);
            continue;
        }
        ll s=0;
        for(int i=1;i<=m;++i)
        {
            s=(s+C((n-i-1),m-i)*(i*k%P)%P*inv(qpow(2,n-i))%P)%P;
        }
        printf("%lld\n",s);
    }
    return 0;
}