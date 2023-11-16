#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=3000001;
const ll P=1e9+7;
int n,m;
ll a[N],b[N],a2[N],f[N],g[N];
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
        a2[i]=(a2[i-1]+a[i])%P;
    }
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&b[i]);
    }
    ll w=0;
    for(int i=1;i<=n;++i)
    {
        f[i]=(w*inv(a2[i-1])%P+b[i])%P;
        w=(w+a[i]*(f[i]+b[i])%P)%P;
    }
    w=0;
    for(int i=1;i<=n;++i)
    {
        g[i]=(w+f[i]*a[i]%P)*inv(a2[i])%P;
        w=(w+g[i]*a[i]%P)%P;
    }
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        if(x==y)
        {
            printf("0\n");
            continue;
        }
        if(x>y) swap(x,y);
        printf("%lld\n",((f[x]+f[y]-2*g[x])%P+P)%P);
    }
    return 0;
}