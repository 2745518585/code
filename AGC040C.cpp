#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long ll;
const int N=20000001;
const ll P=998244353;
int n;
ll jc[N],ivjc[N];
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
ll C(ll a,ll b)
{
    if(a<b) return 0;
    return jc[a]*ivjc[b]%P*ivjc[a-b]%P;
}
int main()
{
    scanf("%d",&n);
    jc[0]=1;
    for(int i=1;i<=n;++i) jc[i]=jc[i-1]*i%P;
    ivjc[n]=qpow(jc[n],P-2);
    for(int i=n-1;i>=0;--i) ivjc[i]=ivjc[i+1]*(i+1)%P;
    ll s=qpow(3,n);
    for(int i=n/2+1;i<=n;++i)
    {
        s=(s-C(n,i)*qpow(2,n-i)%P*2%P)%P;
    }
    printf("%lld",(s%P+P)%P);
    return 0;
}