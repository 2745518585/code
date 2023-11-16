#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=2000001;
const ll P=998244353;
int n,m,a[N],sp,p[N];
bool ip[N];
ll g[N],mu[N];
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
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        ++a[x];
        m=max(m,x);
    }
    for(int i=1;i<=m;++i)
    {
        for(int j=1;i*j<=m;++j) g[i]=(g[i]+(ll)j*a[i*j]%P)%P;
    }
    mu[1]=1;
    for(int i=2;i<=m;++i)
    {
        if(ip[i]==false) p[++sp]=i,mu[i]=-1;
        for(int j=1;j<=sp&&i*p[j]<=m;++j)
        {
            ip[i*p[j]]=true;
            if(i%p[j]==0) break;
            mu[i*p[j]]=-mu[i];
        }
    }
    ll s=0;
    for(int i=1;i<=m;++i)
    {
        for(int j=1;i*j<=m;++j)
        {
            s=(s+(ll)i*j%P*j%P*mu[j]%P*g[i*j]%P*g[i*j]%P)%P;
        }
    }
    for(int i=1;i<=m;++i) s=(s-(ll)i*a[i])%P;
    s=s*inv(2)%P;
    printf("%lld",(s%P+P)%P);
    return 0;
}