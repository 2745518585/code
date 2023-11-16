#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,a[N];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    for(int i=2;i<=n;++i)
    {
        int z=0;
        if(a[i-1]<a[i]) z=1;
        else z=-1;
        for(int j=a[i-1];j!=a[i];j+=z)
        {
            printf("%d ",j);
        }
    }
    printf("%d",a[n]);
    return 0;
}