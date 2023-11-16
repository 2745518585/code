#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2001;
ll n,x,P,m,a[N],b[N],S[N][N],f[N];
void init()
{
    S[0][0]=1;
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=m;++j)
        {
            S[i][j]=(S[i-1][j-1]+j*S[i-1][j]%P)%P;
        }
    }
}
ll qpow(ll a,ll b)
{
    ll x=1,y=a;
    while(b)
    {
        if(b&1) x=x*y%P;
        y=y*y%P;
        b>>=1;
    }
    return x;
}
int main()
{
    scanf("%lld%lld%lld%lld",&n,&x,&P,&m);
    for(int i=0;i<=m;++i)
    {
        scanf("%lld",&a[i]);
    }
    init();
    for(int i=0;i<=m;++i)
    {
        for(int j=i;j<=m;++j)
        {
            b[i]=(b[i]+S[j][i]*a[j]%P)%P;
        }
    }
    ll w=1,s=0;
    for(int i=0;i<=m;++i)
    {
        if(i>=1) w=w*(n-i+1)%P;
        s=(s+b[i]*w%P*qpow(x,i)%P*qpow(x+1,n-i)%P)%P;
    }
    printf("%lld",s);
    return 0;
}