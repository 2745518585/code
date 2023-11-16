#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1001;
int n,m,a[N][N],*b[N];
bool h[N];
char z[N];
int main()
{
    scanf("%d%d",&n,&m);
    int s=0,u=0;
    for(int i=1;i<=n;++i)
    {
        scanf("%s",z+1);
        for(int j=1;j<=m;++j)
        {
            a[i][j]=z[m-j+1]-'0';
            if(a[i][j]==1) u=1;
        }
    }
    for(int i=2;i<=n;++i)
    {
        for(int j=1;j<=m;++j) a[i][j]^=a[1][j];
    }
    for(int i=1;i<=m;++i) a[1][i]=0;
    for(int i=1;i<=n;++i)
    {
        for(int j=m;j>=1;--j)
        {
            if(a[i][j]==0) continue;
            if(h[j]==false)
            {
                b[j]=a[i];
                h[j]=true;
                ++s;
                break;
            }
            for(int k=1;k<=m;++k) a[i][k]^=b[j][k];
        }
    }
    printf("%d",max(s,u));
    return 0;
}