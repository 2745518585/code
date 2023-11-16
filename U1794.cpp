#include<cstdio>
#include<queue>
using namespace std;
const int N=5001;
const short dx[8]={-2,-2,-1,-1,1,1,2,2},dy[8]={-1,1,-2,2,-2,2,-1,1};
int n,x1,y1,x2,y2;
bool h[N][N];
struct str
{
    int x,y,t;
};
bool check(int x,int y)
{
    return x>=1&&x<=n&&y>=1&&y<=n&&h[x][y]==false;
}
int bfs()
{
    queue<str> Q;
    Q.push((str){x1,y1,0});
    h[x1][y1]=true;
    while(!Q.empty())
    {
        str k=Q.front();
        Q.pop();
        if(k.x==x2&&k.y==y2) return k.t;
        for(int i=0;i<8;++i)
        {
            if(check(k.x+dx[i],k.y+dy[i]))
            {
                h[k.x+dx[i]][k.y+dy[i]]=true;
                Q.push((str){k.x+dx[i],k.y+dy[i],k.t+1});
            }
        }
    }
    return -1;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d%d%d",&n,&x1,&y1,&x2,&y2);
        ++x1,++y1,++x2,++y2,++n;
        for(int i=1;i<=n;++i)
        {
            for(int j=1;j<=n;++j)
            {
                h[i][j]=false;
            }
        }
        if(x1==x2&&y1==y2)
        {
            printf("0\n");
            continue;
        }
        printf("%d\n",bfs());
    }
    return 0;
}