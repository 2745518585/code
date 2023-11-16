#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n;
ll l,r,a[N],b[N];
int main()
{
    scanf("%d%lld%lld",&n,&l,&r);
    ll w=0;
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&a[i]);
        w+=a[i];
    }
    a[0]=-1e18;
    sort(a+1,a+n+1);
    w-=l+r;
    ll s=1e18;
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j) b[j]=a[j];
        b[n+1]=a[i],b[n+2]=a[i]+w;
        for(int j=n+1;j>=1;--j)
        {
            if(b[j+1]<b[j]) swap(b[j],b[j+1]);
        }
        for(int j=n+1;j>=1;--j)
        {
            if(b[j+1]<b[j]) swap(b[j],b[j+1]);
        }
        ll q=0;
        for(int j=1;j<=n+2;j+=2) q+=b[j+1]-b[j];
        s=min(s,q);
    }
    if(abs(s)<=r-l) printf("Alice");
    else printf("Bob");
    return 0;
}