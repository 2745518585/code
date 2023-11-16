#include<cstdio>
#include<algorithm>
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
        sort(a+1,a+n+1);
        a[0]=-1;
        a[n+1]=n+1;
        int s=0;
        for(int i=0;i<=n;++i)
        {
            if(a[i]<=i-1&&a[i+1]>i) ++s;
        }
        printf("%d\n",s);
    }
    return 0;
}