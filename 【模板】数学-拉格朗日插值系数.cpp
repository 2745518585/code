#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=5001;
const ll P=998244353;
int n;
ll a1[N],a2[N],f[N];
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
void solve()
{
    static ll b[N];
    for(int i=0;i<=n+1;++i) b[i]=0;
    b[0]=1;
    for(int i=1;i<=n;++i)
    {
        for(int j=i;j>=0;--j)
        {
            b[j]=(b[j]*(-a1[i])%P+(j>0?b[j-1]:0))%P;
        }
    }
    for(int i=1;i<=n;++i)
    {
        ll w=1;
        for(int j=1;j<=n;++j)
        {
            if(i!=j) w=w*(a1[i]-a1[j])%P;
        }
        w=a2[i]*inv(w)%P;
        if(a1[i]==0)
        {
            for(int j=0;j<=n-1;++j) f[j]=(f[j]+w*b[j+1]%P)%P;
            continue;
        }
        ll p=inv(-a1[i]),t=b[0]*p%P;
        for(int j=0;j<=n-1;++j)
        {
            f[j]=(f[j]+w*t%P)%P;
            t=(b[j+1]-t)*p%P;
        }
    }
}
int main()
{
    ll k;
    scanf("%d%lld",&n,&k);
    for(int i=1;i<=n;++i)
    {
        scanf("%lld%lld",&a1[i],&a2[i]);
    }
    solve();
    ll s=0,w=1;
    for(int i=0;i<=n-1;++i)
    {
        s=(s+w*f[i]%P)%P;
        w=w*k%P;
    }
    printf("%lld",(s%P+P)%P);
    return 0;
}