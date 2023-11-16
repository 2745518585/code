#include<bits/stdc++.h>
using namespace std;
const int N=1001;
const short dx[8]={-1,-1,-1,0,0,1,1,1},dy[8]={-1,0,1,-1,1,-1,0,1};
int n,a[N][N];
bool h[N][N],u1,u2;
struct str
{
    int x,y;
};
bool check(int x,int y)
{
    return x>=1&&x<=n&&y>=1&&y<=n;
}
void bfs(int sx,int sy,int k)
{
    queue<str> Q;
    Q.push((str){sx,sy});
    h[sx][sy]=true;
    while(!Q.empty())
    {
        int x=Q.front().x,y=Q.front().y;
        Q.pop();
        for(int i=0;i<8;++i)
        {
            if(check(x+dx[i],y+dy[i]))
            {
                if(a[x+dx[i]][y+dy[i]]>k) u1=false;
                else if(a[x+dx[i]][y+dy[i]]<k) u2=false;
            }
        }
        for(int i=0;i<8;++i)
        {
            if(check(x+dx[i],y+dy[i])&&!h[x+dx[i]][y+dy[i]]&&a[x+dx[i]][y+dy[i]]==k)
            {
                h[x+dx[i]][y+dy[i]]=true;
                Q.push((str){x+dx[i],y+dy[i]});
            }
        }
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            scanf("%d",&a[i][j]);
        }
    }
    int s1=0,s2=0;
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(h[i][j]==false)
            {
                u1=u2=true;
                bfs(i,j,a[i][j]);
                s1+=u1;
                s2+=u2;
            }
        }
    }
    printf("%d %d",s1,s2);
    return 0;
}