#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll P=998244353;
int q;
ll a,b,f[N];
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
int main()
{
    scanf("%lld%lld",&a,&b);
    ll x=a;
    for(ll i=2;i*i<=a;++i)
    {
        if(x%i==0)
        {
            ++q;
            while(x%i==0) x/=i,++f[q];
        }
    }
    if(x>1) f[++q]=1;
    bool u=true;
    for(int i=1;i<=q;++i)
    {
        if(f[i]%2==1&&b%2==1) u=false;
    }
    if(b%2==0) u=false;
    ll w=b%P;
    for(int i=1;i<=q;++i)
    {
        w=w*(f[i]*(b%P)%P+1)%P;
    }
    if(u) --w;
    w=w*inv(2)%P;
    printf("%lld",(w%P+P)%P);
    return 0;
}