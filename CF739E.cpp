#include<cstdio>
#include<algorithm>
using namespace std;
typedef long double ld;
const int N=3001;
int n,m1,m2,g[N][N];
ld a1[N],a2[N],f[N][N];
int check(ld x)
{
    for(int i=1;i<=n;++i)
    {
        for(int j=0;j<=m1;++j)
        {
            f[i][j]=f[i-1][j],g[i][j]=g[i-1][j];
            if(f[i-1][j]+a2[i]-x>f[i][j]) f[i][j]=f[i-1][j]+a2[i]-x,g[i][j]=g[i-1][j]+1;
            if(j>=1)
            {
                if(f[i-1][j-1]+a1[i]>f[i][j]) f[i][j]=f[i-1][j-1]+a1[i],g[i][j]=g[i-1][j-1];
                if(f[i-1][j-1]+(1-(1-a1[i])*(1-a2[i]))-x>f[i][j]) f[i][j]=f[i-1][j-1]+(1-(1-a1[i])*(1-a2[i]))-x,g[i][j]=g[i-1][j-1]+1;
            }
        }
    }
    return g[n][m1];
}
int main()
{
    scanf("%d%d%d",&n,&m1,&m2);
    for(int i=1;i<=n;++i)
    {
        scanf("%Lf",&a1[i]);
    }
    for(int i=1;i<=n;++i)
    {
        scanf("%Lf",&a2[i]);
    }
    ld l=0,r=1;
    for(int i=1;i<=200;++i)
    {
        ld z=(l+r)/2,p=check(z);
        if(p==m2)
        {
            printf("%.12Lf",f[n][m1]+z*g[n][m1]);
            return 0;
        }
        if(p<m2) r=z-2e-20;
        else l=z;
    }
    check(l);
    printf("%.12Lf",f[n][m1]+l*g[n][m1]);
    return 0;
}