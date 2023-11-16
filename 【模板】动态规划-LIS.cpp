#include<cstdio>
using namespace std;
const int N=100001;
int n,a[N],f[N];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=n;++i) f[i]=1e9;
    f[0]=-1e9;
    for(int i=1;i<=n;++i)
    {
        int l=0,r=i-1;
        while(l<r)
        {
            int z=l+r+1>>1;
            if(f[z]<a[i]) l=z;
            else r=z-1;
        }
        f[l+1]=a[i];
    }
    for(int i=n;i>=0;--i)
    {
        if(f[i]!=1e9)
        {
            printf("%d",i);
            return 0;
        }
    }
    return 0;
}