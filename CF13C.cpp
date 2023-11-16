#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=10001;
int n,q,a[N],b[N];
ll f[N],g[N];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        b[i]=a[i];
    }
    sort(b+1,b+n+1);
    q=unique(b+1,b+n+1)-b-1;
    for(int i=1;i<=n;++i)
    {
        a[i]=lower_bound(b+1,b+n+1,a[i])-b;
    }
    for(int i=1;i<=n;++i)
    {
        g[1]=f[1];
        for(int j=2;j<=q;++j) g[j]=min(g[j-1],f[j]);
        for(int j=1;j<=q;++j)
        {
            f[j]=g[j]+abs(b[a[i]]-b[j]);
        }
    }
    ll s=1e18;
    for(int i=1;i<=q;++i) s=min(s,f[i]);
    printf("%lld",s);
    return 0;
}