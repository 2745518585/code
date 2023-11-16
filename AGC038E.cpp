#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const ll P=998244353;
const int N=1001;
int n,m1,m2,a[N],b[N];
ll jc[N],ivjc[N],powb[N],f[N][N],g[N][N];
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
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d",&a[i],&b[i]);
    }
    jc[0]=1;
    for(int i=1;i<=400;++i) jc[i]=jc[i-1]*i%P;
    for(int i=0;i<=400;++i) ivjc[i]=inv(jc[i]);
    f[0][0]=-1;
    for(int i=1;i<=n;++i)
    {
        for(int j=0;j<=m1;++j)
        {
            for(int k=0;k<=m2;++k) g[j][k]=f[j][k];
        }
        powb[0]=1;
        for(int j=1;j<=b[i];++j) powb[j]=powb[j-1]*a[i]%P;
        for(int j=0;j<=m1;++j)
        {
            for(int k=0;k<=m2;++k)
            {
                for(int l=0;l<=b[i]-1;++l)
                {
                    f[j+a[i]][k+l]=(f[j+a[i]][k+l]-g[j][k]*powb[l]%P*ivjc[l]%P)%P;
                }
            }
        }
        m1+=a[i];
        m2+=b[i];
    }
    ll s=0;
    for(int i=0;i<=m1;++i)
    {
        for(int j=0;j<=m2;++j)
        {
            s=(s+f[i][j]*(m1*inv(i)%P)%P*jc[j]%P*inv(qpow(i,j))%P)%P;
        }
    }
    printf("%lld",(s%P+P)%P);
    return 0;
}