#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const ll N=1000001;
ll n,k,b[N];
struct str
{
    ll a,b;
}a[N];
bool cmp(str a,str b)
{
    return a.a<b.a;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%lld%lld",&n,&k);
        for(ll i=1;i<=n;++i)
        {
            scanf("%lld",&a[i].a);
        }
        for(ll i=1;i<=n;++i)
        {
            scanf("%lld",&a[i].b);
        }
        sort(a+1,a+n+1,cmp);
        a[n+1].a=1e18;
        b[n+1]=1e18;
        for(ll i=n;i>=1;--i) b[i]=min(b[i+1],a[i].b);
        ll x=1,s=0;
        bool u;
        while(true)
        {
            s+=k;
            while(a[x].a<=s) ++x;
            if(x==n+1)
            {
                u=true;
                break;
            }
            k-=b[x];
            if(k<=0)
            {
                u=false;
                break;
            }
        }
        if(u==true) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}