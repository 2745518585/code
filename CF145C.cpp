#include<cstdio>
#include<algorithm>
#include<map>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll P=1e9+7;
int n,m,k,q,a[N];
ll jc[N],b[N],f[N];
map<int,int> Map;
void init_jc(int x)
{
    jc[0]=1;
    for(int i=1;i<=x;++i) jc[i]=(jc[i-1]*i)%P;
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
ll C(ll a,ll b)
{
    if(b>a) return 0;
    return (jc[a]*inv(jc[a-b]*jc[b]%P))%P;
}
bool check(int x)
{
    while(x!=0)
    {
        if(x%10!=4&&x%10!=7) return false;
        x/=10;
    }
    return true;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        if(!check(x)) ++k;
        else if(Map.count(x)) ++b[Map[x]];
        else Map[x]=++q,b[q]=1;
    }
    f[0]=1;
    for(int i=1;i<=q;++i)
    {
        for(int j=n;j>=1;--j) f[j]=(f[j]+f[j-1]*b[i])%P;
    }
    init_jc(n);
    ll s=0;
    for(int i=0;i<=n;++i)
    {
        s=(s+f[i]*C(k,m-i)%P)%P;
    }
    printf("%lld",s);
    return 0;
}