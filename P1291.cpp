#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
ll a=0,b=1,c=0;
ll gcd(ll a,ll b)
{
    if(b==0) return a;
    return gcd(b,a%b);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        ll x=n,y=i,k=b/gcd(b,y)*y;
        a*=k/b;
        x*=k/y;
        b=k;
        c+=(a+x)/k;
        a=(a+x)%k;
        k=gcd(a,b);
        a/=k;
        b/=k;
    }
    if(a==0)
    {
        printf("%lld",c);
        return 0;
    }
    ll x=c,l=0;
    while(x!=0)
    {
        x/=10;
        ++l;
    }
    for(int i=1;i<=l;++i) printf(" ");
    printf("%lld\n%lld",a,c);
    x=b;
    int m=0;
    while(x!=0)
    {
        x/=10;
        ++m;
    }
    for(int i=1;i<=m;++i) printf("-");
    printf("\n");
    for(int i=1;i<=l;++i) printf(" ");
    printf("%lld",b);
    return 0;
}