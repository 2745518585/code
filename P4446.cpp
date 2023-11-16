#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll a;
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%lld",&a);
        ll s=1;
        for(ll i=2;i*i*i<=a;++i)
        {
            while(a%(i*i*i)==0)
            {
                s*=i;
                a/=(i*i*i);
            }
            while(a%i==0) a/=i;
        }
        printf("%lld\n",s);
    }
    return 0;
}