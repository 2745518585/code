#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=200001;
int n;
ll m,a[N];
int main()
{
    scanf("%d%lld",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&a[i]);
        a[i]+=a[i-1];
    }
    a[n+1]=1e18;
    int t=1,s=0;
    while(t<=n)
    {
        ++s;
        t=upper_bound(a,a+n+2,a[t-1]+m)-a;
    }
    printf("%d",s);
    return 0;
}