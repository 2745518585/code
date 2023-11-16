#include<cstdio>
#include<algorithm>
using namespace std;
const int N=61,M=3001;
int m,n,q,a[N],f[N][N][N][2][2],g[N][M];
int main()
{
    scanf("%d%d%d",&m,&n,&q);
    for(int r=1;r<=m;++r)
    {
        char z[N];
        scanf("%s",z+1);
        for(int i=1;i<=n;++i)
        {
            a[i]=z[i]-'0';
        }
        for(int i=1;i<=n;++i)
        {
            for(int j=1;j<=n;++j)
            {
                for(int k=0;k<=n;++k)
                {
                    f[i][j][k][0][0]=f[i][j][k][0][1]=f[i][j][k][1][0]=f[i][j][k][1][1]=-1e9;
                }
            }
        }
        for(int i=1;i<=n;++i)
        {
            f[i][i][1][0][0]=(a[i]==0);
            f[i][i][1][1][1]=(a[i]==1);
        }
        for(int p=1;p<=n;++p)
        {
            for(int i=1,j=p;j<=n;++i,++j)
            {
                for(int k=0;k<=n;++k)
                {
                    for(int l1=0;l1<=1;++l1)
                    {
                        for(int l2=0;l2<=1;++l2)
                        {
                            if(i>1) f[i-1][j][k][l1][l2]=max(f[i-1][j][k][l1][l2],f[i][j][k][l1][l2]+(a[i-1]==l1));
                            if(i>1) f[i-1][j][k+1][l1^1][l2]=max(f[i-1][j][k+1][l1^1][l2],f[i][j][k][l1][l2]+(a[i-1]==(l1^1)));
                            if(j<n) f[i][j+1][k][l1][l2]=max(f[i][j+1][k][l1][l2],f[i][j][k][l1][l2]+(a[j+1]==l2));
                            if(j<n) f[i][j+1][k+1][l1][l2^1]=max(f[i][j+1][k+1][l1][l2^1],f[i][j][k][l1][l2]+(a[j+1]==(l2^1)));
                        }
                    }
                }
            }
        }
        for(int i=0;i<=q;++i)
        {
            for(int j=0;j<=i;++j)
            {
                g[r][i]=max(g[r][i],g[r-1][i-j]+max(max(f[1][n][j][0][0],f[1][n][j][0][1]),max(f[1][n][j][1][0],f[1][n][j][1][1])));
            }
        }
    }
    printf("%d",g[m][q]);
    return 0;
}