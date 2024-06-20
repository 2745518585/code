#include<cstdio>
#include<algorithm>
#include<set>
using namespace std;
typedef long long ll;
const int N=5001;
const ll P=998244353;
int n;
ll m,a[N],f[N][2];
char b[N];
ll solve(ll k)
{
    for(int i=0;i<=n+1;++i) f[i][0]=f[i][1]=0;
    f[0][0]=1;
    for(int i=1;i<=n;++i)
    {
        if(b[i]!='S'&&abs(a[i])<=i*m)
        {
            if(abs(a[i-1]-a[i])<=m) f[i][0]=(f[i][0]+f[i-1][0])%P;
            if(abs(a[i-1]+a[i]-k)<=m*2) f[i][0]=(f[i][0]+f[i-1][1])%P;
        }
        if(b[i]!='P'&&abs(a[i])<=(n-i+1)*m)
        {
            if(abs(a[i-1]-a[i])<=m) f[i][1]=(f[i][1]+f[i-1][1])%P;
            if(a[i-1]+a[i]==k) f[i][1]=(f[i][1]+f[i-1][0])%P;
        }
    }
    ll s=f[n][1];
    if(a[n]==k) s=(s+f[n][0])%P;
    return s;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%lld%s",&n,&m,b+1);
        for(int i=1;i<=n;++i)
        {
            scanf("%lld",&a[i]);
        }
        a[0]=a[n+1]=0;
        set<ll> Set;
        for(int i=0;i<=n;++i) Set.insert(a[i]+a[i+1]);
        ll s=0;
        for(auto i:Set)
        {
            s=(s+solve(i))%P;
        }
        printf("%lld\n",s);
    }
    return 0;
}