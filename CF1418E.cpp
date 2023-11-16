#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll P=998244353;
int n,m,a[N];
ll b[N];
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
    return (x%P+P)%P;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    sort(a+1,a+n+1);
    for(int i=1;i<=n;++i) b[i]=(b[i-1]+a[i])%P;
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        y=n-(lower_bound(a+1,a+n+1,y)-a-1);
        if(y<x)
        {
            printf("0\n");
            continue;
        }
        ll s=(b[n]-b[n-y])*((y-x)*inv(y)%P)%P+b[n-y]*((y-x+1)*inv(y+1)%P)%P;
        printf("%lld\n",(s%P+P)%P);
    }
    return 0;
}