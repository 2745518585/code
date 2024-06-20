#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=3000001;
const ll P=335544322,P2=167772161;
int n,sp,pr[N],mu[N];
bool ip[N];
ll jc[N],ivjc[N],f[N],g[N],h1[N],h2[N],d[N],t[N];
void exgcd(ll a,ll b,ll &x,ll &y)
{
    if(b==0) x=1,y=0;
    else exgcd(b,a%b,y,x),y-=a/b*x;
}
ll inv(ll a)
{
    a=(a%P2+P2)%P2;
    ll x,y;
    exgcd(a,P2,x,y);
    return (x%P2+P2)%P2;
}
ll qpow(ll x,ll y,ll P=::P)
{
    ll a=1,b=x;
    while(y!=0)
    {
        if(y&1) a=a*b%P;
        b=b*b%P;
        y>>=1;
    }
    return a;
}
int sum(int a,int b)
{
    return (a&b)==b;
}
void NTT(int n,ll *a,int u)
{
    int x=0;
    static int d[N];
    while((1<<x)<n) ++x;
    for(int i=0;i<n;++i)
    {
        d[i]=(d[i>>1]>>1)|((i&1)<<(x-1));
    }
    for(int i=0;i<n;++i)
    {
        if(i<d[i]) swap(a[i],a[d[i]]);
    }
    for(int i=1;i<n;i<<=1)
    {
        int t=qpow(3,(P2-1)/(i*2));
        if(u==-1) t=inv(t);
        for(int j=0;j<n;j+=i*2)
        {
            ll w=1;
            for(int k=j;k<i+j;++k)
            {
                ll q=w*a[k+i]%P2;
                a[k+i]=(a[k]-q)%P2;
                a[k]=(a[k]+q)%P2;
                w=w*t%P2;
            }
        }
    }
}
void mul(ll *a,ll *b,ll *c)
{
    int x=0;
    while((1<<x)<=n*2) ++x;
    x=(1<<x);
    for(int i=n+1;i<=x;++i) a[i]=b[i]=0;
    NTT(x,a,1);
    NTT(x,b,1);
    for(int i=0;i<=x;++i) c[i]=a[i]*b[i]%P2;
    NTT(x,c,-1);
    for(int i=0;i<=n*2;++i)
    {
        c[i]=c[i]*inv(x)%P2;
    }
}
int main()
{
    scanf("%d",&n);
    jc[0]=1;
    for(int i=1;i<=n*2;++i) jc[i]=jc[i-1]*i%P;
    ivjc[n*2]=inv(jc[n*2]);
    for(int i=n*2;i>=1;--i) ivjc[i-1]=ivjc[i]*i%P;
    mu[1]=1;
    for(int i=2;i<=n;++i)
    {
        if(ip[i]==false) pr[++sp]=i,mu[i]=-1;
        for(int j=1;j<=sp&&i*pr[j]<=n;++j)
        {
            ip[i*pr[j]]=true;
            if(i%pr[j]==0) break;
            mu[i*pr[j]]=-mu[i];
        }
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=1;i*j<=n;++j) d[i]=(d[i]+(n-i*j))%P;
    }
    for(int i=2;i<=n;++i)
    {
        for(int j=1;(i-1)*j<=n;++j)
        {
            t[i]=(t[i]+mu[j]*d[(i-1)*j]%P*d[(i-1)*j]%P)%P;
        }
    }
    for(int i=0;i<=n;++i) h1[i]=(t[i]-t[i+1]*2+t[i+2])*jc[i]%P;
    for(int i=0;i<=n;++i) h2[n-i]=ivjc[i];
    mul(h1,h2,g);
    for(int i=0;i<=n;++i) g[i]=g[n+i]*ivjc[i]%P;
    for(int i=0;i<=n;++i)
    {
        h1[i]=jc[n-i]*jc[i]%P*g[i]%P;
    }
    for(int i=0;i<=n;++i)
    {
        h2[n-i]=(i&1?-1:1)*ivjc[i]%P;
    }
    mul(h1,h2,f);
    for(int i=0;i<=n;++i) f[i]=f[n+i]*ivjc[i]%P;
    ll s=1,q=1;
    for(int i=2;i<=n;++i)
    {
        ll w=0;
        for(int j=n-i-1;j<=n-i;++j)
        {
            for(int k=i+j;k<=n;++k)
            {
                w=(w+(t[k]-t[k-1]*2+t[k+2])%2*sum(k,i)*sum(k-i,j)*(n-i-j<=1))%2;
            }
        }
        w=(w%2+2)%2;
        f[i]=(f[i]%P2+P2)%P2;
        if(w%2!=f[i]%2) f[i]+=P2;
        q=q*i%(P+1);
        s=s*qpow(q,f[i],P+1)%(P+1);
    }
    printf("%lld",(s%(P+1)+(P+1))%(P+1));
    return 0;
}