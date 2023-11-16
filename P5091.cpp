#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
ll a,n,P,k;
ll qpow(ll a,ll b)
{
    ll x=1,y=a;
    while(b)
    {
        if(b&1) x=x*y%P;
        y=y*y%P;
        b>>=1;
    }
    return x;
}
int main()
{
    scanf("%lld%lld",&a,&P);
    ll x=P;
    k=P;
    for(int i=2;i*i<=P;++i)
    {
        if(x%i==0)
        {
            k=k-k/i;
            while(x%i==0) x/=i;
        }
    }
    if(x>1) k=k-k/x;
    char c=getchar();
    while(c<'0'||c>'9') c=getchar();
    bool u=false;
    while(c>='0'&&c<='9')
    {
        n=n*10+c-'0';
        if(n>=k)
        {
            u=true;
            n%=k;
        }
        c=getchar();
    }
    if(u) n+=k;
    printf("%lld",qpow(a,n));
    return 0;
}