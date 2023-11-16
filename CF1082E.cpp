#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,m,k,q,s,a[N],b[N],f[N],g[N],h[N];
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        b[i]=a[i];
    }
    b[n+1]=k;
    sort(b+1,b+n+2);
    q=unique(b+1,b+n+2)-b-1;
    for(int i=1;i<=n;++i)
    {
        a[i]=lower_bound(b+1,b+q+1,a[i])-b;
        ++h[a[i]];
    }
    k=lower_bound(b+1,b+q+1,k)-b;
    for(int i=1;i<=n;++i)
    {
        f[a[i]]=max(f[a[i]],g[k]-g[a[i]]);
        ++g[a[i]];
        s=max(s,h[k]-(g[k]-g[a[i]])+f[a[i]]);
    }
    printf("%d",s);
    return 0;
}