#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=20000001;
const ll P=18888913;
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
ll C(ll a,ll b)
{
    if(a<b) return 0;
    if(a<P&&b<P) return jc[a]*ivjc[a-b]%P*ivjc[b]%P;
    return C(a/P,b/P)*C(a%P,b%P)%P;
}
int main()
{
    jc[0]=1;
    for(int i=1;i<=P-1;++i) jc[i]=jc[i-1]*i%P;
    ivjc[P-1]=inv(jc[P-1]);
    for(int i=P-1;i>=1;--i) ivjc[i-1]=ivjc[i]*i%P;
    int T;
    scanf("%d",&T);
    ll s=0;
    while(T--)
    {
        ll n,m;
        scanf("%lld%lld",&n,&m);
        if(m<n) continue;
        --n,--m;
        m-=n;
        ll w=((C(n+m+1,n)-1)*2+(C(n+m+1,n+1)-1)+C(n+m,n)+1)%P;
        s^=(w%P+P)%P;
    }
    printf("%lld",s);
    return 0;
}