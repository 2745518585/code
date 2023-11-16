#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll P=1e9+7;
int n,k,a[N];
ll f[N];
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
ll solve(ll x,int m)
{
    ll p=1000000000-x,t=qpow(p,k);
    f[0]=f[1]=1;
    for(int i=2;i<=m+1;++i)
    {
		f[i]=(p+1)*f[i-1]%P;
		if(i-k-1>=0) f[i]=(f[i]-t*f[i-k-1]%P+P)%P;
    }
    return f[m+1];
}
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n-k+1;++i)
    {
        scanf("%d",&a[i]);
    }
    ll s=1;
    for(int i=1;i<=n-k+1;++i)
    {
        int j=i;
        while(a[j+1]==a[i]) ++j;
        int u=j-i+k;
        if(i!=1&&a[i-1]>a[i]) u-=k;
        if(j!=n-k+1&&a[j+1]>a[i]) u-=k;
        if(u>0) s=s*solve(a[i],u)%P;
        i=j;
    }
    printf("%lld",s);
    return 0;
}