#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
const int N=201,M=21;
const short dx[4]={-1,0,1,0},dy[4]={0,-1,0,1};
int m,n,s,s1,s2,t1,t2,a[N][N],f[N][N][M];
struct str
{
    int x,y,d,t;
    friend bool operator <(str a,str b)
    {
        return a.t>b.t;
    }
};
bool check(int x,int y,int d,int t,int q)
{
    for(int i=1;i<=q;++i)
    {
        x+=dx[d],y+=dy[d];
        if(!(x>=1&&x<=m&&y>=1&&y<=n&&a[x][y])) return false;
    }
    return x>=1&&x<=m&&y>=1&&y<=n&&a[x][y]&&t+q<f[x][y][d];
}
int bfs(int q)
{
    priority_queue<str> Q;
    Q.push((str){s1,s2,-1,0});
    while(!Q.empty())
    {
        str k=Q.top();
        Q.pop();
        if(k.x==t1&&k.y==t2) return min(k.t,s);
        if(k.x>t1&&k.y==t2&&check(k.x,k.y,0,k.t,k.x-t1)) s=min(s,k.t+k.x-t1);
        else if(k.x==t1&&k.y>t2&&check(k.x,k.y,1,k.t,k.y-t2)) s=min(s,k.t+k.y-t2);
        else if(k.x<t1&&k.y==t2&&check(k.x,k.y,2,k.t,t1-k.x)) s=min(s,k.t+t1-k.x);
        else if(k.x==t1&&k.y<t2&&check(k.x,k.y,3,k.t,t2-k.y)) s=min(s,k.t+t2-k.y);
        if(k.d!=-1&&check(k.x,k.y,k.d,k.t,1))
        {
            f[k.x+dx[k.d]][k.y+dy[k.d]][k.d]=k.t+1;
            Q.push((str){k.x+dx[k.d],k.y+dy[k.d],k.d,k.t+1});
        }
        for(int i=0;i<4;++i)
        {
            if(i==k.d) continue;
            if(check(k.x,k.y,i,k.t,q))
            {
                f[k.x+dx[i]*q][k.y+dy[i]*q][i]=k.t+q;
                Q.push((str){k.x+dx[i]*q,k.y+dy[i]*q,i,k.t+q});
            }
        }
    }
    return s;
}
int main()
{
    scanf("%d%d%d%d%d%d",&m,&n,&s1,&s2,&t1,&t2);
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            scanf("%d",&a[i][j]);
        }
    }
    for(int r=1;r<=10;++r)
    {
        for(int i=1;i<=m;++i)
        {
            for(int j=1;j<=n;++j)
            {
                for(int l=0;l<4;++l)
                {
                    f[i][j][l]=1e9;
                }
            }
        }
        s=1e9;
        int z=bfs(r);
        if(z!=1e9) printf("%d %d\n",r,z);
        else break;
    }
    return 0;
}