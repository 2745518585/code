#include<cstdio>
#include<algorithm>
using namespace std;
const int N=3001;
int n,m,a[N][N],b[N][N],c1[N],c2[N];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        char z[N];
        scanf("%s",z+1);
        for(int j=1;j<=n;++j)
        {
            ++a[i][j];
            if(z[j]=='R')
            {
                b[i][j]=0;
                a[i][j+1]+=a[i][j];
            }
            else
            {
                b[i][j]=1;
                a[i+1][j]+=a[i][j];
            }
        }
        scanf("%d",&c1[i]);
    }
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&c2[i]);
    }
    int s=0;
    for(int i=1;i<=n;++i)
    {
        s+=a[i][n+1]*c1[i]+a[n+1][i]*c2[i];
    }
    printf("%d\n",s);
    scanf("%d",&m);
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        int dx=x,dy=y;
        while(dx<=n&&dy<=n)
        {
            if(b[dx][dy]==0) ++dy;
            else ++dx;
            if(dy==n+1) s-=a[x][y]*c1[dx];
            if(dx==n+1) s-=a[x][y]*c2[dy];
            a[dx][dy]-=a[x][y];
        }
        b[x][y]^=1;
        dx=x,dy=y;
        while(dx<=n&&dy<=n)
        {
            if(b[dx][dy]==0) ++dy;
            else ++dx;
            if(dy==n+1) s+=a[x][y]*c1[dx];
            if(dx==n+1) s+=a[x][y]*c2[dy];
            a[dx][dy]+=a[x][y];
        }
        printf("%d\n",s);
    }
    return 0;
}