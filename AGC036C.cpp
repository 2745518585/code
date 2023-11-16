#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=3000001;
const ll P=998244353;
int n,m;
ll jc[N];
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
    if(b>a) return 0;
    return (jc[a]*inv(jc[a-b]*jc[b]%P))%P;
}
int main()
{
    scanf("%d%d",&n,&m);
    jc[0]=1;
    for(int i=1;i<=3000000;++i) jc[i]=jc[i-1]*i%P;
    ll s=0;
    for(int i=0;i<=min(m,n);++i)
    {
        if((m*3-i)%2==1) continue;
        s=(s+(C((m*3-i)/2+n-1,n-1)-C((m*3-i)/2+n-1-(m+1),n-1)*n%P-C((m*3-i)/2-m+n-2,n-2)*i%P)*C(n,i)%P)%P;
    }
    printf("%lld",(s%P+P)%P);
    return 0;
}