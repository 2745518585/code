#include<cstdio>
#include<algorithm>
using namespace std;
const int N=201;
short dx[4]={-1,0,0,1},dy[4]={0,-1,1,0};
int n,m,q,w,s,b[N][N];
bool a[N][N][4],h[N][N];
void dfs(int x,int y)
{
    h[x][y]=true;
    w+=b[x][y];
    for(int i=0;i<4;++i)
    {
        if(x+dx[i]>=1&&x+dx[i]<=n&&y+dy[i]>=1&&y+dy[i]<=n&&a[x][y][i]==false&&h[x+dx[i]][y+dy[i]]==false)
        {
            dfs(x+dx[i],y+dy[i]);
        }
    }
}
int main()
{
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=q;++i)
    {
        int x1,y1,x2,y2;
        scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
        for(int j=0;j<4;++j)
        {
            if(x1+dx[j]==x2&&y1+dy[j]==y2)
            {
                a[x1][y1][j]=true;
                a[x2][y2][3-j]=true;
                break;
            }
        }
    }
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        ++b[x][y];
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(h[i][j]==false)
            {
                w=0;
                dfs(i,j);
                s+=w*(m-w);
            }
        }
    }
    printf("%d",s/2);
    return 0;
}