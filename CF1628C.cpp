#include<cstdio>
#include<algorithm>
using namespace std;
const int N=2001;
int n,a[N][N],b[N][N],c[N][N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
        {
            for(int j=1;j<=n;++j)
            {
                scanf("%d",&a[i][j]);
            }
        }
        for(int i=1;i<=n;++i)
        {
            for(int j=1;j<=i;++j)
            {
                if(j==i) b[i][j]=a[i][j];
                else if(j==i-1) b[i][j]=a[i][j]^a[j][i];
                else b[i][j]=b[i-1][j+1]^a[i][j]^a[j][i];
            }
        }
        int s=0;
        for(int i=2;i<=n;++i)
        {
            for(int j=1;j<=i-1;++j)
            {
                c[i][j]=c[i-1][j-1]^b[i-1][j];
                s^=c[i][j];
            }
        }
        for(int i=1;i<=n;++i)
        {
            for(int j=1;j<=n/2;++j) swap(a[i][j],a[i][n-j+1]);
        }
        for(int i=1;i<=n;++i)
        {
            for(int j=1;j<=i;++j)
            {
                if(j==i) b[i][j]=a[i][j];
                else if(j==i-1) b[i][j]=a[i][j]^a[j][i];
                else b[i][j]=b[i-1][j+1]^a[i][j]^a[j][i];
            }
        }
        for(int i=2;i<=n;++i)
        {
            for(int j=1;j<=i-1;++j)
            {
                c[i][j]=c[i-1][j-1]^b[i-1][j];
            }
            if(i>n/2) s^=c[i][n-i+1];
        }
        printf("%d\n",s);
    }
    return 0;
}