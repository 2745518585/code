#include<cstdio>
#include<algorithm>
using namespace std;
const int N=24;
int n,a[N],f[1<<N];
int main()
{
    scanf("%d",&n);
    for(int i=0;i<=n-1;++i)
    {
        static char z[N];
        scanf("%s",z);
        for(int j=0;j<=n-1;++j)
        {
            if(z[j]=='1') a[i]|=(1<<j);
        }
    }
    f[0]=1;
    for(int i=0;i<=(1<<(n-1))-1;++i)
    {
        for(int j=1;j<=n-1;++j)
        {
            if((i&(1<<(j-1)))==0&&(f[i]&a[j])!=0)
            {
                f[i|(1<<(j-1))]|=(1<<j);
            }
        }
    }
    for(int i=0;i<=n-1;++i)
    {
        int w=0;
        for(int j=0;j<=(1<<(n-1))-1;++j)
        {
            if(f[j]&(1<<i)) w|=f[(((1<<(n-1))-1)^j)];
        }
        for(int j=0;j<=n-1;++j)
        {
            printf("%d",(w&(1<<j))!=0);
        }
        printf("\n");
    }
    return 0;
}