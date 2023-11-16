#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=2501;
const ll P=1e9+7;
int n;
ll jc[N<<2],ivjc[N<<2],a[N<<1][N];
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
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        ++a[x+y][x];
    }
    jc[0]=1;
    for(int i=1;i<=8000;++i) jc[i]=jc[i-1]*i%P;
    for(int i=0;i<=8000;++i) ivjc[i]=inv(jc[i]);
    ll s=0;
    for(int i=4000;i>=1;--i)
    {
        for(int j=2000;j>=1;--j)
        {
            if(a[i][j]) s=(s-C((i-1)+(i-1),(j-1)+j)*a[i][j]%P)%P;
            a[i-1][j-1]=(a[i-1][j-1]+a[i][j])%P;
            a[i-1][j]=(a[i-1][j]+a[i][j])%P;
            a[i][j]=0;
        }
    }
    for(int i=-4000;i<=2000;++i)
    {
        int x1=max(-i,0),y1=max(i,0);
        if(!a[x1][y1]) continue;
        s=(s+C(x1+x1,y1+y1)*(a[x1][y1]*(a[x1][y1]-1)/2%P)%P)%P;
        for(int j=i+1;j<=2000;++j)
        {
            int x2=max(-j,0),y2=max(j,0);      
            if(a[x2][y2]) s=(s+C(x1+x2,y1+y2)*a[x1][y1]%P*a[x2][y2]%P)%P;
        }
    }
    printf("%lld",(s%P+P)%P);
    return 0;
}