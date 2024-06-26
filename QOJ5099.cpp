#include<cstdio>
#include<algorithm>
#include"pilgrimage.h"
using namespace std;
typedef long long ll;
const int N=2000001,M=31;
int q;
ll p1[N],p2[N],p3[N],f[M][N],g[M][N],P,P2;
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
ll F(ll a,int t)
{
    if(a==0) return 1;
    ll s=g[t][(a/p2[t])%p3[t]]*f[t][a%p2[t]]%p2[t];
    return F(a/p1[t],t)*s%p2[t];
}
ll G(ll a,int t)
{
    if(a<p1[t]) return 0;
    return G(a/p1[t],t)+a/p1[t];
}
ll sum(ll a,ll b,int t)
{
    return F(a,t)*inv(qpow(F(b,t),2,p2[t])%p2[t],p2[t])%p2[t]*qpow(p1[t],G(a,t)-G(b,t)*2,p2[t])%p2[t];
}
ll Lucas(ll a,ll b,ll P)
{
    ll s=0;
    for(int i=1;i<=q;++i)
    {
        s+=sum(a,b,i)*(P/p2[i])%P*inv(P/p2[i],p2[i])%P;
    }
    return (s%P+P)%P;
}
ll phi(ll x)
{
    ll s=x;
    for(ll i=2;i*i<=x;++i)
    {
        if(x%i==0)
        {
            s=s/i*(i-1);
            while(x%i==0) x/=i;
        }
    }
    if(x>1) s=s/x*(x-1);
    return s;
}
void init(int,int _p)
{
    P=_p;
    P2=phi(P);
    q=0;
    ll x=P;
    for(ll i=2;i*i<=P;++i)
    {
        if(x%i==0)
        {
            ll w=1;
            while(x%i==0) x/=i,w*=i;
            p1[++q]=i;
            p2[q]=w;
        }
    }
    if(x!=1)
    {
        p1[++q]=x;
        p2[q]=x;
    }
    for(int t=1;t<=q;++t)
    {
        p3[t]=phi(p2[t]);
        f[t][0]=1;
        for(ll i=1;i<=p2[t];++i)
        {
            if(i%p1[t]!=0) f[t][i]=f[t][i-1]*i%p2[t];
            else f[t][i]=f[t][i-1];
        }
        g[t][0]=1;
        for(ll i=1;i<=p3[t];++i)
        {
            g[t][i]=g[t][i-1]*f[t][p2[t]]%p2[t];
        }
    }
}
int ask(ll n)
{
    ll s=0;
    s=(n%P*Lucas(n*2,n,P)%P)*inv(qpow(2,(n*2)%P2,P),P)%P;
    return (s%P+P)%P;
}