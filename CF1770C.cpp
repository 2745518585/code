#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const ll N=2001;
ll n;
ll a[N];
bool h[N][N];
ll gcd(ll a,ll b)
{
    if(b==0) return a;
    return gcd(b,a%b);
}
int main()
{
    ll T;
    scanf("%lld",&T);
    while(T--)
    {
        scanf("%lld",&n);
        for(ll i=1;i<=n;++i)
        {
            scanf("%lld",&a[i]);
        }
        bool u=true;
        for(ll i=1;i<=n;++i)
        {
            for(ll j=i+1;j<=n;++j)
            {
                if(a[i]==a[j])
                {
                    u=false;
                    break;
                }
            }
        }
        if(!u)
        {
            printf("NO\n");
            continue;
        }
        for(ll i=1;i<=n*2;++i)
        {
            for(ll j=0;j<=n*2;++j) h[i][j]=false;
        }
        for(ll i=1;i<=n;++i)
        {
            for(ll j=1;j<=n;++j)
            {
                if(i==j) continue;
                ll x=abs(a[i]-a[j]);
                for(ll k=2;k<=n*2;++k)
                {
                    if(x%k==0) h[k][a[i]%k]=true;
                }
            }
        }
        for(ll i=2;i<=n*2;++i)
        {
            ll w=0;
            for(ll j=0;j<=i-1;++j) w+=h[i][j];
            if(w==i)
            {
                u=false;
                break;
            }
        }
        if(u) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}