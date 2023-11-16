#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1000001,M=5001;
const ll P=998244353;
int m,n,k,q,t;
ll f[M][M],a[N],b[N];
ll gcd(ll a,ll b)
{
    if(b==0) return a;
    return gcd(b,a%b);
}
void exgcd(ll a,ll b,ll &x,ll &y)
{
    if(b==0) x=1,y=0;
    else exgcd(b,a%b,y,x),y-=a/b*x;
}
ll sum(ll x,ll y)
{
    if(k%gcd(x,y)!=0) return 0;
    ll z1,z2,z=y/gcd(x,y);
    exgcd(x,y,z1,z2);
    z1*=(k/gcd(x,y));
    z1=(z1%z+z)%z;
    if(z1==0) z1+=z;
    ll s=0;
    for(int i=z1;x*i<=k;i+=z)
    {
        s=(s+a[i]*b[(k-x*i)/y]%P)%P;
    }
    return s;
}
int main()
{
    scanf("%d%d%d",&m,&n,&k);
    for(int i=1;i<=m;++i)
    {
        scanf("%lld",&a[i]);
    }
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&b[i]);
    }
    t=sqrt(k);
    for(int i=1;i<=t;++i)
    {
        for(int j=1;j<=t;++j) f[i][j]=sum(i,j);
    }
    scanf("%d",&q);
    for(int i=1;i<=q;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        if(x<=t&&y<=t) printf("%lld\n",f[x][y]);
        else printf("%lld\n",sum(x,y));
    }
    return 0;
}