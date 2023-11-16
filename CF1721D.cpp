#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,t,a[N],b[N];
bool cmp(int x,int y)
{
    return (x&t)<(y&t);
}
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
            a[i]=~a[i];
        }
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&b[i]);
        }
        t=0;
        for(int i=30;i>=0;--i)
        {
            t+=(1<<i);
            sort(a+1,a+n+1,cmp);
            sort(b+1,b+n+1,cmp);
            for(int j=1;j<=n;++j)
            {
                if((a[j]&t)!=(b[j]&t))
                {
                    t-=(1<<i);
                    break;
                }
            }
        }
        printf("%d\n",t);
    }
    return 0;
}