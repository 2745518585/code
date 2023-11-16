#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=101;
const short dx[9]={-1,-1,-1,0,0,0,1,1,1},dy[9]={-1,0,1,-1,0,1,-1,0,1};
int s1x,s1y,s2x,s2y;
char b[N][N];
bool h[N][N][N],g[N][N][N];
bool check(int x,int y,int t)
{
    if(x<1||x>8||y<1||y>8||t>20||(x-t+1>=1&&b[x-t+1][y]=='S')||(x-t>=1&&b[x-t][y]=='S')||h[x][y][t]) return false;
    return true;
}
void dfs(int x,int y,int t)
{
    h[x][y][t]=true;
    for(int i=0;i<=8;++i)
    {
        if(!check(x+dx[i],y+dy[i],t+1)) continue;
        dfs(x+dx[i],y+dy[i],t+1);
    }
}
int main()
{
    for(int i=1;i<=8;++i)
    {
        scanf("%s",b[i]+1);
        for(int j=1;j<=8;++j)
        {
            if(b[i][j]=='M') s1x=i,s1y=j;
            else if(b[i][j]=='A') s2x=i,s2y=j;
        }
    }
    dfs(s1x,s1y,0);
    bool u=false;
    for(int i=0;i<=20;++i) u|=h[s2x][s2y][i];
    if(u) printf("WIN");
    else printf("LOSE");
    return 0;
}