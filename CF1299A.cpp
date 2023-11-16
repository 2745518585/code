#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,a[N],b[N],c[N];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    b[0]=(1ll<<31)-1;
    for(int i=1;i<=n;++i) b[i]=b[i-1]&(((1ll<<31)-1)^a[i]);
    c[n+1]=(1ll<<31)-1;
    for(int i=n;i>=1;--i) c[i]=c[i+1]&(((1ll<<31)-1)^a[i]);
    int s=0,q=1;
    for(int i=1;i<=n;++i)
    {
        if((b[i-1]&c[i+1]&a[i])>s)
        {
            s=b[i-1]&c[i+1]&a[i];
            q=i;
        }
    }
    printf("%d ",a[q]);
    for(int i=1;i<=n;++i)
    {
        if(i!=q) printf("%d ",a[i]);
    }
    return 0;
}