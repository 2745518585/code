#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
int n,N,s1,s2,p=1,t[10001],r[10001];
ll b[10001],f[10001],g[10001],w0,w1,w2,t1,t2;
bool h[10001];
struct str
{
    int x,m,q;
    ll r,w;
}a[1000001];
void road(int x,int y,ll r,ll w)
{
    a[++p].x=x;
    a[p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].r=r;
    a[p].w=w;
}
bool SPFA()
{
    queue<int> Q;
    Q.push(s1);
    for(int i=1;i<=N;++i)
    {
        f[i]=1e18;
        g[i]=1e18;
        h[i]=false;
        r[i]=0;
    }
    g[s1]=0;
    h[s1]=true;
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        if(h[k]==false) continue;
        h[k]=false;
        for(int i=t[k];i!=0;i=a[i].q)
        {
            if(a[i].r>0&&g[k]+a[i].w<g[a[i].m])
            {
                f[a[i].m]=min(f[k],a[i].r);
                g[a[i].m]=g[k]+a[i].w;
                r[a[i].m]=i;
                Q.push(a[i].m);
                h[a[i].m]=true;
            }
        }
    }
    if(f[s2]!=1e18) return true;
    return false;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&b[i]);
    }
    scanf("%lld%lld%lld%lld%lld",&w0,&t1,&w1,&t2,&w2);
    s1=n*2+1;
    s2=n*2+2;
    N=n*2+2;
    for(int i=1;i<=n;++i)
    {
        road(i*2-1,s2,b[i],0);
        road(s2,i*2-1,0,0);
    }
    for(int i=1;i<=n;++i)
    {
        road(s1,i*2,b[i],0);
        road(i*2,s1,0,0);
    }
    for(int i=1;i<=n-1;++i)
    {
        road(i*2,(i+1)*2,1e18,0);
        road((i+1)*2.,i*2,0,0);
    }
    for(int i=1;i<=n;++i)
    {
        road(s1,i*2-1,1e18,w0);
        road(i*2-1,s1,0,-w0);
    }
    for(int i=1;i<=n-t1;++i)
    {
        road(i*2,(i+t1)*2-1,1e18,w1);
        road((i+t1)*2-1,i*2,0,-w1);
    }
    for(int i=1;i<=n-t2;++i)
    {
        road(i*2,(i+t2)*2-1,1e18,w2);
        road((i+t2)*2-1,i*2,0,-w2);
    }
    ll w=0;
    while(SPFA())
    {
        w+=f[s2]*g[s2];
        int x=s2;
        while(x!=s1)
        {
            a[r[x]].r-=f[s2];
            a[r[x]^1].r+=f[s2];
            x=a[r[x]].x;
        }
    }
    printf("%lld",w);
    return 0;
}