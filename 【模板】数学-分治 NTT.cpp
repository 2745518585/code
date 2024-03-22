#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=3000001;
const ll P=998244353;
int n,m;
ll a[N],b[N];
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
    return (x%P+P)%P;
}
ll qpow(ll x,ll y)
{
    ll a=1,b=x;
    while(y!=0)
    {
        if(y&1) a=a*b%P;
        b=b*b%P;
        y>>=1;
    }
    return a;
}
void NTT(int n,ll *a,int u)
{
    int x=0;
    static int d[N];
    while((1<<x)<n) ++x;
    for(int i=0;i<n;++i)
    {
        d[i]=(d[i>>1]>>1)|((i&1)<<(x-1));
    }
    for(int i=0;i<n;++i)
    {
        if(i<d[i]) swap(a[i],a[d[i]]);
    }
    for(int i=1;i<n;i<<=1)
    {
        int t=qpow(3,(P-1)/(i*2));
        if(u==-1) t=inv(t);
        for(int j=0;j<n;j+=i*2)
        {
            ll w=1;
            for(int k=j;k<i+j;++k)
            {
                ll q=w*a[k+i]%P;
                a[k+i]=(a[k]-q)%P;
                a[k]=(a[k]+q)%P;
                w=w*t%P;
            }
        }
    }
}
void mul(int n,ll *a,ll *b)
{
    NTT(n,a,1);
    NTT(n,b,1);
    for(int i=0;i<=n;++i) a[i]=a[i]*b[i]%P;
    NTT(n,a,-1);
    for(int i=0;i<=n;++i)
    {
        a[i]=a[i]*inv(n)%P;
    }
}
void solve(int l,int r)
{
    if(l==r) return;
    int z=l+r>>1;
    solve(l,z);
    int x=0;
    while((1<<x)<=r-l+1) ++x;
    static ll pa[N],pb[N];
    for(int i=0;i<=(1<<x);++i) pa[i]=pb[i]=0;
    for(int i=l;i<=z;++i) pa[i-l]=a[i];
    for(int i=0;i<=r-l+1;++i) pb[i]=b[i];
    mul(1<<x,pa,pb);
    for(int i=z+1;i<=r;++i) a[i]=(a[i]+pa[i-l])%P;
    solve(z+1,r);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n-1;++i) scanf("%lld",&b[i]);
    a[0]=1;
    solve(0,n-1);
    for(int i=0;i<=n-1;++i)
    {
        printf("%lld ",(a[i]%P+P)%P);
    }
    return 0;
}