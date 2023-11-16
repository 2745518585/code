#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const ll P=10007;
const int N=50001;
ll n,m,q,a[N],f[N],g[N];
bool b[N];
int main()
{
    scanf("%lld%lld",&n,&m);
    ++m;
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&a[i]);
        q=max(q,a[i]);
        a[i]+=a[i-1];
    }
    a[n+1]=1e18;
    ll l=q,r=a[n];
    while(l<r)
    {
        ll z=l+r>>1;
        ll t=0,s=0;
        while(t<n)
        {
            t=upper_bound(a+1,a+n+2,a[t]+z)-a-1;
            ++s;
        }
        if(s>m) l=z+1;
        else r=z;
    }
    printf("%lld ",l);
    ll s=0;
    f[0]=1;
    for(int i=1;i<=m;++i)
    {
        for(int j=0;j<=n;++j) g[j]=f[j],f[j]=0;
        ll t=g[0],T=0;
        for(int j=1;j<=n;++j)
        {
            while(a[j]-a[T]>l) t=(t-g[T++])%P;
            f[j]=t;
            t=(t+g[j])%P;
        }
        s=(s+f[n])%P;
    }
    printf("%lld",(s%P+P)%P);
    return 0;
}