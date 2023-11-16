#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
const int N=1001;
const short dx[4]={-1,0,1,0},dy[4]={0,-1,0,1};
int n,m,f[N][N];
bool h[N][N];
char a[N][N];
struct str
{
    str(){}
    str(int x,int y):x(x),y(y){}
    int x,y;
}s1,s2;
bool check1(int x,int y)
{
    return x>=1&&x<=m&&y>=1&&y<=n&&a[x][y]!='#';
}
bool check2(int x,int y)
{
    return a[x-1][y]=='#'||a[x][y-1]=='#'||a[x+1][y]=='#'||a[x][y+1]=='#';
}
str check(int x,int y,int d)
{
    while(check1(x+dx[d],y+dy[d])) x+=dx[d],y+=dy[d];
    if(a[x+dx[d]][y+dy[d]]=='#') return str(x,y);
    return str(1e9,1e9);
}
int main()
{
    scanf("%d%d",&m,&n);
    for(int i=1;i<=m;++i)
    {
        scanf("%s",a[i]+1);
        for(int j=1;j<=n;++j)
        {
            if(a[i][j]=='C') s1=str(i,j);
            else if(a[i][j]=='F') s2=str(i,j);
        }
    }
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            f[i][j]=1e9;
        }
    }
    f[s1.x][s1.y]=0;
    h[s1.x][s1.y]=true;
    queue<str> Q;
    Q.push(s1);
    while(!Q.empty()) 
    {
        str k=Q.front();
        Q.pop();
        if(h[k.x][k.y]==false) continue;
        h[k.x][k.y]=false;
        for(int i=0;i<=3;++i)
        {
            if(check1(k.x+dx[i],k.y+dy[i])&&f[k.x][k.y]+1<f[k.x+dx[i]][k.y+dy[i]])
            {
                f[k.x+dx[i]][k.y+dy[i]]=f[k.x][k.y]+1;
                h[k.x+dx[i]][k.y+dy[i]]=true;
                Q.push(str(k.x+dx[i],k.y+dy[i]));
            }
        }
        int q=1e9;
        for(int i=0;i<=3;++i)
        {
            str z=check(k.x,k.y,i);
            q=min(q,abs(k.x-z.x)+abs(k.y-z.y));
        }
        for(int i=0;i<=3;++i)
        {
            str z=check(k.x,k.y,i);
            if(f[k.x][k.y]+q+1<f[z.x][z.y])
            {
                f[z.x][z.y]=f[k.x][k.y]+q+1;
                h[z.x][z.y]=true;
                Q.push(z);
            }
        }
    }
    if(f[s2.x][s2.y]==1e9) printf("nemoguce");
    else printf("%d",f[s2.x][s2.y]);
    return 0;
}