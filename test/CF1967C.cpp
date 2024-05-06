#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001,M=31;
const ll P=998244353;
int n,g[N];
ll k,a[N],b[M];
void exgcd(ll a,ll b,ll &x,ll &y)
{
    if(b==0) x=1,y=0;
    else exgcd(b,a%b,y,x),y-=a/b*x;
}
ll inv(ll a)
{
    a=(a%P+P)%P;
    ll x,y;
    exgcd(a,P,x,y);
    x=(x%P+P)%P;
    return x;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%lld",&n,&k);
        for(int i=1;i<=n;++i)
        {
            scanf("%lld",&a[i]);
        }
        for(int i=0;i<=20;++i)
        {
            b[i]=1;
            for(int j=1;j<=i;++j) b[i]=b[i]*j%P;
            b[i]=inv(b[i]);
            for(ll j=k;j<=k+i-1;++j) b[i]=b[i]*j%P;
        }
        for(int i=1;i<=n;++i)
        {
            int x=i;
            g[i]=0;
            while(x) x^=x&-x,++g[i];
        }
        for(int i=1;i<=n;++i)
        {
            for(int j=(i^(i&-i))+1;j<=i-1;++j)
            {
                a[i]=(a[i]-a[j]*b[g[i-j]]%P)%P;
            }
        }
        for(int i=1;i<=n;++i)
        {
            printf("%lld ",(a[i]%P+P)%P);
        }
        printf("\n");
    }
    return 0;
}