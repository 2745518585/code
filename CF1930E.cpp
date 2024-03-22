#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=5000001;
const ll P=998244353;
int n;
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
    if(b>a) return 0;
    return (jc[a]*ivjc[a-b]%P*ivjc[b]%P)%P;
}
int main()
{
    jc[0]=1;
    for(int i=1;i<=5000000;++i) jc[i]=jc[i-1]*i%P;
    ivjc[5000000]=inv(jc[5000000]);
    for(int i=5000000;i>=1;--i) ivjc[i-1]=ivjc[i]*i%P;
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=(n-1)/2;++i)
        {
            ll s=1;
            for(int j=i*2;j<=n;j+=i*2)
            {
                s=(s+C(n,j)-C(i*2-1+n-j,i*2-1))%P;
            }
            printf("%lld ",(s%P+P)%P);
        }
        printf("\n");
    }
    return 0;
}