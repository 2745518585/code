#include<cstdio>
#include<algorithm>
using namespace std;
const int N=10001,M=1001,inf=1000000000;
int n,m,b[N],f[N][M],p=1,t[N];
struct road
{
    int m,q;
}a[N];
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
void dfs(int x)
{
	f[x][1]=b[x];
    for(int i=t[x];i!=0;i=a[i].q)
    {
        dfs(a[i].m);
        for(int j=m+1;j>=1;--j)
        {
            for(int k=0;k<j;++k)
            {
                f[x][j]=max(f[x][j],f[x][j-k]+f[a[i].m][k]);
            }
        }
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        int x;
        scanf("%d%d",&x,&b[i]);
        if(x==0) x=n+1;
        road(x,i);
    }
    dfs(n+1);
	printf("%d",f[n+1][m+1]);
    return 0;
}
