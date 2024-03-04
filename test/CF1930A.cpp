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
        n*=2;
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
        }
        sort(a+1,a+n+1);
        int s=0;
        for(int i=1;i<=n;i+=2) s+=a[i];
        printf("%d\n",s);
    }
    return 0;
}