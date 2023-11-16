#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1001;
int n;
ll a[N],b[N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
        {
            scanf("%lld",&a[i]);
        }
        for(int i=1;i<=n;++i)
        {
            scanf("%lld",&b[i]);
        }
        ll s=0,w=1e18;
        for(int i=0;i<=(1<<(n/2))-1;++i)
        {
            ll t=0;
            for(int j=1;j<=n/2;++j)
            {
                if(i&(1<<(j-1))) t+=abs(a[j]-a[j+1])+abs(b[j]-b[j+1]);
                else t+=abs(a[j]-b[j+1])+abs(b[j]-a[j+1]);
            }
            w=min(w,t);
        }
        s+=w;
        w=1e18;
        for(int i=0;i<=(1<<(n-n/2-1))-1;++i)
        {
            ll t=0;
            for(int j=1;j<=n-n/2-1;++j)
            {
                if(i&(1<<(j-1))) t+=abs(a[n-j+1]-a[n-j])+abs(b[n-j+1]-b[n-j]);
                else t+=abs(a[n-j+1]-b[n-j])+abs(b[n-j+1]-a[n-j]);
            }
            w=min(w,t);
        }
        s+=w;
        printf("%lld\n",s);
    }
    return 0;
}