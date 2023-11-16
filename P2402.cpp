#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
const int N=10001,M=100001;
int n,m,p=1,p2=1,s1,s2,t[N],t2[N],t0[N],f[N];
ll c[N][2],g[N][N],q;
bool h[N];
struct road
{
    int m,q;
    ll r;
}a[M];
struct road2
{
    int m,q;
    ll w;
}b[M];
void road(int x,int y,ll r)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].r=r;
}
void road2(int x,int y,ll w)
{
    b[++p2].m=y;
    b[p2].q=t2[x];
    t2[x]=p2;
    b[p2].w=w;
}
bool bfs()
{
    queue<int> Q;
    Q.push(s1);
    for(int i=1;i<=s2;++i) f[i]=0;
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
ll dfs(int x,ll r)
{
    if(x==s2) return r;
    ll s=0;
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
void SPFA(int x)
{
    for(int i=1;i<=n;++i)
    {
        g[x][i]=1e18+1;
        h[i]=false;
    }
    g[x][x]=0;
    h[x]=true;
	queue<int> Q;
	Q.push(x);
    while(!Q.empty()) 
    {
        int k=Q.front();
        Q.pop();
        if(h[k]==false) continue;
        h[k]=false;
        for(int i=t2[k];i!=0;i=b[i].q)
        {
            if(g[x][k]+b[i].w<g[x][b[i].m])
            {
                g[x][b[i].m]=g[x][k]+b[i].w;
                h[b[i].m]=true;
                Q.push(b[i].m);
            }
        }
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    s1=n*2+1,s2=n*2+2;
    for(int i=1;i<=n;++i)
    {
        scanf("%lld%lld",&c[i][0],&c[i][1]);
        q+=c[i][0];
    }
    for(int i=1;i<=m;++i)
    {
        int x,y;
        ll w;
        scanf("%d%d%lld",&x,&y,&w);
        road2(x,y,w);
        road2(y,x,w);
    }
    for(int i=1;i<=n;++i) SPFA(i);
    ll s=0,l=0,r=1e18;
    while(l<r)
    {
        ll z=l+r>>1;
        p=1;
        for(int i=1;i<=s2;++i) t[i]=0;
        for(int i=1;i<=n;++i)
        {
            road(s1,i,c[i][0]);
            road(i,s1,0);
            road(n+i,s2,c[i][1]);
            road(s2,n+i,0);
        }
        for(int i=1;i<=n;++i)
        {
            for(int j=1;j<=n;++j)
            {
                if(g[i][j]<=z)
                {
                    road(i,n+j,1e18);
                    road(n+j,i,0);
                }
            }
        }
        ll s=0;
        while(bfs())
        {
            for(int i=1;i<=s2;++i) t0[i]=t[i];
            s+=dfs(s1,1e18);
        }
        if(s>=q) r=z;
        else l=z+1;
    }
    printf("%lld",l==1e18?-1:l);
    return 0;
}