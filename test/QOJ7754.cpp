#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=2001,M=12;
const ll P=998244353;
int m,n,a[N],b[N];
ll jc[N],ivjc[N],c[N],d[N],f[1<<M][N],g[1<<M][N];
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
ll C(ll a,ll b)
{
    if(a<b) return 0;
    return jc[a]*ivjc[a-b]%P*ivjc[b]%P;
}
int main()
{
    scanf("%d%d",&m,&n);
    jc[0]=1;
    for(int i=1;i<=1000;++i) jc[i]=jc[i-1]*i%P;
    ivjc[1000]=inv(jc[1000]);
    for(int i=1000;i>=1;--i) ivjc[i-1]=ivjc[i]*i%P;
    for(int i=1;i<=1000;++i) c[i]=(c[i-1]+inv(i))%P;
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    int q=0,z=0;
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&b[i]);
        q+=b[i];
        d[i]=jc[a[i]]*ivjc[a[i]-b[i]]%P;
        if(b[i]==0) z|=(1<<(i-1));
    }
    g[z][0]=1;
    for(int s=0;s<(1<<n);++s)
    {
        int t1=0,t2=0;
        for(int i=1;i<=n;++i)
        {
            if(s&(1<<(i-1))) t1+=a[i]-b[i],t2+=b[i];
        }
        for(int i=1;i<=n;++i)
        {
            if(!(s&(1<<(i-1)))&&b[i])
            {
                ll w1=0,w2=0,w3=0;
                for(int j=0;j<=min(q,m-t1);++j)
                {
                    ll z=jc[m-j-t1]*d[i]%P*C(j-1-t2,b[i]-1)%P;
                    f[s|(1<<(i-1))][j]=(f[s|(1<<(i-1))][j]+z*w1%P+z*w2%P*t1%P-z*c[m-j-t1]%P*t1%P*w3%P)%P;
                    g[s|(1<<(i-1))][j]=(g[s|(1<<(i-1))][j]+z*w3%P)%P;
                    w1=(w1+ivjc[m-j-t1]*f[s][j]%P)%P;
                    w2=(w2+ivjc[m-j-t1]*g[s][j]%P*c[m-j-t1]%P)%P;
                    w3=(w3+ivjc[m-j-t1]*g[s][j]%P)%P;
                }
            }
        }
    }
    printf("%lld",((f[(1<<n)-1][q]+q)%P+P)%P);
    return 0;
}