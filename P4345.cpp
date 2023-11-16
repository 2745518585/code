#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const ll P=2333;
ll jc[P+1],c[P+1][P+1],f[P+1][P+1];
void init_jc(int x)
{
    jc[0]=1;
    for(int i=1;i<=x;++i)
    {
        jc[i]=(jc[i-1]*i)%P;
    }
}
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
ll C0(ll a,ll b)
{
    if(a<b) return 0;
    return jc[a]*inv(jc[a-b]*jc[b]%P)%P;
}
ll C(ll a,ll b)
{
    if(b==0) return 1;
    return C(a/P,b/P)*C0(a%P,b%P)%P;
}
ll solve(ll a,ll b)
{
    if(a==0) return 1;
    if(b<0) return 0;
    if(b==0) return 1;
    if(a<P&&b<P) return f[a][b];
    return solve(a/P,b/P-1)*solve(a%P,P-1)%P+C(a/P,b/P)*solve(a%P,b%P)%P;
}
int main()
{
    init_jc(P-1);
    for(int i=0;i<P;++i)
    {
        for(int j=0;j<P;++j)
        {
            c[i][j]=C(i,j);
            f[i][j]=(f[i][j-1]+c[i][j])%P;
        }
    }
    int T;
    scanf("%d",&T);
    while(T--)
    {
        ll a,b;
        scanf("%lld%lld",&a,&b);
        printf("%lld\n",solve(a,b)%P);
    }
    return 0;
}