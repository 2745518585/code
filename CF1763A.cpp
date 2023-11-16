#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,a[N],h[N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        for(int i=0;i<=30;++i) h[i]=0;
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
            for(int j=0;j<=30;++j)
            {
                if(a[i]&(1<<j)) ++h[j];
            }
        }
        int s=0;
        for(int i=0;i<=30;++i)
        {
            if(h[i]!=0&&h[i]!=n) s+=(1<<i);
        }
        printf("%d\n",s);
    }
    return 0;
}