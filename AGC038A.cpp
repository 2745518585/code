#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1001;
int m,n,a,b,f[N][N];
int main()
{
    scanf("%d%d%d%d",&m,&n,&a,&b);
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j) f[i][j]=(j<=a);
    }
    for(int i=1;i<=b;++i)
    {
        for(int j=1;j<=n;++j) f[i][j]^=1;
    }
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j) printf("%d",f[i][j]);
        printf("\n");
    }
    return 0;
}