#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
const int N=2001;
const short dx[4]={-1,0,1,0},dy[4]={0,-1,0,1};
int m,n,q,f[N][N];
char a[N][N];
int main()
{
    scanf("%d%d%d",&m,&n,&q);
    for(int i=1;i<=m;++i)
    {
        scanf("%s",a[i]+1);
    }
    queue<pair<int,int>> Q;
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(a[i][j]==a[i-1][j]||a[i][j]==a[i+1][j]||a[i][j]==a[i][j-1]||a[i][j]==a[i][j+1])
            {
                f[i][j]=0;
                Q.push(make_pair(i,j));
            }
            else f[i][j]=-1;
        }
    }
    while(!Q.empty())
    {
        int x=Q.front().first,y=Q.front().second;
        Q.pop();
        for(int i=0;i<4;++i)
        {
            if(f[x+dx[i]][y+dy[i]]==-1)
            {
                f[x+dx[i]][y+dy[i]]=f[x][y]+1;
                Q.push(make_pair(x+dx[i],y+dy[i]));
            }
        }
    }
    for(int i=1;i<=q;++i)
    {
        int x,y;
        ll t;
        scanf("%d%d%lld",&x,&y,&t);
        if(t<=f[x][y]||f[x][y]==-1) printf("%d\n",a[x][y]-'0');
        else printf("%d\n",(a[x][y]-'0')^((t-f[x][y])%2));
    }
    return 0;
}