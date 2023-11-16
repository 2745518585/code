#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=2000001;
const ll P=1e9+7;
int n,m;
ll a[N],b[N],c[N];
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
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&a[i]);
        b[i]=(b[i-1]+a[i])%P;
        c[i]=(c[i-1]+a[i]*a[i]%P)%P;
    }
    for(int i=1;i<=m;++i)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        printf("%lld\n",(((b[r]-b[l-1])*(b[r]-b[l-1])%P-(c[r]-c[l-1]))%P*inv(2)%P+P)%P);
    }
    return 0;
}