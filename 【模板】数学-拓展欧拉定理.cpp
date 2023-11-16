#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=20000001;
ll a,b,P;
char c[N];
ll phi(ll x)
{
    ll z=x,s=x;
    for(ll i=2;i*i<=x;++i)
    {
        while(z%i==0)
        {
            s=s/i*(i-1);
            while(z%i==0) z/=i;
        }
    }
    if(z>1) s=s/z*(z-1);
    return s;
}
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
    scanf("%lld%lld%s",&a,&P,c+1);
    ll k=phi(P);
    bool u=false;
    for(int i=1;c[i];++i)
    {
        b=b*10+c[i]-'0';
        if(b>=k) u=true;
        b%=k;
    }
    if(u==false) printf("%lld",qpow(a,b));
    else printf("%lld",qpow(a,b%k+k));
    return 0;
}