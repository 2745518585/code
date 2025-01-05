#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const ll P=998244353;
const int N=1000001;
int n;
ll a[N],b[N],c[N];
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
void FWT_or(ll *a,int u)
{
    for(int k=1;k*2<=n;k<<=1)
    {
        for(int i=0;i<n;i+=k*2)
        {
            for(int j=0;j<k;++j) a[i+j+k]=(a[i+j+k]+a[i+j]*u)%P;
        }
    }
}
void FWT_and(ll *a,int u)
{
    for(int k=1;k*2<=n;k<<=1)
    {
        for(int i=0;i<n;i+=k*2)
        {
            for(int j=0;j<k;++j) a[i+j]=(a[i+j]+a[i+j+k]*u)%P;
        }
    }
}
void FWT_xor(ll *a,int u)
{
    for(int k=1;k*2<=n;k<<=1)
    {
        for(int i=0;i<n;i+=k*2)
        {
            for(int j=0;j<k;++j)
            {
                a[i+j]=a[i+j]+a[i+j+k];
                a[i+j+k]=a[i+j]-a[i+j+k]*2;
                a[i+j]=a[i+j]*u%P,a[i+j+k]=a[i+j+k]*u%P;
            }
        }
    }
}
void solve(ll *_a,ll *_b,ll *c,int u,auto func)
{
    static ll a[N],b[N];
    for(int i=0;i<=n-1;++i) a[i]=_a[i],b[i]=_b[i];
    func(a,1),func(b,1);
    for(int i=0;i<=n-1;++i) c[i]=a[i]*b[i]%P;
    func(c,u);
}
int main()
{
    scanf("%d",&n);
    n=(1<<n);
    for(int i=0;i<=n-1;++i)
    {
        scanf("%lld",&a[i]);
    }
    for(int i=0;i<=n-1;++i)
    {
        scanf("%lld",&b[i]);
    }
    solve(a,b,c,-1,FWT_or);
    for(int i=0;i<=n-1;++i) printf("%lld ",(c[i]%P+P)%P);
    printf("\n");
    solve(a,b,c,-1,FWT_and);
    for(int i=0;i<=n-1;++i) printf("%lld ",(c[i]%P+P)%P);
    printf("\n");
    solve(a,b,c,inv(2),FWT_xor);
    for(int i=0;i<=n-1;++i) printf("%lld ",(c[i]%P+P)%P);
    printf("\n");
    return 0;
}