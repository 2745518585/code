#include<cstdio>
#include<algorithm>
using namespace std;
const int N=2000001;
int m,n,a[N],b[N],c[N],d[N];
char z[N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&m,&n);
        scanf("%s",z+1);
        for(int i=1;i<=m*n;++i) a[i]=z[i]-'0',b[i]=b[i-1]+a[i];
        for(int i=1;i<=n;++i) c[i]=(b[i]!=0);
        for(int i=n+1;i<=m*n;++i)
        {
            c[i]=c[i-n]+(b[i]-b[i-n]!=0);
        }
        for(int i=1;i<=n;++i) d[i]=0;
        int w=0;
        for(int i=1;i<=m*n;++i)
        {
            if(a[i]==1&&d[(i-1)%n+1]==0)
            {
                d[(i-1)%n+1]=1;
                ++w;
            }
            printf("%d ",w+c[i]);
        }
        printf("\n");
    }
    return 0;
}