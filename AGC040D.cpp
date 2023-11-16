#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
typedef __int128_t int128;
const int N=1000001;
int n;
ll m1,m2,b[N];
struct str
{
    ll a,b;
}a[N];
ll gcd(ll a,ll b)
{
    if(b==0) return a;
    return gcd(b,a%b);
}
bool cmp(str a,str b)
{
    return max(a.a,a.b)>max(b.a,b.b);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%lld%lld",&a[i].a,&a[i].b);
        m1+=a[i].a;
        m2+=a[i].b;
    }
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;++i) b[i]=b[i-1]+max(a[i].a,a[i].b);
    ll s1=0,s2=1;
    for(int i=1;i<=n;++i)
    {
        int l=1,r=n+1;
        while(l<r)
        {
            int z=l+r>>1;
            if(b[z]-(z>=i?max(a[i].a,a[i].b):0)+a[i].b>=m1) r=z;
            else l=z+1;
        }
        if(l==n+1) continue;
        if(b[l]-(l>=i?max(a[i].a,a[i].b):0)+a[i].b-m1>a[i].b) continue;
        ll w=(b[l]-(l>=i?max(a[i].a,a[i].b):0)+a[i].b-m1)+(l>=i?n-l:n-l-1)*a[i].b;
        if((int128)w*s2>(int128)s1*a[i].b*n) s1=w,s2=a[i].b*n;
    }
    ll z=gcd(s1,s2);
    s1/=z,s2/=z;
    printf("%lld %lld",s1,s2);
    return 0;
}