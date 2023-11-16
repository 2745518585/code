#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,a[N];
int solve()
{
    int i=1,j=2,k=0;
    while(i<=n&&j<=n&&k<=n-1)
    {
        if(a[(i+k-1)%n+1]==a[(j+k-1)%n+1]) ++k;
        else
        {
            if(a[(i+k-1)%n+1]>a[(j+k-1)%n+1]) i+=k+1;
            else j+=k+1;
            if(i==j) ++i;
            k=0;
        }
    }
    return min(i,j);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    int x=solve();
    for(int i=1;i<=n;++i)
    {
        printf("%d ",a[(x+i-2)%n+1]);
    }
    return 0;
}