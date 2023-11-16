#include<cstdio>
#include<algorithm>
using namespace std;
const int N=2001;
int n,a[N],f[N][N],g[N][N];
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
            f[i][i]=g[i][i]=a[i];
        }
        for(int p=2;p<=n;++p)
        {
            for(int i=1,j=i+p-1;j<=n;++i,++j)
            {
                int l=f[i][j-1],r=g[i][j-1];
                if(a[j]==r) f[i][j]=0;
                else if(a[j]<l&&a[j]<r) f[i][j]=a[j];
                else if(l>r&&a[j]>r&&a[j]<=l) f[i][j]=a[j]-1;
                else if(r>l&&a[j]>=l&&a[j]<r) f[i][j]=a[j]+1;
                else if(a[j]>l&&a[j]>r) f[i][j]=a[j];
                l=f[i+1][j],r=g[i+1][j];
                if(a[i]==l) g[i][j]=0;
                else if(a[i]<r&&a[i]<l) g[i][j]=a[i];
                else if(r>l&&a[i]>l&&a[i]<=r) g[i][j]=a[i]-1;
                else if(l>r&&a[i]>=r&&a[i]<l) g[i][j]=a[i]+1;
                else if(a[i]>r&&a[i]>l) g[i][j]=a[i];
            }
        }
        if(f[1][n]==0) printf("0\n");
        else printf("1\n");
    }
    return 0;
}