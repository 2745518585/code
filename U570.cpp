#include<cstdio>
#include<algorithm>
#include<unordered_map>
using namespace std;
const int N=5;
const short dx[4]={-1,0,1,0},dy[4]={0,-1,0,1};
int sx,sy,a[N][N],b[N][N],c[N][N];
unordered_map<int,int> Map;
bool check()
{
    for(int i=1;i<=3;++i)
    {
        for(int j=1;j<=3;++j)
        {
            if(a[i][j]!=c[i][j]) return false;
        }
    }
    return true;
}
bool check2(int x,int y)
{
    return x>=1&&x<=3&&y>=1&&y<=3;
}
int sum()
{
    int s=0;
    for(int i=1;i<=3;++i)
    {
        for(int j=1;j<=3;++j)
        {
            s=s*9+a[i][j];
        }
    }
    return s;
}
void print()
{
    for(int i=1;i<=3;++i)
    {
        for(int j=1;j<=3;++j)
        {
            printf("%d ",a[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
bool dfs(int x,int y,int k,int t)
{
    if(k==t+1)
    {
        if(check())
        {
            printf("%d\n",t);
            print();
            return true;
        }
        return false;
    }
    int z=sum();
    if(Map.count(z)!=0&&Map[z]<k) return false;
    Map[z]=k;
    for(int i=0;i<4;++i)
    {
        if(check2(x+dx[i],y+dy[i]))
        {
            swap(a[x][y],a[x+dx[i]][y+dy[i]]);
            bool u=dfs(x+dx[i],y+dy[i],k+1,t);
            swap(a[x][y],a[x+dx[i]][y+dy[i]]);
            if(u)
            {
                print();
                return true;
            }
        }
    }
    return false;
}
int main()
{
    for(int i=1;i<=3;++i)
    {
        for(int j=1;j<=3;++j)
        {
            scanf("%d",&c[i][j]);
        }
    }
    for(int i=1;i<=3;++i)
    {
        for(int j=1;j<=3;++j)
        {
            scanf("%d",&b[i][j]);
            if(b[i][j]==0) sx=i,sy=j;
        }
    }
    for(int t=0;;++t)
    {
        for(int i=1;i<=3;++i)
        {
            for(int j=1;j<=3;++j)
            {
                a[i][j]=b[i][j];
            }
        }
        if(dfs(sx,sy,1,t)) return 0;
    }
    return 0;
}