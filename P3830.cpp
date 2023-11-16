#include<cstdio>
#include<algorithm>
using namespace std;
typedef long double ld;
const int N=1001;
int n;
ld f[N][N],g[N];
int main()
{
    int z;
    scanf("%d%d",&z,&n);
    if(z==1)
    {
        g[1]=0;
        for(int i=2;i<=n;++i) g[i]=g[i-1]+(ld)2/i;
        printf("%.6Lf",g[n]);
        return 0;
    }
    for(int i=0;i<=n;++i) f[i][0]=1;
    for(int i=2;i<=n;++i)
    {
        for(int j=1;j<=i;++j)
        {
            for(int k=1;k<=i-1;++k)
            {
                f[i][j]+=(f[k][j-1]+f[i-k][j-1]-f[k][j-1]*f[i-k][j-1])/(i-1);
            }
        }
    }
    ld s=0;
    for(int i=1;i<=n;++i) s+=f[n][i];
    printf("%.6Lf",s);
    return 0;
}