#include<cstdio>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;
typedef long long ll;
const int N=600001,M=31;
int n,m,tot=1,a[N][2],b[N],fl[N],d[N][M][2],p[N];
ll f[N][M][2],g[N];
vector<int> e[N];
struct
{
    int l,r;
}c[N];
int add(char *x)
{
    int q=1;
    for(int i=1;x[i];++i)
    {
        if(a[q][x[i]-'0']==0) a[q][x[i]-'0']=++tot;
        q=a[q][x[i]-'0'];
    }
    return q;
}
void bfs()
{
    queue<int> Q;
    a[0][0]=a[0][1]=1;
    Q.push(1);
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        for(int i=0;i<=1;++i)
        {
            if(a[k][i])
            {
                fl[a[k][i]]=a[fl[k]][i];
                Q.push(a[k][i]);
            }
            else a[k][i]=a[fl[k]][i];
        }
    }
}
inline int popc(int x)
{
    int s=0;
    while(x) x^=x&-x,++s;
    return s;
}
void dfs(int x)
{
    for(auto i:e[x])
    {
        dfs(i);
        g[x]+=g[i];
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d",&c[i].l,&c[i].r);
    }
    for(int i=1;i<=m;++i)
    {
        static char z[N];
        scanf("%s",z+1);
        b[i]=add(z);
    }
    bfs();
    for(int i=0;i<=tot;++i)
    {
        d[i][0][0]=a[i][0];
        d[i][0][1]=a[i][1];
    }
    for(int i=1;i<=30;++i)
    {
        for(int j=0;j<=tot;++j)
        {
            d[j][i][0]=d[d[j][i-1][0]][i-1][1];
            d[j][i][1]=d[d[j][i-1][1]][i-1][0];
        }
    }
    int x=1;
    for(int i=1;i<=n;++i)
    {
        int l=c[i].l,r=c[i].r;
        for(int j=30;j>=0;--j)
        {
            p[j]=(l&(1<<j))!=0;
            p[j]^=p[j+1];
        }
        for(int j=0;j<=30;++j)
        {
            if((l&(1<<j))&&l+(1<<j)-1<=r)
            {
                ++f[x][j][p[j+1]^1];
                x=d[x][j][p[j+1]^1];
                l+=(1<<j);
            }
        }
        int t=popc(l)%2;
        for(int j=30;j>=0;--j)
        {
            if(l+(1<<j)-1<=r)
            {
                ++f[x][j][t];
                x=d[x][j][t];
                l+=(1<<j);
                t^=1;
            }
        }
    }
    for(int i=30;i>=1;--i)
    {
        for(int j=1;j<=tot;++j)
        {
            for(int k=0;k<=1;++k)
            {
                f[j][i-1][k]+=f[j][i][k];
                f[d[j][i-1][k]][i-1][k^1]+=f[j][i][k];
            }
        }
    }
    for(int i=1;i<=tot;++i)
    {
        g[a[i][0]]+=f[i][0][0];
        g[a[i][1]]+=f[i][0][1];
    }
    for(int i=2;i<=tot;++i) e[fl[i]].push_back(i);
    dfs(1);
    for(int i=1;i<=m;++i)
    {
        printf("%lld\n",g[b[i]]);
    }
    return 0;
}