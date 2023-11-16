#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=1000001,M=21;
int n,m,q,p=1,t[N],f[N],g[N][M];
vector<int> d[N];
struct road
{
    int m,q;
}a[N<<1];
struct tree
{
    int f,d;
}T[N];
struct str
{
    int x,y;
}c[N];
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
void dfs0(int x)
{
    T[x].d=T[T[x].f].d+1;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        T[a[i].m].f=x;
        dfs0(a[i].m);
    }
}
int find(int x,int y)
{
    int t=0;
    while(t>=0)
    {
        if(T[g[x][t]].d>T[y].d) x=g[x][t],++t;
        else --t;
    }
    return x;
}
void dfs(int x)
{
    for(int i=t[x];i!=0;i=a[i].q)
    {
        dfs(a[i].m);
        f[x]+=f[a[i].m];
    }
    for(int i=0;i<d[x].size();++i) f[x]=max(f[x],f[d[x][i]]+1);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=2;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        road(x,i);
    }
    dfs0(1);
    for(int i=1;i<=n;++i) g[i][0]=T[i].f;
    for(int i=1;i<=20;++i)
    {
        for(int j=1;j<=n;++j) g[j][i]=g[g[j][i-1]][i-1];
    }
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        if(T[x].d>T[y].d) swap(x,y);
        int z=find(y,x);
        if(T[z].f!=x)
        {
            c[++q]=(str){x,y};
            continue;
        }
        if(z==y)
        {
            printf("-1");
            return 0;
        }
        d[z].push_back(y);
    }
    dfs(1);
    int s=f[1];
    for(int i=1;i<=q;++i)
    {
        s=max(s,f[c[i].x]+f[c[i].y]+1);
    }
    printf("%d",s);
    return 0;
}