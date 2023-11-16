#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=3000001;
const ll P=998244353;
ll f[N],g[N];
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
    f[0]=1,f[1]=2;
    for(int i=2;i<=2000000;++i)
    {
        f[i]=(f[i-1]+f[i-2])%P;
    }
    g[0]=f[0];
    for(int i=1;i<=1000000;++i) g[i]=(g[i-1]*f[i*2-1])%P;
    // printf("%lld %lld %lld %lld\n",f[1],f[3],f[5],f[7]);
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int m,n;
        scanf("%d%d",&m,&n);
        if(m>n) swap(m,n);
        ll s=0;
        s=(g[m]*qpow(f[m*2],(n-m))%P*g[m]%P)%P;
        printf("%lld\n",(s%P+P)%P);
    }
    return 0;
}