#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=2000001;
const ll P=998244353;
int n,m;
ll f[N];
char a[N],b[N];
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
        scanf("%d%s%s",&n,a+1,b+1);
        m=0;
        for(int i=1;i<=n;++i) m+=a[i]!=b[i];
        f[n]=1;
        for(int i=n-1;i>=1;--i)
        {
            f[i]=(n+(n-i)*f[i+1]%P)*inv(i)%P;
        }
        ll s=0;
        for(int i=1;i<=m;++i) s=(s+f[i])%P;
        printf("%lld\n",(s%P+P)%P);
    }
    return 0;
}