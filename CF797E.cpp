#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
const int N=100001,M=401;
int n,m,q,a[N],f[N][M];
int check(int x,int y)
{
    int s=0;
    while(x<=n) x=x+a[x]+y,++s;
    return s;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    q=sqrt(n);
    for(int i=1;i<=q;++i)
    {
        for(int j=n;j>=1;--j)
        {
            if(j+a[j]+i>n) f[j][i]=1;
            else f[j][i]=f[j+a[j]+i][i]+1;
        }
    }
    scanf("%d",&m);
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        if(y<=q) printf("%d\n",f[x][y]);
        else printf("%d\n",check(x,y));
    }
    return 0;
}