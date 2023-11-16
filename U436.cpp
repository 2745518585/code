#include<bits/stdc++.h>
using namespace std;
const int N=20001,M=10001;
const short dx[4]={-1,0,1,0},dy[4]={0,-1,0,1};
int n,m,k,a[N][2],b[N],h[M][M/30];
void add(int x,int y)
{
    h[x][y/30]^=(1<<(y%30));
}
bool check(int x,int y)
{
    return h[x][y/30]&(1<<(y%30));
}
int dfs(int x,int y)
{
    int s=1;
    add(x,y);
    for(int i=0;i<4;++i)
    {
        if(check(x+dx[i],y+dy[i])) s+=dfs(x+dx[i],y+dy[i]);
    }
    return s;
}
bool cmp(int a,int b)
{
    return a>b;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        a[i][0]=x,a[i][1]=y;
        add(x,y);
    }
    for(int i=1;i<=n;++i)
    {
        if(check(a[i][0],a[i][1]))
        {
            b[++k]=dfs(a[i][0],a[i][1]);
        }
    }
    sort(b+1,b+k+1,cmp);
    int s=0;
    for(int i=1;i<=m;++i) s+=b[i];
    printf("%d",s);
    return 0;
}