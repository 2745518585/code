#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=200001,M=601;
const ll P=1e9+7;
int n,m;
ll f[M][N],jc[N];
void init_jc(int x)
{
    jc[0]=1;
    for(int i=1;i<=x;++i) jc[i]=(jc[i-1]*i)%P;
}
void exgcd(ll a,ll b,ll &x,ll &y)
{
    if(b==0) x=1,y=0;
    else exgcd(b,a%b,y,x),y-=a/b*x;
}
ll inv(ll a)
{
    ll x,y;
    exgcd(a,P,x,y);
    x=(x%P+P)%P;
    return x;
}
ll C(ll a,ll b)
{
    if(b>a) return 0;
    return (jc[a]*inv(jc[a-b]*jc[b]%P))%P;
}
int main()
{
    init_jc(200000);
    scanf("%d%d",&n,&m);
    f[0][0]=1;
    for(int i=1;i*i<=m*2;++i)
    {
        for(int j=i;j<=m;++j)
        {
            f[i][j]=(f[i][j]+f[i][j-i]+f[i-1][j-i])%P;
            if(j>=n+1) f[i][j]=(f[i][j]-f[i-1][j-(n+1)])%P;
        }
    }
    ll s=C(n+m-1,n-1);
    for(int i=1;i<=m;++i)
    {
        ll w=0;
        for(int j=1;j<=n&&j*j<=m*2;++j)
        {
            if(j%2==1) w-=f[j][i];
            else w+=f[j][i];
        }
        s=(s+(w%P+P)%P*C(n+m-i-1,n-1)%P)%P;
    }
    printf("%lld",(s%P+P)%P);
    return 0;
}