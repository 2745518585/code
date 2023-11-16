#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=21;
const short dx[4]={-1,0,1,0},dy[4]={0,-1,0,1};
int n,f[N][N][N][N][2][N*3];
int dfs(int ax,int ay,int bx,int by,int u,int w)
{
    if(ax==bx&&ay==by) return u==0?0:1e9;
    if(w>n*3) return 1e9;
    if(f[ax][ay][bx][by][u][w]!=-1) return f[ax][ay][bx][by][u][w];
    if(u==0)
    {
        f[ax][ay][bx][by][u][w]=0;
        for(int i=0;i<4;++i)
        {
            if(ax+dx[i]<1||ax+dx[i]>n||ay+dy[i]<1||ay+dy[i]>n) continue;
            f[ax][ay][bx][by][u][w]=max(f[ax][ay][bx][by][u][w],dfs(ax+dx[i],ay+dy[i],bx,by,u^1,w+1)+1);
        }
    }
    else
    {
        f[ax][ay][bx][by][u][w]=1e9;
        for(int i=0;i<4;++i)
        {
            for(int j=1;j<=2;++j)
            {
                if(bx+dx[i]*j<1||bx+dx[i]*j>n||by+dy[i]*j<1||by+dy[i]*j>n) continue;
                f[ax][ay][bx][by][u][w]=min(f[ax][ay][bx][by][u][w],dfs(ax,ay,bx+dx[i]*j,by+dy[i]*j,u^1,w+1)+1);
            }
        }
    }
    return f[ax][ay][bx][by][u][w];
}
int main()
{
    int ax,ay,bx,by;
    scanf("%d%d%d%d%d",&n,&ax,&ay,&bx,&by);
    if(abs(ax-bx)+abs(ay-by)==1)
    {
        printf("WHITE 1");
        return 0;
    }
    memset(f,-1,sizeof(f));
    printf("BLACK %d",dfs(ax,ay,bx,by,0,0));
    return 0;
}