#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,a[N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
            a[i]-=i-1;
        }
        ll k=1;
        for(int i=1;i<=m;++i)
        {
            int x=upper_bound(a+1,a+n+1,k)-a-1;
            k+=x;
        }
        printf("%lld\n",k);
    }
    return 0;
}