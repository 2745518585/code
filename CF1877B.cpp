#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000001;
int n;
ll k;
struct str
{
    ll a,b;
}a[N];
bool cmp(str a,str b)
{
    return a.b<b.b;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%lld",&n,&k);
        for(int i=1;i<=n;++i)
        {
            scanf("%lld",&a[i].a);
        }
        for(int i=1;i<=n;++i)
        {
            scanf("%lld",&a[i].b);
        }
        sort(a+1,a+n+1,cmp);
        ll s=k,w=1;
        for(int i=1;i<=n;++i)
        {
            if(a[i].b>k) break;
            ll z=min(a[i].a,n-w);
            s+=a[i].b*z;
            w+=z;
        }
        s+=k*(n-w);
        printf("%lld\n",s);
    }
    return 0;
}