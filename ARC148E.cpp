#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll P=998244353;
int n,k,a[N];
ll jc[N];
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
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    sort(a+1,a+n+1);
    jc[0]=1;
    for(int i=1;i<=n;++i) jc[i]=jc[i-1]*i%P;
    ll s=1;
    int l=1,r=n;
    while(l<=r)
    {
        while(l<r&&a[l]+a[r]>=k)
        {
            s=s*(n-r-l+2)%P;
            --r;
        }
        s=s*(n-r-l+2)%P;
        ++l;
    }
    int x=0;
    a[n+1]=2e9;
    for(int i=1;i<=n;++i)
    {
        ++x;
        if(a[i]!=a[i+1])
        {
            s=s*inv(jc[x])%P;
            x=0;
        }
    }
    s=s*inv(jc[x])%P;
    printf("%lld",s);
    return 0;
}