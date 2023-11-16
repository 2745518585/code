#include<cstdio>
#include<algorithm>
using namespace std;
const int N=51,M=11,Q=500001;
int n,m,q,a[N][M],f[Q];
int main()
{
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=m;++j)
        {
            scanf("%d",&a[i][j]);
        }
    }
    for(int i=1;i<=m-1;++i)
    {
        for(int j=0;j<=q;++j) f[j]=j;
        for(int j=1;j<=n;++j)
        {
            for(int k=a[j][i];k<=q;++k)
            {
                f[k]=max(f[k],f[k-a[j][i]]+a[j][i+1]);
            }
        }
        q=f[q];
    }
    printf("%d",q);
    return 0;
}