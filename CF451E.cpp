#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1001;
const ll P=1e9+7;
int n;
ll m,f[N];
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
ll C(ll a,ll b)
{
    if(a<b) return 0;
    ll s=1;
    for(ll i=a-b+1;i<=a;++i) s=s*(i%P)%P;
    for(ll i=1;i<=b;++i) s=s*inv(i%P)%P;
    return s;
}
int sum(int x)
{
    int s=0;
    while(x) x-=x&-x,++s;
    return s;
}
int main()
{
    scanf("%d%lld",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&f[i]);
    }
    ll s=0;
    for(int i=0;i<=(1<<n)-1;++i)
    {
        ll q=m;
        for(int j=1;j<=n;++j)
        {
            if(i&(1<<(j-1))) q-=f[j]+1;
        }
        if(sum(i)%2==0) s+=C(q+n-1,n-1);
        else s-=C(q+n-1,n-1);
    }
    printf("%lld",(s%P+P)%P);
    return 0;
}