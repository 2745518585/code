#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,a[N],b[N][2],f[N][2];
bool h[N];
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
            b[i][0]=-a[i],b[i][1]=a[i];
        }
        a[0]=b[0][0]=b[0][1]=-(n+1);
        f[0][0]=f[0][1]=-(n+1);
        for(int i=1;i<=n;++i)
        {
            for(int j=0;j<=1;++j)
            {
                f[i][j]=n+1;
                for(int k=0;k<=1;++k)
                {
                    if(b[i][j]>b[i-1][k]) f[i][j]=min(f[i][j],f[i-1][k]);
                    if(b[i][j]>f[i-1][k]) f[i][j]=min(f[i][j],b[i-1][k]);
                }
            }
            // printf("%d %d\n",f[i][0],f[i][1]);
        }
        if(f[n][0]>n&&f[n][1]>n)
        {
            printf("NO\n");
            continue;
        }
        printf("YES\n");
        int x=f[n][0]<=n?0:1;
        for(int i=n;i>=1;--i)
        {
            h[i]=x;
            for(int j=0;j<=1;++j)
            {
                if((b[i][x]>b[i-1][j]&&f[i][x]==f[i-1][j])||(b[i][x]>f[i-1][j]&&f[i][x]==b[i-1][j]))
                {
                    x=j;
                    break;
                }
            }
        }
        for(int i=1;i<=n;++i) printf("%d ",b[i][h[i]]);printf("\n");
    }
    return 0;
}