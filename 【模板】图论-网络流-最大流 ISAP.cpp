#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
const int N=10001,M=1000001;
int n,m,p=1,s1,s2,t[N],t0[N],f[N],g[N];
bool u=true;
struct road
{
    int m,q;
    ll r;
}a[M];
void road(int x,int y,ll r)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].r=r;
}
void bfs()
{
    queue<int> Q;
    Q.push(s2);
    f[s2]=1;
    g[1]=1;
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        for(int i=t[k];i!=0;i=a[i].q)
        {
            if(f[a[i].m]==0)
            {
                f[a[i].m]=f[k]+1;
                ++g[f[a[i].m]];
                Q.push(a[i].m);
            }
        }
    }
}
ll dfs(int x,ll r)
{
    if(x==s2) return r;
    ll s=0;
    for(int i=t0[x];i!=0;i=a[i].q)
    {
        t0[x]=i;
        if(f[x]==f[a[i].m]+1&&a[i].r!=0)
        {
            int z=dfs(a[i].m,min(r,a[i].r));
            if(z!=0)
            {
                a[i].r-=z;
                a[i^1].r+=z;
                r-=z;
                s+=z;
            }
            if(r==0) return s;
        }
    }
    --g[f[x]];
    if(g[f[x]]==0) u=false;
    ++f[x];
    ++g[f[x]];
    return s;
}
int main()
{
    scanf("%d%d%d%d",&n,&m,&s1,&s2);
    for(int i=1;i<=m;++i)
    {
        int x,y,r;
        scanf("%d%d%lld",&x,&y,&r);
        road(x,y,r);
        road(y,x,0);
    }
    bfs();
    ll r=0;
    while(u==true)
    {
        for(int i=1;i<=n;++i) t0[i]=t[i];
        r+=dfs(s1,1e18);
    }
    printf("%lld",r);
    return 0;
}