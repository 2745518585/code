#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=100001;
const ll M=1000000000;
int n,m;
ll a[N];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&a[i]);
    }
    sort(a+1,a+n+1);
    a[n+1]=1e18;
    ll l=0,r=M;
    while(l<r)
    {
        ll z=l+r+1>>1;
        int t=1,s=0;
        while(t<=n)
        {
            ++s;
            t=lower_bound(a,a+n+2,a[t]+z)-a;
        }
        if(s>=m) l=z;
        else r=z-1;
    }
    printf("%lld",l);
    return 0;
}