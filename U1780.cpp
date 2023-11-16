#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m;
ll a[N],q;
int main()
{
    scanf("%d%d",&n,&m);
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
        int t=1,s=0;
        while(t<=n)
        {
            ++s;
            t=upper_bound(a,a+n+2,a[t-1]+z)-a;
        }
        if(s>m) l=z+1;
        else r=z;
    }
    printf("%lld",l);
    return 0;
}