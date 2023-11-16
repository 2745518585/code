#include<cstdio>
#include<algorithm>
using namespace std;
const int N=10001;
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
        int s=a[n]-a[1];
        for(int i=1;i<=n-1;++i)
        {
            s=max(s,a[i]-a[i+1]);
        }
        int s1=1e9,s2=-1e9;
        for(int i=1;i<=n;++i)
        {
            if(i!=n) s1=min(s1,a[i]);
            if(i!=1) s2=max(s2,a[i]);
        }
        s=max(s,max(a[n]-s1,s2-a[1]));
        printf("%d\n",s);
    }
    return 0;
}