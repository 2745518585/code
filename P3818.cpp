#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
const int N=1001;
const short dx[4]={-1,0,1,0},dy[4]={0,-1,0,1};
int m,n,s,t1,t2;
char a[N][N];
bool h[N][N][2];
struct str
{
    int x,y,u,t;
};
bool check(int x,int y,int u)
{
    return x>=1&&x<=m&&y>=1&&y<=n&&a[x][y]=='.'&&!h[x][y][u];
}
int bfs()
{
    queue<str> Q;
    Q.push((str){1,1,0,0});
    while(!Q.empty())
    {
        str k=Q.front();
        Q.pop();
        if(k.x==m&&k.y==n) return k.t;
        for(int i=0;i<4;++i)
        {
            if(check(k.x+dx[i],k.y+dy[i],k.u))
            {
                h[k.x+dx[i]][k.y+dy[i]][k.u]=true;
                Q.push((str){k.x+dx[i],k.y+dy[i],k.u,k.t+1});
            }
        }
        if(k.u==0&&check(k.x+t1,k.y+t2,1))
        {
            h[k.x+t1][k.y+t2][1]=true;
            Q.push((str){k.x+t1,k.y+t2,1,k.t+1});
        }
    }
    return -1;
}
int main()
{
    scanf("%d%d%d%d",&m,&n,&t1,&t2);
    for(int i=1;i<=m;++i)
    {
        scanf("%s",a[i]+1);
    }
    printf("%d",bfs());
    return 0;
}