#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll P=998244353;
int n,m,k;
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
    if(a<b) return 0;
    return jc[a]*ivjc[a-b]%P*ivjc[b]%P;
}
ll solve(int n,int m)
{
    if(n-m==1) return (m<=k)*n;
    ll s=0;
    for(int i=0;i<=k;++i)
    {
        ll w=0;
        for(int j=0;j<=(m-i)/(k+1);++j)
        {
            w=(w+(j&1?-1:1)*C(n-m-1,j)%P*C(m-i-j*(k+1)+(n-m-2),n-m-2)%P)%P;
        }
        s=(s+w*(i+1)%P)%P;
    }
    return s;
}
int phi(int x)
{
    int s=x;
    for(int i=2;i*i<=x;++i)
    {
        if(x%i==0)
        {
            s=s/i*(i-1);
            while(x%i==0) x/=i;
        }
    }
    if(x>1) s=s/x*(x-1);
    return s;
}
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    if(n==m)
    {
        printf("0");
        return 0;
    }
    jc[0]=1;
    for(int i=1;i<=n;++i) jc[i]=jc[i-1]*i%P;
    ivjc[n]=inv(jc[n]);
    for(int i=n;i>=1;--i) ivjc[i-1]=ivjc[i]*i%P;
    ll s=0;
    for(int i=1;i<=n;++i)
    {
        if(n%i!=0||m%i!=0) continue;
        s=(s+solve(n/i,m/i)*phi(i)%P)%P;
    }
    printf("%lld",(s*inv(n)%P+P)%P);
    return 0;
}