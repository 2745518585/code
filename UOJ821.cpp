#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll P=998244353;
int n,m,q,a[N],b[N],c[N];
ll jc[N],ivjc[N];
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
    return jc[a]*ivjc[a-b]%P*ivjc[b]%P;
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
    scanf("%d%d%*d",&n,&m);
    jc[0]=1;
    for(int i=1;i<=n+m;++i) jc[i]=jc[i-1]*i%P;
    for(int i=0;i<=n+m;++i) ivjc[i]=inv(jc[i]);
    int x=0;
    for(int i=1;i<=m;++i)
    {
        int z;
        scanf("%d",&z);
        if(z>=x) x=z,++a[z];
    }
    for(int i=1;i<=m;++i)
    {
        if(a[i]) ++b[a[i]];
    }
    for(int i=1;i<=m;++i)
    {
        if(b[i]) c[++q]=i;
    }
    ll s=0;
    for(int i=n;i>=1;--i)
    {
        ll z=1;
        for(int j=1;j<=q;++j) z=z*qpow(C(c[j]+i-1,i-1),b[c[j]])%P;
        if((n-i)%2==0) s=(s+C(n,i)*z%P)%P;
        else s=(s-C(n,i)*z%P)%P;
    }
    printf("%lld",(s%P+P)%P);
    return 0;
}