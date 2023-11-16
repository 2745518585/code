#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
const int N=1001,M=1000001;
int n,m,k,p=1,s1,s2,t1,t2,tot,t[M],t0[M];
ll v,f[M],b[M],g[N][N];
bool h[M];
struct road
{
    int m,q;
    ll r,w;
}a[M];
void road(int x,int y,ll r,ll w)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].r=r;
    a[p].w=w;
    a[++p].m=x;
    a[p].q=t[y];
    t[y]=p;
    a[p].r=0;
    a[p].w=-w;
}
bool SPFA()
{
    queue<int> Q;
    Q.push(s1);
    for(int i=1;i<=tot;++i)
    {
        f[i]=1e18;
        h[i]=false;
    }
    f[s1]=0;
    h[s1]=true;
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        if(h[k]==false) continue;
        h[k]=false;
        for(int i=t[k];i!=0;i=a[i].q)
        {
            if(a[i].r>0&&f[k]+a[i].w<f[a[i].m])
            {
                f[a[i].m]=f[k]+a[i].w;
                Q.push(a[i].m);
                h[a[i].m]=true;
            }
        }
    }
    return f[s2]!=1e18;
}
ll dfs(int x,ll r)
{
    if(x==s2) return r;
    ll s=0;
    for(int i=t0[x];i!=0;i=a[i].q)
    {
        t0[x]=i;
        if(h[a[i].m]==false&&a[i].r>0&&f[a[i].m]==f[x]+a[i].w)
        {
            h[a[i].m]=true;
            ll z=dfs(a[i].m,min(r,a[i].r));
            h[a[i].m]=false;
            if(z!=0)
            {
                a[i].r-=z;
                a[i^1].r+=z;
                r-=z;
                s+=z;
                v+=z*a[i].w;
            }
            else f[a[i].m]=0;
            if(r==0) return s; 
        }
    }
    return s;
}
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    t1=1,t2=n*2+2,s1=n*2+3,s2=n*2+4,tot=n*2+4;
    road(1,2,k,0);
    for(int i=1;i<=n;++i)
    {
        ++b[i*2+1];
        --b[i*2+2];
        road(i*2+1,i*2+2,1e18,0);
    }
    for(int i=0;i<=n-1;++i)
    {
        road(i*2+2,n*2+2,1e18,0);
    }
    for(int i=0;i<=n;++i)
    {
        for(int j=0;j<=n;++j) g[i][j]=1e18;
        g[i][i]=0;
    }
    for(int i=1;i<=m;++i)
    {
        int x,y;
        ll w;
        scanf("%d%d%lld",&x,&y,&w);
        g[x][y]=min(g[x][y],w);
        g[y][x]=min(g[y][x],w);
    }
    for(int l=0;l<=n;++l)
    {
        for(int i=0;i<=n;++i)
        {
            for(int j=0;j<=n;++j)
            {
                g[i][j]=min(g[i][j],g[i][l]+g[l][j]);
            }
        }
        for(int i=0;i<=l-1;++i)
        {
            road(i*2+2,l*2+1,1e18,g[i][l]);
        }
    }
    for(int i=1;i<=tot;++i)
    {
        if(b[i]<0)
        {
            road(s1,i,-b[i],0);
        }
        else if(b[i]>0)
        {
            road(i,s2,b[i],0);
        }
    }
    road(t2,t1,1e18,0);
    ll r=0;
    while(SPFA())
    {
        for(int i=1;i<=tot;++i)
        {
            t0[i]=t[i];
            h[i]=false;
        }
        r+=dfs(s1,1e18);
    }
    printf("%lld",v);
    return 0;
}