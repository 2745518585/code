#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=3000001;
const ll P=998244353;
ll jc[N],ivjc[N],pw[N],f[N],g[N];
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
    if(a<b) return 0;
    return jc[a]*ivjc[a-b]%P;
}
ll C(ll a,ll b)
{
    if(a<b) return 0;
    return jc[a]*ivjc[a-b]%P*ivjc[b]%P;
}
int n,m,k;
int main()
{
    jc[0]=1;
    for(int i=1;i<=2000000;++i) jc[i]=jc[i-1]*i%P;
    ivjc[2000000]=inv(jc[2000000]);
    for(int i=2000000;i>=1;--i) ivjc[i-1]=ivjc[i]*i%P;
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d",&n,&m,&k);
        if(k>=m)
        {
            ll w=1;
            for(int i=1;i<=n;++i) w=w*m%P;
            printf("%lld\n",w);
            continue;
        }
        pw[0]=1;
        for(int i=1;i<=n;++i) pw[i]=pw[i-1]*(m-1)%P;
        for(int i=0;i<=n;++i) f[i]=0;
        for(int i=k-n;i<=k+n;i+=2)
        {
            // printf("%d:\n",i);
            auto add=[&](int x,ll k)
            {
                if(x<0) x=(x%(m+1)+(m+1))%(m+1);
                // printf("%d %lld\n",x,k);
                if(x<=n) f[x]=(f[x]+k)%P;
            };
            if(i>=0)
            {
                add((i-k+n)/2,pw[(i-k+n)/2]);
                add((i+2+k+n)/2,-pw[(i-k+n)/2]);
            }
            else
            {
                add((-i-2-k+n)/2+(m+1),pw[(i-k+n)/2]);
                add((-i+k+n)/2+(m+1),-pw[(i-k+n)/2]);
            }
        }
        for(int i=m+1;i<=n;++i) f[i]=(f[i]+f[i-(m+1)])%P;
        // for(int i=0;i<=n;++i) printf("%lld ",f[i]);printf("\n");
        ll s=0;
        for(int i=0;i<=n;++i)
        {
            s=(s+C(n,i)*f[i]%P)%P;
        }
        printf("%lld\n",(s%P+P)%P);
    }
    return 0;
}