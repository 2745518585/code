#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=1001;
int m,n,p=1,t[N*N],c[N][N],g[N*N];
bool h[N*N];
char b[N][N];
struct road
{
    int m,q;
}a[N*N];
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
bool dfs(int x)
{
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(h[a[i].m]) continue;
        h[a[i].m]=true;
        if(g[a[i].m]==0||dfs(g[a[i].m]))
        {
            g[a[i].m]=x;
            return true;
        }
    }
    return false;
}
int main()
{
    scanf("%d%d",&m,&n);
    for(int i=1;i<=m;++i)
    {
        scanf("%s",b[i]+1);
    }
    int q=0,w=0;
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(b[i][j]=='.') continue;
            c[i][j]=++q;
        }
    }
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(b[i][j]=='.') continue;
            if(b[i-1][j]=='#') ++w;
            if(b[i][j-1]=='#') ++w;
            if(b[i-1][j]=='#'&&b[i][j-1]=='#') road(c[i-1][j],c[i][j-1]);
            if(b[i-1][j]=='#'&&b[i][j+1]=='#') road(c[i-1][j],c[i][j]);
            if(b[i+1][j]=='#'&&b[i][j-1]=='#') road(c[i][j],c[i][j-1]);
            if(b[i+1][j]=='#'&&b[i][j+1]=='#') road(c[i][j],c[i][j]);
        }
    }
    int s=0;
    for(int i=1;i<=q;++i)
    {
        for(int j=1;j<=q;++j) h[j]=false;
        s+=dfs(i);
    }
    printf("%d",q-(w-s));
    return 0;
}