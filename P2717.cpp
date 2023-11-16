#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=200001;
int n,m,q;
ll a[N],b[N],T[N];
void add(int x,ll k)
{
    while(x<=1e5)
    {
        T[x]+=k;
        x+=(x&-x);
    }
}
ll sum(int x)
{
    ll s=0;
    while(x>=1)
    {
        s+=T[x];
        x-=(x&-x);
    }
    return s;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&a[i]);
        a[i]+=a[i-1]-m;
        b[i]=a[i];
    }
    b[n+1]=0;
    sort(b+1,b+n+2);
    q=unique(b+1,b+n+2)-b-1;
    for(int i=1;i<=n;++i)
    {
        a[i]=lower_bound(b+1,b+q+1,a[i])-b;
    }
    ll s=0;
    add(lower_bound(b+1,b+q+1,0)-b,1);
    for(int i=1;i<=n;++i)
    {
        s+=sum(a[i]);
        add(a[i],1);
    }
    printf("%lld",s);
    return 0;
}