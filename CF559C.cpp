#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=3000001;
const ll P=1e9+7;
int m,n,k;
ll jc[N],f[N];
struct str
{
    int x,y;
}a[N];
bool cmp(str a,str b)
{
    if(a.x!=b.x) return a.x<b.x;
    return a.y<b.y;
}
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
ll A(ll a,ll b)
{
    if(b>a) return 0;
    return (jc[a]*inv(jc[a-b]))%P;
}
ll C(ll a,ll b)
{
    if(b>a) return 0;
    return (jc[a]*inv(jc[a-b]*jc[b]%P))%P;
}
int main()
{
    scanf("%d%d%d",&m,&n,&k);
    init_jc(m+n);
    --m,--n;
    for(int i=1;i<=k;++i)
    {
        scanf("%d%d",&a[i].x,&a[i].y);
        --a[i].x,--a[i].y;
    }
    sort(a+1,a+k+1,cmp);
    for(int i=1;i<=k;++i)
    {
        f[i]=C(a[i].x+a[i].y,a[i].x);
        for(int j=1;j<=i-1;++j)
        {
            if(a[j].x<=a[i].x&&a[j].y<=a[i].y) f[i]=(f[i]-f[j]*C(a[i].x+a[i].y-(a[j].x+a[j].y),a[i].x-a[j].x)%P)%P;
        }
    }
    ll s=C(m+n,m);
    for(int i=1;i<=k;++i)
    {
        s=(s-f[i]*C(m+n-(a[i].x+a[i].y),m-a[i].x)%P)%P;
    }
    printf("%lld",(s%P+P)%P);
    return 0;
}