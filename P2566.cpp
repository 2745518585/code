#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
const int N=12;
const short dx[4]={-1,1,0,0},dy[4]={0,0,-1,1};
int m,n,k,b[N],c[N][N],f[N][N][1<<N],g[1<<N];
bool h[N][N][1<<N];
char a[N][N];
struct str
{
    int x,y,k;
    str(){}
    str(int x,int y,int k):x(x),y(y),k(k){}
};
int check(int x,int y)
{
    int s=0;
    for(int i=y+1;i<=n;++i)
    {
        if(a[x][i]!='0'&&a[x][i]!='#') s|=(1<<(a[x][i]-'0'-1));
    }
    return s;
}
int SPFA(int x,int y)
{
    queue<str> Q;
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            for(int l=0;l<=(1<<k)-1;++l) f[i][j][l]=1e9;
        }
    }
    f[x][y][0]=0;
    h[x][y][0]=true;
    Q.push(str(x,y,0));
    while(!Q.empty())
    {
        str k=Q.front();
        Q.pop();
        if(h[k.x][k.y][k.k]==false) continue;
        h[k.x][k.y][k.k]=false;
        for(int i=0;i<=3;++i)
        {
            if(a[k.x+dx[i]][k.y+dy[i]]!='0') continue;
            int z=k.k;
            if(i==0) z=k.k^c[k.x+dx[i]][k.y+dy[i]];
            else if(i==1) z=k.k^c[k.x][k.y];
            if(f[k.x][k.y][k.k]+1<f[k.x+dx[i]][k.y+dy[i]][z])
            {
                f[k.x+dx[i]][k.y+dy[i]][z]=f[k.x][k.y][k.k]+1;
                h[k.x+dx[i]][k.y+dy[i]][z]=true;
                Q.push(str(k.x+dx[i],k.y+dy[i],z));
            }
        }
    }
    int s=0;
    for(int i=0;i<=(1<<k)-1;++i)
    {
        s=max(s,g[i]-f[x][y][i]);
    }
    return s;
}
int main()
{
    scanf("%d%d%d",&m,&n,&k);
    for(int i=1;i<=k;++i)
    {
        scanf("%d",&b[i]);
    }
    for(int i=1;i<=m;++i)
    {
        scanf("%s",a[i]+1);
    }
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            c[i][j]=check(i,j);
        }
    }
    for(int i=0;i<=(1<<k)-1;++i)
    {
        for(int j=1;j<=k;++j)
        {
            if((i&(1<<(j-1)))!=0) g[i]+=b[j];
        }
    }
    int s=0;
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            s=max(s,SPFA(i,j));
        }
    }
    printf("%d",s);
    return 0;
}