#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll P=1e9+7;
int n,m,a[N];
ll q,f[N];
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
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        m=max(m,a[i]);
        q+=a[i];
    }
    f[1]=(q-1)*(q-1)%P*inv(q)%P;
    for(int i=2;i<=m;++i)
    {
        f[i]=(f[i-1]*2-f[i-2]-(q-1)*inv(q-i+1)%P)%P;
    }
    ll s=0;
    for(int i=1;i<=n;++i) s=(s+f[a[i]])%P;
    printf("%lld",(s%P+P)%P);
    return 0;
}