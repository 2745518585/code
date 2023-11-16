#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        ll n;
        scanf("%lld",&n);
        ll s=0,l=1,r;
        while(l<=n)
        {
            r=n/(n/l);
            s+=(ll)(r-l+1)*(n/l);
            l=r+1;
        }
        printf("%lld\n",s);
    }
    return 0;
}