#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1001;
int m,n,*b[N*N],f[N][N],g[N][N],h[N][N];
char *a[N*N];
int main()
{
    int TOT;
    scanf("%d",&TOT);
    while(TOT--)
    {
        scanf("%d%d",&m,&n);
        for(int i=1;i<=m;++i)
        {
            a[i]=new char[n+10];
            b[i]=new int[n+10];
            scanf("%s",a[i]+1);
        }
        if(m<=n)
        {
            for(int i=0;i<=m+1;++i)
            {
                for(int j=0;j<=m+1;++j) f[i][j]=g[i][j]=0,h[i][j]=1e9;
            }
            for(int p=1;p<=n;++p)
            {
                for(int i=0;i<=m+1;++i)
                {
                    for(int j=0;j<=m+1;++j) h[i][j]=1e9;
                }
                for(int i=1;i<=m;++i)
                {
                    for(int j=i+1;j<=m;++j)
                    {
                        if(f[i][j]<=n&&g[i][j]>=1) h[i][j]=min(h[i][j],(f[i][j]-g[i][j]+1)*(j-i+1));
                        if(f[i][j]<=p) f[i][j]=p+1;
                        while(f[i][j]<=n&&(a[i][f[i][j]]!='1'||a[j][f[i][j]]!='1')) ++f[i][j];
                        if(a[i][p]=='1'&&a[j][p]=='1') g[i][j]=p;
                        if(f[i][j]<=n&&g[i][j]>=1) h[i][j]=min(h[i][j],(f[i][j]-g[i][j]+1)*(j-i+1));
                    }
                }
                for(int k=m;k>=1;--k)
                {
                    for(int i=1,j=i+k-1;j<=m;++i,++j)
                    {
                        h[i][j]=min(h[i][j],min(h[i-1][j],h[i][j+1]));
                    }
                }
                for(int i=1;i<=m;++i)
                {
                    b[i][p]=h[i][i];
                }
            }
            for(int i=1;i<=m;++i)
            {
                for(int j=1;j<=n;++j)
                {
                    if(b[i][j]==1e9) printf("0 ");
                    else printf("%d ",b[i][j]);
                }
                printf("\n");
            }
        }
        else
        {
            for(int i=0;i<=n+1;++i)
            {
                for(int j=0;j<=n+1;++j) f[i][j]=g[i][j]=0,h[i][j]=1e9;
            }
            for(int p=1;p<=m;++p)
            {
                for(int i=0;i<=n+1;++i)
                {
                    for(int j=0;j<=n+1;++j) h[i][j]=1e9;
                }
                for(int i=1;i<=n;++i)
                {
                    for(int j=i+1;j<=n;++j)
                    {
                        if(f[i][j]<=m&&g[i][j]>=1) h[i][j]=min(h[i][j],(f[i][j]-g[i][j]+1)*(j-i+1));
                        if(f[i][j]<=p) f[i][j]=p+1;
                        while(f[i][j]<=m&&(a[f[i][j]][i]!='1'||a[f[i][j]][j]!='1')) ++f[i][j];
                        if(a[p][i]=='1'&&a[p][j]=='1') g[i][j]=p;
                        if(f[i][j]<=m&&g[i][j]>=1) h[i][j]=min(h[i][j],(f[i][j]-g[i][j]+1)*(j-i+1));
                    }
                }
                for(int k=n;k>=1;--k)
                {
                    for(int i=1,j=i+k-1;j<=n;++i,++j)
                    {
                        h[i][j]=min(h[i][j],min(h[i-1][j],h[i][j+1]));
                    }
                }
                for(int i=1;i<=n;++i)
                {
                    b[p][i]=h[i][i];
                }
            }
            for(int i=1;i<=m;++i)
            {
                for(int j=1;j<=n;++j)
                {
                    if(b[i][j]==1e9) printf("0 ");
                    else printf("%d ",b[i][j]);
                }
                printf("\n");
            }
        }
    }
    return 0;
}