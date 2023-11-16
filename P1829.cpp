#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=12000001;
const ll P=20101009;
int n,m,f[N],g[N],mu[N],powk[N];
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
void init()
{
    int t=0,*b=new int[N];
    bool *h=new bool[N];
    mu[1]=1;
    powk[1]=1;
    for(int i=2;i<=11000000;++i)
    {
        if(h[i]==false) b[++t]=i,mu[i]=-1;
        for(int j=1;j<=t&&i*b[j]<=11000000;++j)
        {
            h[i*b[j]]=true;
            if(i%b[j]==0) break;
            mu[i*b[j]]=-mu[i];
        }
    }
    for(int i=1;i<=11000000;++i) f[i]=(f[i-1]+mu[i]*((ll)i*i%P)%P)%P;
    for(int i=1;i<=11000000;++i) g[i]=(g[i-1]+(ll)i)%P;
    delete []b;
    delete []h;
}
ll sum(int m,int n)
{
    ll s=0;
    for(int i=1;i<=min(m,n);++i)
    {
        int j=min(m/(m/i),n/(n/i));
        s+=(ll)(f[j]-f[i-1])*((ll)g[m/i]*g[n/i]%P)%P;
        i=j;
    }
    return s;
}
int main()
{
    scanf("%d%d",&m,&n);
    init();
    ll s=0;
    for(int i=1;i<=min(m,n);++i)
    {
        int j=min(m/(m/i),n/(n/i));
        s+=(ll)(g[j]-g[i-1])*sum(m/i,n/i)%P;
        i=j;
    }
    printf("%lld",(s%P+P)%P);
    return 0;
}