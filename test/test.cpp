#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
typedef long long ll;
const int N=200001,M=21;
int n,q,rt,q1,q2,b[N],e[N],d[N][M],fa[N],g[N],t[N];
ll f[N];
bool h[N],p[N];
vector<int> a[N],c[N];
struct tree
{
    int s,ms,d;
}T[N];
struct str
{
    int x;
    ll w;
    str() {}
    str(int x,ll w):x(x),w(w) {}
    friend bool operator<(const str &a,const str &b)
    {
        return a.w>b.w;
    }
};
priority_queue<str> Q;
void dfs0(int x,int fa)
{
    ++q;
    for(auto i:a[x])
    {
        if(i==fa||g[i]) continue;
        dfs0(i,x);
    }
}
void dfs1(int x,int fa,int t)
{
    T[x].s=1;
    T[x].ms=0;
    d[x][t]=-1;
    for(auto i:a[x])
    {
        if(i==fa||g[i]) continue;
        dfs1(i,x,t);
        T[x].s+=T[i].s;
        T[x].ms=max(T[x].ms,T[i].s);
    }
    T[x].ms=max(T[x].ms,q-T[x].s);
    if(T[x].ms<T[rt].ms) rt=x;
}
void solve(int x,int t)
{
    queue<int> Q;
    Q.push(x);
    d[x][t]=0;
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        c[x].push_back(k);
        for(auto i:a[k])
        {
            if(g[i]||d[i][t]!=-1) continue;
            d[i][t]=d[k][t]+1;
            Q.push(i);
        }
    }
}
int dfs(int x,int t)
{
    rt=q=0;
    dfs0(x,0);
    dfs1(x,0,t);
    solve(rt,t);
    g[rt]=t;
    int p=rt;
    for(auto i:a[p])
    {
        if(g[i]) continue;
        fa[dfs(i,t+1)]=p;
    }
    return p;
}
void find(int x,int e)
{
    int rt=x;
    while(rt)
    {
        while(t[rt]<c[rt].size()&&d[c[rt][t[rt]]][g[rt]]+d[x][g[rt]]<=e)
        {
            int z=c[rt][t[rt]];
            if(!p[z])
            {
                if(f[x]+b[z]<f[z])
                {
                    f[z]=f[x]+b[z];
                    Q.push(str(z,f[z]));
                }
                p[z]=true;
            }
            ++t[rt];
        }
        rt=fa[rt];
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&b[i]);
    }
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&e[i]);
    }
    for(int i=1;i<=n-1;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        a[x].push_back(y);
        a[y].push_back(x);
    }
    T[0].ms=1e9;
    dfs(1,1);
    for(int i=1;i<=n;++i) f[i]=1e18;
    f[1]=b[1];
    Q.push(str(1,0));
    while(!Q.empty())
    {
        int k=Q.top().x;
        Q.pop();
        if(h[k]) continue;
        h[k]=true;
        find(k,e[k]);
    }
    for(int i=1;i<=n;++i)
    {
        printf("%lld",f[i]-b[i]);
        if(i<n) printf(" ");
    }
    printf("\n");
    return 0;
}