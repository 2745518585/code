#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,a[N];
bool h[N];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    a[0]=a[1],a[n+1]=2e9;
    for(int i=1;i<=n;++i)
    {
        if(((a[i-1]<=a[i])&&(a[i+1]<a[i]))) h[i]^=1;
        if(((a[i-1]>a[i])&&(a[i+1]>=a[i]))) h[i]^=1;
    }
    for(int i=1;i<=n;++i)
    {
        printf("%d ",h[i]);
    }
    return 0;
}