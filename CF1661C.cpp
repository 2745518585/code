#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
const int N=1000001;
int n;
ll a[N];
ll solve(ll k)
{
    ll w1=0,w2=0;
    for(int i=1;i<=n;++i)
    {
        if((k-a[i])%2==1) ++w1;
        w2+=(k-a[i])/2;
    }
    ll s=max(w1*2-1,w2*2);
    ll x=max((w2-w1)/3-1,0ll);
    w1+=x*2,w2-=x;
    if(w2>=0) s=min(s,max(w1*2-1,w2*2));
    w1+=2,w2-=1;
    if(w2>=0) s=min(s,max(w1*2-1,w2*2));
    w1+=2,w2-=1;
    if(w2>=0) s=min(s,max(w1*2-1,w2*2));
    return s;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        ll k=0;
        for(int i=1;i<=n;++i)
        {
            scanf("%lld",&a[i]);
            k=max(k,a[i]);
        }
        printf("%lld\n",min(solve(k),solve(k+1)));
    }
    return 0;
}