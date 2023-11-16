#include<cstdio>
#include<algorithm>
#include<set>
using namespace std;
typedef long long ll;
const int N=1001;
int n;
ll a[N],b[N],d[N][N],f[N],T[N];
multiset<ll> Set;
ll find(ll x)
{
    set<ll>::iterator p=Set.lower_bound(x);
    ll s=5e18;
    if(p!=Set.end()) s=min(s,abs((*p)-x));
    if(p!=Set.begin())
    {
        --p;
        s=min(s,abs((*p)-x));
    }
    return s;
}
void add(int x,ll k)
{
    while(x>=1)
    {
        T[x]=min(T[x],k);
        x-=(x&-x);
    }
}
ll sum(int x)
{
    ll s=5e18;
    while(x<=n)
    {
        s=min(s,T[x]);
        x+=(x&-x);
    }
    return s;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&a[i]);
        b[i]=b[i-1]+a[i];
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=i;j<=n;++j) d[i][j]=5e18;
    }
    Set.clear();
    Set.insert(0);
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=i;++j)
        {
            Set.insert(b[i]-b[j-1]);
        }
        for(int j=i+1;j<=n;++j)
        {
            d[i+1][j]=min(d[i+1][j],find(b[j]-b[i]));
        }
    }
    Set.clear();
    Set.insert(0);
    for(int i=n;i>=1;--i)
    {
        for(int j=i;j<=n;++j)
        {
            Set.insert(b[j]-b[i-1]);
        }
        for(int j=1;j<=i-1;++j)
        {
            d[j][i-1]=min(d[j][i-1],find(b[i-1]-b[j-1]));
        }
    }
    Set.clear();
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=i;++j)
        {
            Set.insert(b[j-1]-b[i]);
        }
        for(int j=i+2;j<=n;++j)
        {
            d[i+2][j]=min(d[i+2][j],find(b[j]-b[i+1]));
        }
    }
    Set.clear();
    for(int i=n;i>=1;--i)
    {
        for(int j=i;j<=n;++j)
        {
            Set.insert(b[i-1]-b[j]);
        }
        for(int j=1;j<=i-2;++j)
        {
            d[j][i-2]=min(d[j][i-2],find(b[i-2]-b[j-1]));
        }
    }
    for(int i=1;i<=n;++i) T[i]=5e18;
    for(int i=1;i<=n;++i)
    {
        for(int j=i;j<=n;++j)
        {
            add(j,d[i][j]);
        }
        f[i]=sum(i);
    }
    for(int i=1;i<=n;++i)
    {
        printf("%lld\n",f[i]);
    }
    return 0;
}