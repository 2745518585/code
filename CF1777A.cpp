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
        int s=0;
        for(int i=2;i<=n;++i)
        {
            if(a[i-1]%2==a[i]%2) ++s;
        }
        printf("%d\n",s);
    }
    return 0;
}