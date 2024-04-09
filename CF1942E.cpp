#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=2000001;
const ll P=998244353;
int n,m;
ll jc[N],ivjc[N];
void exgcd(ll a,ll b,ll &x,ll &y)
{
    if(b==0) x=1,y=0;
    else exgcd(b,a%b,y,x),y-=a/b*x;
}
ll inv(ll a)
{
    ll x,y;
    exgcd(a,P,x,y);
    x=(x%P+P)%P;
    return x;
}
ll A(ll a,ll b)
{
    if(a<b) return 0;
    return jc[a]*ivjc[a-b]%P;
}
ll C(ll a,ll b)
{
    if(a<b) return 0;
    return jc[a]*ivjc[a-b]%P*ivjc[b]%P;
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
    jc[0]=1;
    for(int i=1;i<=2000000;++i) jc[i]=jc[i-1]*i%P;
    ivjc[2000000]=inv(jc[2000000]);
    for(int i=2000000;i>=1;--i) ivjc[i-1]=ivjc[i]*i%P;
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&m,&n);
        ll s=C(m,n*2);
        for(int i=0;i<=m-2*n;i+=2)
        {
            s-=C(m-n-i,n)*C(i/2+n-1,n-1)%P;
        }
        printf("%lld\n",(s*2%P+P)%P);
    }
    return 0;
}