#include<cstdio>
#include<algorithm>
using namespace std;
int n,m,q,a[5001],b[5001],c[5001],d[5001],f[101][101][5001],f2[101][101][5001],g1[101][101][5001],g2[101][101][5001],h[5001];
void print(int l,int r,int t)
{
    int z=g1[l][r][t];
    if(l<=z-1) print(l,z-1,g2[l][z-1][t]);
    printf("%d ",d[t]);
    if(r>=z+1) print(z+1,r,g2[z+1][r][t]);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i)
    {
        scanf("%d%d%d",&a[i],&b[i],&c[i]);
        d[i]=c[i];
    }
    sort(d+1,d+m+1);
    q=unique(d+1,d+m+1)-(d+1);
    for(int i=1;i<=m;++i) c[i]=lower_bound(d+1,d+q+1,c[i])-d;
    for(int i=n;i>=1;--i)
    {
        for(int j=i;j<=n;++j)
        {
            for(int k=i;k<=j;++k)
            {
                int w=0;
                for(int l=1;l<=q;++l) h[l]=0;
                for(int l=1;l<=m;++l)
                {
                    if(a[l]>=i&&b[l]<=j&&a[l]<=k&&b[l]>=k) ++h[c[l]];
                }
                for(int l=q;l>=1;--l)
                {
                    w+=h[l];
                    if(f2[i][k-1][l]+f2[k+1][j][l]+w*d[l]>=f[i][j][l])
                    {
                        f[i][j][l]=f2[i][k-1][l]+f2[k+1][j][l]+w*d[l];
                        g1[i][j][l]=k;
                    }
                }
            }
            for(int k=q;k>=1;--k)
            {
                if(f[i][j][k]>=f2[i][j][k+1])
                {
                    f2[i][j][k]=f[i][j][k];
                    g2[i][j][k]=k;
                }
                else
                {
                    f2[i][j][k]=f2[i][j][k+1];
                    g2[i][j][k]=g2[i][j][k+1];
                }
            }
        }
    }
    printf("%d\n",f2[1][n][1]);
    print(1,n,g2[1][n][1]);
    return 0;
}