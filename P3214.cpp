#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll P=1e8+7;
ll n,m,t,f[N],A[N];
ll qpow(ll a,ll b)
{
    ll x=1,y=a;
    while(b!=0)
    {
        if(b&1) x=(x*y)%P;
        y=(y*y)%P;
        b>>=1;
    }
    return x;
}
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
ll jc(int x)
{
    ll s=1;
    for(int i=1;i<=x;++i) s=(s*i)%P;
    return s;
}
int main()
{
    scanf("%lld%lld",&n,&m);
    t=qpow(2ll,n)-1;
    A[0]=1;
    for(int i=1;i<=m;++i)
    {
        A[i]=(A[i-1]*(t-i+1)%P+P)%P;
    }
    f[0]=1;
    f[1]=0;
    for(int i=2;i<=m;++i)
    {
        f[i]=(A[i-1]-f[i-1]-f[i-2]*(i-1)%P*(t-i+2)%P)%P;
    }
    printf("%lld",(f[m]*inv(jc(m))%P+P)%P);
    return 0;
}