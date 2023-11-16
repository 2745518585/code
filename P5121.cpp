#include<cstdio>
#include<algorithm>
using namespace std;
const int N=101;
const short dx[4]={-1,0,1,0},dy[4]={0,-1,0,1};
int n,m,q,w,a[N][11];
bool h[N][11];
bool check(int x,int y)
{
    return x>=1&&x<=n&&y>=1&&y<=10;
}
void dfs(int x,int y)
{
    h[x][y]=true;
    ++w;
    for(int i=0;i<4;++i)
    {
        if(check(x+dx[i],y+dy[i])&&!h[x+dx[i]][y+dy[i]]&&a[x+dx[i]][y+dy[i]]==a[x][y])
        {
            dfs(x+dx[i],y+dy[i]);
        }
    }
}
void dfs2(int x,int y,int k)
{
    a[x][y]=0;
    for(int i=0;i<4;++i)
    {
        if(check(x+dx[i],y+dy[i])&&a[x+dx[i]][y+dy[i]]==k)
        {
            dfs2(x+dx[i],y+dy[i],k);
        }
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    q=n;
    for(int i=n;i>=1;--i)
    {
        char z[20];
        scanf("%s",z+1);
        for(int j=1;j<=10;++j)
        {
            a[i][j]=z[j]-'0';
        }
    }
    while(true)
    {
        for(int i=1;i<=q;++i)
        {
            for(int j=1;j<=10;++j)
            {
                h[i][j]=false;
            }
        }
        bool u=false;
        for(int i=1;i<=q;++i)
        {
            for(int j=1;j<=10;++j)
            {
                if(h[i][j]==false&&a[i][j]!=0)
                {
                    w=0;
                    dfs(i,j);
                    if(w>=m)
                    {
                        dfs2(i,j,a[i][j]);
                        u=true;
                    }
                }
            }
        }
        if(u==false) break;
        int d=0;
        for(int i=1;i<=10;++i)
        {
            int x=1;
            for(int j=1;j<=q;++j)
            {
                if(a[j][i]!=0)
                {
                    a[x][i]=a[j][i];
                    if(x!=j) a[j][i]=0;
                    ++x;
                }
            }
            d=max(d,x-1);
        }
        q=d;
        if(q==0) break;
    }
    for(int i=n;i>=1;--i)
    {
        for(int j=1;j<=10;++j)
        {
            printf("%d",a[i][j]);
        }
        printf("\n");
    }
    return 0;
}