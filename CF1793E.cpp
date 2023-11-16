#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,a[N],f[N],g[N],h[N];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    sort(a+1,a+n+1);
    for (int i=1;i<=n;++i)
    {
        if(i<=a[i]) f[i]=1-(a[i]-i);
        else f[i]=g[i-a[i]]+1;
        g[i]=max(g[i-1],f[i]);
    }
    for(int i=1;i<=n;++i) h[f[i]+n-i]=max(h[f[i]+n-i],i);
    for(int i=n;i>=1;--i) h[i]=max(h[i],h[i+1]);
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int x;
        scanf("%d",&x);
        printf("%d\n",h[x]);
    }
    return 0;
}