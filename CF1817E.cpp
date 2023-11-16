#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll P=1e9+7;
int n,a[N];
ll b[N],c[N];
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
void check(int x)
{
    for(int i=0;i<=n;++i) c[i]=0;
    for(int i=1;i<=x-1;++i) c[i]-=a[i];
    for(int i=x+2;i<=n;++i) c[n-i+1]+=a[i];
    c[x-1]-=a[x];
    c[n-x-1]+=a[x+1];
    for(int i=n;i>=1;--i)
    {
        c[i-1]+=c[i]/2;
        c[i]%=2;
        if(c[i]<0) --c[i-1],c[i]+=2;
    }
    bool u=false;
    for(int i=0;i<=n;++i)
    {
        if(b[i]!=c[i])
        {
            if(b[i]<c[i]) u=true;
            break;
        }
    }
    if(u)
    {
        for(int i=0;i<=n;++i) b[i]=c[i];
    }
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
        }
        sort(a+1,a+n+1);
        for(int i=0;i<=n;++i) b[i]=0;
        for(int i=max(n/2-40,1);i<=min(n/2+40,n);++i) check(i);
        int p=0;
        for(int i=1;i<=n-1;++i)
        {
            if(a[i]!=a[i+1])
            {
                ++p;
                if(p<=40) check(i);
            }
        }
        p=0;
        for(int i=n-1;i>=1;--i)
        {
            if(a[i]!=a[i+1])
            {
                ++p;
                if(p<=40) check(i);
            }
        }
        ll s=0,w=1;
        for(int i=0;i<=n;++i)
        {
            s=(s+b[i]%P*w%P)%P;
            w=w*inv(2)%P;
        }
        printf("%lld\n",s);
    }
    return 0;
}