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
        int w=-1e9,s=0;
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
            s=max(s,w-a[i]);
            w=max(w,a[i]);
        }
        int t=0;
        while(s) ++t,s/=2;
        printf("%d\n",t);
    }
    return 0;
}