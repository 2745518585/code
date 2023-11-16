#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,a[N],f[N];
int main()
{
    scanf("%d",&n);
    int s=0;
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        s=max(s,a[i]);
    }
    for(int i=1;i<=n-1;++i)
    {
        f[min(i-1,n-i-1)*2+2]=max(f[min(i-1,n-i-1)*2+2],max(a[i],a[i+1]));
    }
    for(int i=2;i<=n-1;++i)
    {
        f[min(i-2,n-i-1)*2+3]=max(f[min(i-2,n-i-1)*2+3],max(min(a[i-1],a[i]),min(a[i],a[i+1])));
    }
    for(int i=n;i>=1;--i) f[i]=max(f[i],f[i+2]);
    f[1]=s;
    for(int i=n;i>=1;--i)
    {
        printf("%d ",f[i]);
    }
    return 0;
}