#include<cstdio>
#include<algorithm>
#include<stack>
#include<queue>
using namespace std;
const int N=2001,M=100001;
int n,m1,m2,p=1,q,tot,t[N],d[N],b[N],c[N],r[N],g[N],f[N][N];
bool h[N];
struct road
{
    int m,q,w;
}a[M];
stack<int> S;
void road(int x,int y,int w)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].w=w;
}
void dfs(int x)
{
    b[x]=c[x]=++tot;
    S.push(x);
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(b[a[i].m]==0)
        {
            dfs(a[i].m);
            c[x]=min(c[x],c[a[i].m]);
        }
        else if(h[a[i].m]==false)
        {
            c[x]=min(c[x],c[a[i].m]);
        }
    }
    if(b[x]==c[x])
    {
        ++q;
        while(S.top()!=x)
        {
            h[S.top()]=true;
            r[S.top()]=q;
            S.pop();
        }
        h[x]=true;
        r[x]=q;
        S.pop();
    }
}
int main()
{
    scanf("%d%d%d",&n,&m1,&m2);
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(i!=j) f[i][j]=1e9;
        }
    }
    for(int i=1;i<=m1;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        road(x,y,1);
        road(y,x,-1);
        f[x][y]=min(f[x][y],1);
        f[y][x]=min(f[y][x],-1);
    }
    for(int i=1;i<=m2;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        road(y,x,0);
        f[y][x]=min(f[y][x],0);
    }
    for(int i=1;i<=n;++i) h[i]=false;
    for(int i=1;i<=n;++i)
    {
        if(b[i]==0) dfs(i);
    }
    for(int k=1;k<=n;++k)
    {
        for(int i=1;i<=n;++i)
        {
            for(int j=1;j<=n;++j)
            {
                f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
            }
        }
    }
    for(int i=1;i<=n;++i)
    {
        if(f[i][i]<0)
        {
            printf("NIE");
            return 0;
        }
    }
    for(int i=1;i<=n;++i) g[i]=0;
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(r[i]==r[j]) g[r[i]]=max(g[r[i]],f[i][j]);
        }
    }
    int s=0;
    for(int i=1;i<=q;++i) s+=g[i]+1;
    printf("%d",s);
    return 0;
}