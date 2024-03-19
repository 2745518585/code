#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n;
ll k,a[N],b[N],c[N],f[N];
bool check(int n)
{
    for(int i=0;i<=n;++i) b[i]=a[i];
    sort(b,b+n+1);
    c[0]=b[0];
    for(int i=1;i<=n;++i) c[i]=c[i-1]+b[i];
    int x=0;
    for(int i=0;i<=n;++i)
    {
        while(x<i&&(c[i]-(x>0?c[x-1]:0))-(b[x]+1)*(i-x+1)+1>x*k) ++x;
        if(c[i]-(x>0?c[x-1]:0)-x*k<=f[i-x+1]) return true;
    }
    return false;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%lld",&n,&k);
        for(int i=0;i<=n;++i)
        {
            scanf("%lld",&a[i]);
        }
        f[1]=0,f[2]=k*2;
        for(int i=3;i<=n+1;++i)
        {
            ll l=f[i-1],r=1e18;
            while(l<r)
            {
                ll z=l+r+1>>1;
                if(z-z/i-k<=f[i-1]) l=z;
                else r=z-1;
            }
            f[i]=l;
        }
        int l=0,r=n+1;
        while(l<r)
        {
            int z=l+r+1>>1;
            if(check(z-1)) r=z-1;
            else l=z;
        }
        printf("%d\n",l);
    }
    return 0;
}