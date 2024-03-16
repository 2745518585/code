#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=2000001;
const ll P=998244353;
int n,m,a[N],b[N];
ll jc[N],ivjc[N],f[N];
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
    return (jc[a]*ivjc[a-b]%P*ivjc[b]%P)%P;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        a[i]+=a[i-1];
    }
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&b[i]);
        b[i]+=b[i-1];
    }
    jc[0]=1;
    for(int i=1;i<=b[n];++i) jc[i]=jc[i-1]*i%P;
    ivjc[b[n]]=inv(jc[b[n]]);
    for(int i=b[n];i>=1;--i) ivjc[i-1]=ivjc[i]*i%P;
    for(int i=b[n];i>=0;--i)
    {
        f[i]=(f[i+1]+C(b[n],i))%P;
    }
    ll w=1;
    for(int i=1;i<=b[n];++i) w=w*2%P;
    w=inv(w);
    for(int i=1;i<=m;++i)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        int x=a[r]-a[l-1],y=a[n]-x,u=b[r]-b[l-1],v=b[n]-u;
        if(x+u<=y)
        {
            printf("0 ");
            continue;
        }
        printf("%lld ",f[max(v-(x-y)+1,0)]*w%P);
    }
    return 0;
}