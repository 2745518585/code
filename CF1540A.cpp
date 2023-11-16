#include<cstdio>
#include<algorithm>
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
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
        }
        sort(a+1,a+n+1);
        ll s=a[n],w=0;
        for(int i=1;i<=n;++i)
        {
            s+=w-(ll)a[i]*(i-1);
            w+=a[i];
        }
        printf("%lld\n",s);
    }
    return 0;
}