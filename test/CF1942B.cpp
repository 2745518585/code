#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,a[N],b[N];
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
        int x=n;
        for(int i=n;i>=1;--i)
        {
            b[i]=x-a[i];
            x=min(x,x-a[i]);
        }
        for(int i=1;i<=n;++i) printf("%d ",b[i]);
        printf("\n");
    }
    return 0;
}