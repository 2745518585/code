#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=601;
const ll P=998244353;
int n,a[N];
ll pw[N],jc[N],ivjc[N],f[N][N][N];
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
ll A(ll a,ll b)
{
    if(b>a) return 0;
    return (jc[a]*ivjc[a-b]%P)%P;
}
ll C(ll a,ll b)
{
    if(b>a) return 0;
    return (jc[a]*ivjc[a-b]%P*ivjc[b]%P)%P;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        ++a[x];
    }
    for(int i=n;i>=1;--i) a[i]+=a[i+1];
    jc[0]=1;
    for(int i=1;i<=n;++i) jc[i]=jc[i-1]*i%P;
    ivjc[n]=inv(jc[n]);
    for(int i=n;i>=1;--i) ivjc[i-1]=ivjc[i]*i%P;
    f[n+1][0][0]=1;
    for(int i=n;i>=1;--i)
    {
        pw[0]=1;
        for(int j=1;j<=a[i];++j) pw[j]=pw[j-1]*ivjc[i]%P;
        for(int j=0;(i+1)*j<=a[i+1];++j)
        {
            for(int k=(i+1)*j;k<=a[i+1];++k)
            {
                for(int l=0;j+l<=a[i]&&k+i*l<=a[i];++l)
                {
                    f[i][j+l][k+i*l]=(f[i][j+l][k+i*l]+f[i+1][j][k]*C(a[i]-j,l)%P*(jc[a[i]-k]*pw[l]%P*ivjc[a[i]-k-i*l]%P)%P)%P;
                }
            }
        }
    }
    ll s=0;
    for(int i=1;i<=n;++i)
    {
        s=(s+f[1][i][n])%P;
    }
    printf("%lld",s);
    return 0;
}