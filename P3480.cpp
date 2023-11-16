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
        for(int i=n;i>=1;--i) a[i]-=a[i-1];
        int s=0;
        for(int i=n;i>=1;i-=2) s^=a[i];
        if(s) printf("TAK\n");
        else printf("NIE\n");
    }
    return 0;
}