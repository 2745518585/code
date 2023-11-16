#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
const int N=2000001;
int n,t;
ll a[N],b[N];
int sum(ll x)
{
    if(x<0) return 0;
    int s=0;
    for(int i=1;i<=n;++i)
    {
        ll z=sqrt(a[i]+x);
        if(z*z==a[i]+x) ++s;
        // if(b[lower_bound(b+1,b+t+1,a[i]+x)-b]==a[i]+x) ++s;
    }
    return s;
}
int check(ll x,ll k)
{
    int s=0;
    for(ll i=1;i*i<=x;++i)
    {
        if(x%i==0&&(x/i+i)%2==0)
        {
            s=max(s,sum(((x/i+i)/2)*((x/i+i)/2)-k));
        }
    }
    return s;
}
int main()
{
    // for(ll i=0;i<=1000000;++i) b[++t]=i*i;
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
        {
            scanf("%lld",&a[i]);
        }
        sort(a+1,a+n+1);
        int w=1,q=1;
        for(int i=2;i<=n;++i)
        {
            if(a[i]==a[i-1]) ++q;
            else q=1;
            w=max(w,q);
        }
        int s=w;
        for(int i=1;i<=n;++i)
        {
            for(int j=i+1;j<=n;++j)
            {
                s=max(s,check(abs(a[i]-a[j]),max(a[i],a[j])));
            }
        }
        printf("%d\n",s);
    }
    return 0;
}