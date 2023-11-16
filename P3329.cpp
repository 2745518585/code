#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
const int N=5001,M=100001;
int n,m,q,p=1,t[N],f[N][N],g[N];
vector<pair<int,int>> b[N];
struct road
{
    int m,q,r;
}a[M];
void addroad(int x,int y,int r)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].r=r;
}
namespace mf
{
    int s1,s2,t[N],t0[N],f[N];
    road a[M];
    bool bfs()
    {
        queue<int> Q;
        Q.push(s1);
        for(int i=1;i<=n;++i) f[i]=0;
        f[s1]=1;
        while(!Q.empty())
        {
            int k=Q.front();
            Q.pop();
            for(int i=t[k];i!=0;i=a[i].q)
            {
                if(f[a[i].m]==0&&a[i].r!=0)
                {
                    f[a[i].m]=f[k]+1;
                    Q.push(a[i].m);
                }
            }
        }
        return f[s2]!=0;
    }
    int dfs(int x,int r)
    {
        if(x==s2) return r;
        int s=0;
        for(int i=t0[x];i!=0;i=a[i].q)
        {
            t0[x]=i;
            if(f[a[i].m]==f[x]+1&&a[i].r!=0)
            {
                int z=dfs(a[i].m,min(r,a[i].r));
                if(z!=0)
                {
                    a[i].r-=z;
                    a[i^1].r+=z;
                    r-=z;
                    s+=z;
                }
                else f[a[i].m]=0;
                if(r==0) return s;
            }
        }
        return s;
    }
    int maxflow()
    {
        int r=0;
        while(bfs())
        {
            for(int i=1;i<=n;++i) t0[i]=t[i];
            r+=dfs(s1,1e9);
        }
        return r;
    }
};
void dfs(int x,int *f,int fa)
{
    for(auto i:b[x])
    {
        if(i.first==fa) continue;
        f[i.first]=min(f[x],i.second);
        dfs(i.first,f,x);
    }
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        p=1;
        for(int i=1;i<=n;++i) t[i]=0;
        for(int i=1;i<=m;++i)
        {
            int x,y,r;
            scanf("%d%d%d",&x,&y,&r);
            addroad(x,y,r);
            addroad(y,x,r);
        }
        for(int i=1;i<=n;++i) g[i]=1,b[i].clear();
        while(true)
        {
            int x=0,y=0;
            for(int j=1;j<=n;++j)
            {
                if(g[j]!=j)
                {
                    x=j;
                    break;
                }
            }
            if(x==0) break;
            y=g[x];
            for(int j=1;j<=n;++j) mf::t[j]=t[j];
            for(int j=2;j<=p;++j) mf::a[j]=a[j];
            mf::s1=x,mf::s2=y;
            int r=mf::maxflow();
            b[x].push_back(make_pair(y,r));
            b[y].push_back(make_pair(x,r));
            int z=g[x];
            for(int j=1;j<=n;++j)
            {
                if(g[j]==z)
                {
                    if(mf::f[j]) g[j]=x;
                    else g[j]=y;
                }
            }
        }
        for(int i=1;i<=n;++i)
        {
            for(int j=1;j<=n;++j) f[i][j]=0;
            f[i][i]=1e9;
            dfs(i,f[i],0);
        }
        scanf("%d",&q);
        for(int i=1;i<=q;++i)
        {
            int x;
            scanf("%d",&x);
            int s=0;
            for(int j=1;j<=n;++j)
            {
                for(int k=j+1;k<=n;++k)
                {
                    if(f[j][k]<=x) ++s;
                }
            }
            printf("%d\n",s);
        }
        printf("\n");
    }
    return 0;
}