#include<cstdio>
#include<algorithm>
#include<unordered_map>
using namespace std;
typedef long long ll;
const int N=1000001;
int sp,p[N];
bool ip[N];
ll n,mu[N],phi[N],mu2[N],phi2[N];
unordered_map<ll,ll> Map1,Map2;
ll solve1(ll n)
{
    if(n<=1000000) return phi2[n];
    if(Map1.count(n)) return Map1[n];
    ll s=n*(n+1)/2;
    for(ll i=2;i<=n;++i)
    {
        int j=n/(n/i);
        s-=(j-i+1)*solve1(n/i);
        i=j;
    }
    return Map1[n]=s;
}
ll solve2(ll n)
{
    if(n<=1000000) return mu2[n];
    if(Map2.count(n)) return Map2[n];
    ll s=1;
    for(ll i=2;i<=n;++i)
    {
        ll j=n/(n/i);
        s-=(j-i+1)*solve2(n/i);
        i=j;
    }
    return Map2[n]=s;
}
int main()
{
    mu[1]=1;
    phi[1]=1;
    for(int i=2;i<=1000000;++i)
    {
        if(ip[i]==false) p[++sp]=i,mu[i]=-1,phi[i]=i-1;
        for(int j=1;j<=sp&&i*p[j]<=1000000;++j)
        {
            ip[i*p[j]]=true;
            if(i%p[j]==0)
            {
                phi[i*p[j]]=phi[i]*p[j];
                break;
            }
            phi[i*p[j]]=phi[i]*phi[p[j]];
            mu[i*p[j]]=-mu[i];
        }
    }
    for(int i=1;i<=1000000;++i) mu2[i]=mu2[i-1]+mu[i],phi2[i]=phi2[i-1]+phi[i];
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%lld",&n);
        printf("%lld %lld\n",solve1(n),solve2(n));
    }
    return 0;
}