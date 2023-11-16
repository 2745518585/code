#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,a[N],b[N],c[N],d[N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i) b[i]=0,c[i]=0;
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
            c[a[i]]=max(c[a[i]],i-b[a[i]]);
            b[a[i]]=i;
        }
        for(int i=0;i<=n;++i) d[i]=1e9;
        for(int i=1;i<=n;++i)
        {
            c[i]=max(c[i],n+1-b[i]);
            d[c[i]]=min(d[c[i]],i);
        }
        for(int i=1;i<=n;++i) d[i]=min(d[i],d[i-1]);
        for(int i=1;i<=n;++i) printf("%d ",d[i]==1e9?-1:d[i]);
        printf("\n");
    }
    return 0;
}