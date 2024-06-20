#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=3001;
const ll P=998244353;
int n,m,a1[N],a2[N];
ll f[N][N],g[N][N],h[N],jc[N],ivjc[N];
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
ll A(ll a,ll b)
{
    if(a<b) return 0;
    return jc[a]*ivjc[a-b]%P;
}
int main()
{
    scanf("%d%d",&n,&m);
    jc[0]=1;
    for(int i=1;i<=n;++i) jc[i]=jc[i-1]*i%P;
    ivjc[n]=inv(jc[n]);
    for(int i=n;i>=1;--i) ivjc[i-1]=ivjc[i]*i%P;
    for(int i=1;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        a1[i]=max(x-m,0);
        a2[i]=min(x+m,i);
    }
    f[0][0]=1;
    for(int i=1;i<=n;++i)
    {
        for(int j=0;j<=i;++j)
        {
            for(int k=a1[i-1];k<=a2[i-1];++k) g[j][k]=f[j][k]%P,f[j][k]=0;
        }
        for(int j=0;j<=n;++j) h[j]=0;
        for(int j=0;j<=i;++j)
        {
            for(int k=a1[i];k<=min(a2[i],j);++k)
            {
                f[j][k]+=f[j][k]+g[j][k]*j%P;
                if(j>0) f[j][k]+=g[j-1][k];
                if(k>0) f[j][k]+=h[min(k-1,a2[i-1])]*ivjc[j-k]%P;
            }
            for(int k=a1[i-1];k<=min(a2[i-1],j);++k)
            {
                h[k]=g[j][k]*jc[j-k]%P;
                if(k>a1[i-1]) h[k]=(h[k]+h[k-1])%P;
            }
        }
        for(int j=0;j<=i;++j)
        {
            for(int k=a1[i-1];k<=a2[i-1];++k) g[j][k]=0;
        }
    }
    ll s=0;
    for(int i=0;i<=n;++i)
    {
        for(int j=a1[n];j<=min(a2[n],i);++j)
        {
            s=(s+f[i][j]%P*A(n-j,i-j)%P)%P;
        }
    }
    printf("%lld\n",(s%P+P)%P);
    return 0;
}