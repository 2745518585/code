#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll P=104857601;
int n,pri[N],spri,phi[N];
bool ipri[N];
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
int main()
{
    scanf("%d",&n);
    phi[1]=1;
    for(int i=2;i<=n;++i)
    {
        if(ipri[i]==false) pri[++spri]=i,phi[i]=i-1;
        for(int j=1;j<=spri&&i*pri[j]<=n;++j)
        {
            ipri[i*pri[j]]=true;
            if(i%pri[j]==0)
            {
                phi[i*pri[j]]=phi[i]*pri[j];
                break;
            }
            phi[i*pri[j]]=phi[i]*phi[pri[j]];
        }
    }
    for(int i=1;i<=n;++i) phi[i]=(phi[i]+phi[i-1])%(P-1);
    ll s=1;
    for(int i=1;i<=n;++i)
    {
        s=(s*qpow(i,(phi[n/i]*2-1+(P-1))%(P-1)))%P;
    }
    ll w=1;
    for(int i=1;i<=n;++i) w=(w*i)%P;
    printf("%lld",qpow(w,n*2)*inv(s*s%P)%P);
    return 0;
}