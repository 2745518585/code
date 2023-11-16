#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
const int N=101;
ll n,k,d,f[N];
bool h[N];
void SPFA(ll x)
{
    queue<ll> Q;
    for(ll i=0;i<=d-1;++i)
    {
        Q.push(i);
        h[i]=true;
    }
    while(!Q.empty())
    {
        ll k=Q.front();
        Q.pop();
        if(h[k]==false) continue;
        h[k]=false;
        if(f[k]+x<f[(k+x)%d])
        {
            f[(k+x)%d]=f[k]+x;
            h[(k+x)%d]=true;
            Q.push((k+x)%d);
        }
    }
}
ll check(ll x)
{
    ll s=0;
    for(ll i=0;i<=d-1;++i)
    {
        if(x>=f[i]) s+=(x-f[i])/d+1;
    }
    return s-1;
}
int main()
{
    int TOT;
    scanf("%d",&TOT);
    while(TOT--)
    {
        scanf("%lld%lld",&n,&k);
        if(k>(n-1)/2)
        {
            printf("-1\n");
            continue;
        }
        d=1;
        while(n%d==0) ++d;
        f[0]=0;
        for(ll i=1;i<=d-1;++i) f[i]=1e18;
        while(true)
        {
            ll v=1e18;
            for(ll i=1;i<=d-1;++i)
            {
                ll p=0;
                for(ll j=1;j<=d-1;++j)
                {
                    p=max(p,(n-f[((n-i*j)%d+d)%d])/j+1);
                }
                if((p-i+d)%d!=0) p+=(d-(p-i+d)%d);
                if(f[i]>p) v=min(v,p);
            }
            if(v>=n/2) break;
            SPFA(v);
        }
        if(k<=check(n/2))
        {
            ll l=1,r=n/2;
            while(l<r)
            {
                ll z=l+r>>1;
                if(check(z)>=k) r=z;
                else l=z+1;
            }
            printf("%lld\n",l);
        }
        else
        {
            k=(n-1)/2-k+1;
            ll l=1,r=n/2;
            while(l<r)
            {
                ll z=l+r>>1;
                if(z-check(z)>=k) r=z;
                else l=z+1;
            }
            printf("%lld\n",n-l);
        }
    }
    return 0;
}