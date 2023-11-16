#include<cstdio>
using namespace std;
const int p=19650827;
int n,a[1001],f[1001][1001][2];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        f[i][i][0]=1;
    }
    for(int l=2;l<=n;++l)
    {
        for(int i=1,j=l;j<=n;++i,++j)
        {
            if(a[i]<a[i+1]) f[i][j][0]+=f[i+1][j][0];
            if(a[i]<a[j]) f[i][j][0]+=f[i+1][j][1];
            if(a[j]>a[j-1]) f[i][j][1]+=f[i][j-1][1];
            if(a[j]>a[i]) f[i][j][1]+=f[i][j-1][0];
            f[i][j][0]%=p;
            f[i][j][1]%=p;
        }
    }
    printf("%d",(f[1][n][0]+f[1][n][1])%p);
    return 0;
}