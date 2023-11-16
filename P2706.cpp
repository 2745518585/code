#include<cstdio>
#include<algorithm>
using namespace std;
const int N=301;
int m,n,s,a[N][N],b[N][N],c[N][N],d[N][N][N];
int main()
{
    scanf("%d%d",&m,&n);
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            scanf("%d",&a[i][j]);
            b[i][j]=b[i][j-1]+a[i][j];
            c[i][j]=c[i][j-1]+(a[i][j]==0);
        }
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=i;j<=n;++j)
        {
            int w=0;
            for(int k=1;k<=m;++k)
            {
                if(c[k][j]-c[k][i-1]>0)
                {
                    w=0;
                    continue;
                }
                w+=b[k][j]-b[k][i-1];
                s=max(s,w);
            }
        }
    }
    printf("%d",s);
    return 0;
}