#include<cstdio>
#include<algorithm>
using namespace std;
int n,q,a[101],b[101],c[101],f[101][101][2];
int main()
{
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d",&a[i],&b[i]);
        c[i]=c[i-1]+b[i];
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            f[i][j][0]=1e9;
            f[i][j][1]=1e9;
        }
    }
    f[q][q][0]=0;
    f[q][q][1]=0;
    for(int i=1;i<=n-1;++i)
    {
        for(int j=max(q-i,1);j<=min(q,n-i);++j)
        {
            f[j][i+j][1]=min(f[j][i+j][1],f[j][i+j-1][1]+(a[i+j]-a[i+j-1])*(c[n]-c[i+j-1]+c[j-1]));
            f[j][i+j][0]=min(f[j][i+j][0],f[j+1][i+j][0]+(a[j+1]-a[j])*(c[n]-c[i+j]+c[j]));
            f[j][i+j][1]=min(f[j][i+j][1],f[j][i+j][0]+(a[i+j]-a[j])*(c[n]-c[i+j]+c[j-1]));
            f[j][i+j][0]=min(f[j][i+j][0],f[j][i+j][1]+(a[i+j]-a[j])*(c[n]-c[i+j]+c[j-1]));
        }
    }
    printf("%d",min(f[1][n][0],f[1][n][1]));
    return 0;
}
