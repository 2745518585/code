#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,a[N];
bool check(int x)
{
    int x1=1,x2=n;
    while(x1<x2)
    {
        if(a[x1]!=a[x2])
        {
            if(a[x1]==x)
            {
                ++x1;
                continue;
            }
            if(a[x2]==x)
            {
                --x2;
                continue;
            }
            return false;
        }
        ++x1,--x2;
    }
    return true;
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
        }
        int x1=0,x2=0;
        for(int i=1;i<=n/2;++i)
        {
            if(a[i]!=a[n-i+1])
            {
                x1=a[i],x2=a[n-i+1];
                break;
            }
        }
        if(x1==0)
        {
            printf("YES\n");
            continue;
        }
        if(check(x1)||check(x2)) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}