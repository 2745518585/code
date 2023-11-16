#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1001,M=51;
int n,n1,n2,m,q,a1[N],a2[N],f[M][M][N],g[M][M][N];
bool h1[N],h2[N];
int main()
{
    scanf("%d%d%d",&n,&q,&m);
    scanf("%d",&n1);
    for(int i=1;i<=n1;++i)
    {
        scanf("%d",&a1[i]);
        h1[a1[i]]=true;
    }
    scanf("%d",&n2);
    for(int i=1;i<=n2;++i)
    {
        scanf("%d",&a2[i]);
        h2[a2[i]]=true;
    }
    if(m*q>=n*2+2)
    {
        int s=0;
        for(int i=1;i<=n;++i) s+=(h1[i]|h2[i]);
        printf("%d\n",s);
        return 0;
    }
    for(int i=0;i<=m-1;++i)
    {
        for(int j=0;j<=m-1;++j)
        {
            for(int k=0;k<=q;++k)
            {
                f[i][j][k]=-1e9;
            }
        }
    }
    f[0][0][0]=0;
    for(int i=1;i<=n;++i)
    {
        for(int j=0;j<=m-1;++j)
        {
            for(int k=0;k<=m-1;++k)
            {
                for(int l=0;l<=q;++l) g[j][k][l]=f[j][k][l],f[j][k][l]=-1e9;
            }
        }
        for(int j=0;j<=m-1;++j)
        {
            for(int k=0;k<=m-1;++k)
            {
                for(int l=0;l<=q;++l)
                {
                    f[max(j-1,0)][max(k-1,0)][l]=max(f[max(j-1,0)][max(k-1,0)][l],g[j][k][l]+((j>0&&h1[i])||(k>0&&h2[i])));
                    if(l<q&&h1[i]) f[m-1][max(k-1,0)][l+1]=max(f[m-1][max(k-1,0)][l+1],g[j][k][l]+1);
                    if(l<q&&h2[i]) f[max(j-1,0)][m-1][l+1]=max(f[max(j-1,0)][m-1][l+1],g[j][k][l]+1);
                    if(l<=q-2&&h1[i]&&h2[i]) f[m-1][m-1][l+2]=max(f[m-1][m-1][l+2],g[j][k][l]+1);
                }
            }
        }
    }
    int s=0;
    for(int i=0;i<=m-1;++i)
    {
        for(int j=0;j<=m-1;++j)
        {
            for(int k=0;k<=q;++k)
            {
                s=max(s,f[i][j][k]);
            }
        }
    }
    printf("%d",s);
    return 0;
}