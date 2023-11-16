#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
const int N=1000001;
int n,a[N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
        }
        int l=0,r=1e9;
        for(int i=1;i<=n-1;++i)
        {
            if(a[i]<a[i+1]) r=min(r,int(floor((double)(a[i]+a[i+1])/2)));
            if(a[i]>a[i+1]) l=max(l,int(ceil((double)(a[i]+a[i+1])/2)));
        }
        if(l>r) printf("-1\n");
        else printf("%d\n",l);
    }
    return 0;
}