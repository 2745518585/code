#include<cstdio>
using namespace std;
typedef long long ll;
ll a,b,p;
ll Pow(int x,int k)
{
    if(k==0) return 1;
    if(k==1) return x;
    ll t=Pow(x,k/2);
    if(k%2==0) return t*t%p;
    return t*t%p*x%p;
}
int main()
{
    scanf("%lld%lld%lld",&a,&b,&p);
    printf("%lld",Pow(a,b)%p);
    return 0;
}