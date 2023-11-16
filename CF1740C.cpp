#include<cstdio>
#include<algorithm>
using namespace std;
const int N=200001;
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
        sort(a+1,a+n+1);
        int s=0;
        for(int i=1;i<=n-2;++i)
        {
            s=max(s,a[n]-a[i]+a[i+1]-a[i]);
        }
        for(int i=n;i>=3;--i)
        {
            s=max(s,a[i]-a[1]+a[i]-a[i-1]);
        }
        printf("%d\n",s);
    }
    return 0;
}