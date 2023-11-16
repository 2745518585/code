#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=6001;
int n,m,q,p=1,t[N],t2[N],c[N],fa[N];
bool g[N],h[N],d1[N][N],d2[N][N];
vector<int> b[N];
struct road
{
    int m,q;
}a[N<<1];
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
void road2(int x,int y)
{
    a[++p].m=y;
    a[p].q=t2[x];
    t2[x]=p;
}
bool cmp(int x,int y)
{
    return b[x].size()<b[y].size();
}
void dfs(int x)
{
    if(h[x]||g[x]) return;
    h[x]=true;
    for(int i=t[x];i!=0;i=a[i].q) dfs(a[i].m);
}
void dfs2(int x)
{
    if(h[x]||g[x]) return;
    h[x]=true;
    for(int i=t2[x];i!=0;i=a[i].q) dfs2(a[i].m);
}
int main()
{
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        road(x,y);
        road2(y,x);
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j) h[j]=false;
        g[i]=true;
        if(!g[1]) dfs(1);
        g[i]=false;
        for(int j=1;j<=n;++j)
        {
            d1[i][j]=h[j];
            if(h[j]==false) b[j].push_back(i);
        }
    }
    for(int i=1;i<=n;++i) c[i]=i;
    sort(c+1,c+n+1,cmp);
    for(int i=2;i<=n;++i)
    {
        int x=0;
        for(auto j:b[c[i]])
        {
            if(b[j].size()>b[x].size()&&c[i]!=j) x=j;
        }
        fa[c[i]]=x;
        for(int j=1;j<=n;++j) h[j]=false;
        g[fa[c[i]]]=true;
        dfs2(c[i]);
        g[fa[c[i]]]=false;
        for(int j=1;j<=n;++j) d2[c[i]][j]=h[j];
    }
    for(int i=1;i<=q;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        for(int j=1;j<=n;++j) h[j]=false;
        for(int j=2;j<=n;++j)
        {
            if(d1[fa[j]][x]&&d2[j][y]) h[j]=true;
        }
        for(int j=1;j<=n;++j) h[c[j]]|=h[fa[c[j]]];
        int s=0;
        for(int j=1;j<=n;++j) s+=h[j];
        printf("%d\n",s);
    }
    return 0;
}