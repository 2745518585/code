#include<cstdio>
#include<algorithm>
using namespace std;
const int N=5001;
int n,m,a[N],b[N];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    sort(a+1,a+n+1);
    b[++m]=1;
    for(int i=2;i<=n;++i)
    {
        int l=0,r=m;
        while(l<r)
        {
            int z=l+r+1>>1;
            if(b[z]<=a[i]) l=z;
            else r=z-1;
        }
        if(l==0)
        {
            b[++m]=1;
            for(int j=m-1;j>=1;--j)
            {
                if(b[j+1]<b[j])
                {
                    swap(b[j+1],b[j]);
                }
            }
        }
        else
        {
            ++b[l];
            for(int j=l;j<=m-1;++j)
            {
                if(b[j+1]<b[j])
                {
                    swap(b[j+1],b[j]);
                }
            }
        }
    }
    printf("%d",m);
    return 0;
}