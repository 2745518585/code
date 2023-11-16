#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,a[N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        ll s=0;
        for(int i=1;i<=n-1;++i)
        {
            scanf("%d",&a[i]);
            s+=a[i];
        }
        printf("%lld\n",-s);
    }
    return 0;
}