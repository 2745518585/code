#pragma GCC optimize("O2")
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=61;
int m,n;
ll P,C[N][N],pow2[N],f[N][N][N][N],g1[N][N],g2[N][N];
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
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%lld",&m,&n,&P);
        C[0][0]=1;
        for(int i=1;i<=30;++i)
        {
            C[i][0]=1;
            for(int j=1;j<=30;++j)
            {
                C[i][j]=(C[i-1][j-1]+C[i-1][j])%P;
            }
        }
        pow2[0]=1;
        for(int i=1;i<=30;++i) pow2[i]=pow2[i-1]*2%P;
        for(int i=0;i<=30;++i)
        {
            for(int j=0;j<=30;++j)
            {
                g1[i][j]=qpow(inv(pow2[i]),j);
                g2[i][j]=qpow(1-inv(pow2[i])+P,j);
            }
        }
        memset(f,0,sizeof(f));
        f[1][0][1][1]=1;
        for(int i=1;i<=m;++i)
        {
            for(int j=0;j<=n-1;++j)
            {
                for(int p=1;p<=min(m,n)*2+1;++p)
                {
                    if(p&1)
                    {
                        for(int k=1;k<=i;++k)
                        {
                            f[i][j][k][p]%=P;
                            for(int l=1;l<=n-j-1;++l)
                            {
                                f[i][j+l][l][p+1]+=f[i][j][k][p]*g2[k][l]%P*C[n-j-1][l]%P*g1[k][n-j-l]%P;
                            }
                        }
                    }
                    else
                    {
                        for(int k=1;k<=j;++k)
                        {
                            f[i][j][k][p]%=P;
                            for(int l=1;l<=m-i;++l)
                            {
                                f[i+l][j][l][p+1]+=f[i][j][k][p]*g2[k][l]%P*C[m-i][l]%P*g1[k][m-i-l]%P;
                            }
                        }
                    }
                }
            }
        }
        ll s=0;
        for(int i=1;i<=m;++i)
        {
            for(int j=0;j<=n-1;++j)
            {
                for(int k=1;k<=i;++k)
                {
                    for(int l=1;l<=min(m,n)*2+1;l+=2)
                    {
                        s=(s+f[i][j][k][l]*l%P*(1-inv(pow2[k]))%P)%P;
                    }
                }
            }
        }
        printf("%lld\n",(s%P+P)%P);
    }
    return 0;
}