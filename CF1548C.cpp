#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=6000001;
const ll P=1e9+7;
int n,m;
ll jc[N],ivjc[N],f[N][3];
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
int main()
{
    scanf("%d%d",&n,&m);
    jc[0]=1;
    for(int i=1;i<=n*3;++i) jc[i]=(jc[i-1]*i)%P;
    ivjc[n*3]=inv(jc[n*3]);
    for(int i=n*3-1;i>=0;--i) ivjc[i]=(ivjc[i+1]*(i+1))%P;
    f[0][0]=f[0][1]=f[0][2]=n;
    ll w=inv(3);
    for(int i=1;i<=n*3;++i)
    {
        f[i][0]=(C(n*3,i+1)-2*f[i-1][0]-f[i-1][1])%P*w%P;
        f[i][1]=(f[i-1][0]+f[i][0])%P;
        f[i][2]=(f[i-1][1]+f[i][1])%P;
    }
    for(int i=1;i<=m;++i)
    {
        int x;
        scanf("%d",&x);
        printf("%lld\n",((C(n*3,x)+f[x][0])%P+P)%P);
    }
    return 0;
}