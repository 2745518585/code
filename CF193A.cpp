#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=1001;
const short dx[4]={-1,0,1,0},dy[4]={0,-1,0,1};
int m,n,q,w;
char a[N][N];
bool h[N][N];
bool check(int x,int y)
{
    return x>=1&&x<=m&&y>=1&&y<=n&&a[x][y]=='#'&&!h[x][y];
}
void dfs0(int x,int y)
{
    ++q;
    h[x][y]=true;
    for(int i=0;i<4;++i)
    {
        if(check(x+dx[i],y+dy[i])) dfs0(x+dx[i],y+dy[i]);
    }
}
void dfs(int x,int y)
{
    ++w;
    h[x][y]=true;
    for(int i=0;i<4;++i)
    {
        if(check(x+dx[i],y+dy[i])) dfs(x+dx[i],y+dy[i]);
    }
}
int main()
{
    scanf("%d%d",&m,&n);
    for(int i=1;i<=m;++i)
    {
        scanf("%s",a[i]+1);
    }
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(a[i][j]!='#') continue;
            if(q==0) dfs0(i,j);
            memset(h,false,sizeof(h));
            h[i][j]=true;
            w=0;
            for(int k=0;k<4;++k)
            {
                if(check(i+dx[k],j+dy[k]))
                {
                    dfs(i+dx[k],j+dy[k]);
                    break;
                }
            }
            if(w!=q-1)
            {
                printf("1");
                return 0;
            }
        }
    }
    printf("2");
    return 0;
}