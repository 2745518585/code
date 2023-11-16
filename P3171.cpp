#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
const int N=10000001,M=10000001;
int n,m,p=1,s1,s2,t[N],p2=1,t2[N],t0[N];
ll v,f[N];
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
}a2[M];
void road(int x,int y,ll r)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].r=r;
}
void road2(int x,int y,ll w)
{
    a2[++p2].m=y;
    a2[p2].q=t2[x];
    t2[x]=p2;
    a2[p2].w=w;
}
void SPFA()
{
    queue<int> Q;
    Q.push(1);
    for(int i=1;i<=n;++i)
    {
        f[i]=1e18;
        h[i]=false;
    }
    f[1]=0;
    h[1]=true;
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
                Q.push(a2[i].m);
                h[a2[i].m]=true;
            }
        }
    }
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
int main()
{
    scanf("%d%d",&n,&m);
    s1=1,s2=n*2;
    for(int i=1;i<=m;++i)
    {
        int x,y;
        ll w;
        scanf("%d%d%lld",&x,&y,&w);
        road2(x,y,w);
        road2(y,x,w);
    }
    SPFA();
    for(int i=1;i<=n;++i)
    {
        for(int j=t2[i];j!=0;j=a2[j].q)
        {
            if(f[i]+a2[j].w==f[a2[j].m])
            {
                road(n+i,a2[j].m,1e18);
                road(a2[j].m,n+i,0);
            }
        }
    }
    for(int i=1;i<=n;++i)
    {
        ll r;
        scanf("%lld",&r);
        if(i==1||i==n) r=1e18;
        road(i,n+i,r);
        road(n+i,i,0);
    }
    ll r=0;
    while(bfs())
    {
        for(int i=1;i<=s2;++i) t0[i]=t[i];
        r+=dfs(s1,1e18);
    }
    printf("%lld",r);
    return 0;
}