#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=2000001;
ll a1[N],a2[N];
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
ll qpow(ll a,ll b,ll P)
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
ll F(ll a,ll P,ll k)
{
    if(a==0) return 1;
    ll s=1;
    for(ll i=1;i<=k;++i)
    {
        if(i%P!=0) s=s*i%k;
    }
    s=qpow(s,a/k,k);
    for(ll i=1;i<=a%k;++i)
    {
        if(i%P!=0) s=s*i%k;
    }
    return F(a/P,P,k)*s%k;
}
ll G(ll a,ll P)
{
    if(a<P) return 0;
    return G(a/P,P)+a/P;
}
ll sum(ll a,ll b,ll P,ll k)
{
    return F(a,P,k)*inv(F(a-b,P,k)*F(b,P,k)%k,k)%k*qpow(P,G(a,P)-G(a-b,P)-G(b,P),k)%k;
}
ll Lucas(ll a,ll b,ll P)
{
    int q=0;
    ll x=P;
    for(ll i=2;i*i<=P;++i)
    {
        if(x%i==0)
        {
            ll w=1;
            while(x%i==0) x/=i,w*=i;
            a1[++q]=w;
            a2[q]=sum(a,b,i,w);
        }
    }
    if(x!=1)
    {
        a1[++q]=x;
        a2[q]=sum(a,b,x,x);
    }
    ll s=0;
    for(int i=1;i<=q;++i)
    {
        s+=a2[i]*(P/a1[i])%P*inv(P/a1[i],a1[i])%P;
    }
    return (s%P+P)%P;
}
int main()
{
    ll n,m,P;
    scanf("%lld%lld%lld",&n,&m,&P);
    printf("%lld\n",Lucas(n,m,P));
    return 0;
}