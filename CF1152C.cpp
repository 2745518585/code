#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll a,b,k,s=1e18,q;
void check(ll k)
{
    ll x;
    if(a%k==0) x=0;
    else x=k-a%k;
    if(((a+x)*(b+x)/k)<s||(((a+x)*(b+x)/k)==s&&x<q))
    {
        s=(a+x)*(b+x)/k;
        q=x;
    }
}
int main()
{
    scanf("%lld%lld",&a,&b);
    k=abs(a-b);
    for(int i=1;i*i<=k;++i)
    {
        if(k%i==0)
        {
            check(i);
            check(k/i);
        }
    }
    printf("%lld\n",q);
    return 0;
}