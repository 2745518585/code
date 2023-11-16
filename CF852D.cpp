#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
const int N=5001,M=1000001;
int n,m,q,k,p=1,s1,s2,t[N],p2=1,t2[N],t0[N],b[N],f[N],g[N][N];
bool h[N];
struct road
{
    int m,q;
    ll r;
}a[M];
struct road2
{
    int m,q,w;
}a2[M];
void road(int x,int y,ll r)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].r=r;
}
void road2(int x,int y,int w)
{
    a2[++p2].m=y;
    a2[p2].q=t2[x];
    t2[x]=p2;
    a2[p2].w=w;
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
            ll z=dfs(a[i].m,min(r,a[i].r));
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
bool check(int x)
{
    p=1;
    for(int i=1;i<=s2;++i) t[i]=0;
    for(int i=1;i<=q;++i)
    {
        road(s1,b[i],1);
        road(b[i],s1,0);
    }
    for(int i=1;i<=n;++i)
    {
        road(n+i,s2,1);
        road(s2,n+i,0);
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(g[i][j]<=x)
            {
                road(i,n+j,1);
                road(n+j,i,0);
            }
        }
    }
    ll r=0;
    while(bfs())
    {
        for(int i=1;i<=s2;++i) t0[i]=t[i];
        r+=dfs(s1,1e18);
    }
    return r>=k;
}
void SPFA0(int x,int f[])
{
    queue<int> Q;
    for(int i=1;i<=n;++i) f[i]=1e9,h[i]=false;
    f[x]=0;
    h[x]=true;
    Q.push(x);
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        if(h[k]==false) continue;
        h[k]=false;
        for(int i=t2[k];i!=0;i=a2[i].q)
        {
            if(f[k]+a2[i].w<f[a2[i].m])
            {
                f[a2[i].m]=f[k]+a2[i].w;
                h[a2[i].m]=true;
                Q.push(a2[i].m);
            }
        }
    }
}
int main()
{
    scanf("%d%d%d%d",&n,&m,&q,&k);
    s1=n*2+1,s2=n*2+2;
    for(int i=1;i<=q;++i)
    {
        scanf("%d",&b[i]);
    }
    for(int i=1;i<=m;++i)
    {
        int x,y,w;
        scanf("%d%d%d",&x,&y,&w);
        road2(x,y,w);
        road2(y,x,w);
    }
    for(int i=1;i<=n;++i) SPFA0(i,g[i]);
    int l=0,r=2000000;
    while(l<r)
    {
        int z=l+r>>1;
        if(check(z)) r=z;
        else l=z+1;
    }
    printf("%d",l==2000000?-1:l);
    return 0;
}