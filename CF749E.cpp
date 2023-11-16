#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N=1000001;
int n,a[N];
struct sgt
{
    ll T[N];
    void add(int x,ll k)
    {
        while(x<=n) T[x]+=k,x+=x&-x;
    }
    ll sum(int x)
    {
        ll s=0;
        while(x>=1) s+=T[x],x-=x&-x;
        return s;
    }
}T1,T2;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    ll s=0,w=0;
    for(int i=1;i<=n;++i)
    {
        w+=(T1.sum(n)-T1.sum(a[i]));
        s+=T2.sum(a[i]-1)*(n-i+1);
        s-=(T2.sum(n)-T2.sum(a[i]))*(n-i+1);
        T1.add(a[i],1);
        T2.add(a[i],i);
    }
    printf("%.18Lf",w+(ld)s/((ll)n*(n+1)));
    return 0;
}