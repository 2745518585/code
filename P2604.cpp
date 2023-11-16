#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
const int N=10001,M=100001;
int n,m,r0,p=1,v,s1,s2,t[N],t0[N];
ll f[N],b[N][4];
bool h[N];
struct str
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
}
bool SPFA()
{
    queue<int> Q;
    Q.push(s1);
    for(int i=1;i<=n+1;++i)
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
    if(f[s2]!=1e18) return true;
    return false;
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
    scanf("%d%d%d",&n,&m,&r0);
    s1=1,s2=n;
    for(int i=1;i<=m;++i)
    {
        int x,y;
        ll r,w;
        scanf("%d%d%lld%lld",&x,&y,&r,&w);
        b[i][0]=x,b[i][1]=y,b[i][2]=r,b[i][3]=w;
        road(x,y,r,0);
        road(y,x,0,0);
    }
    ll r=0;
    while(SPFA())
    {
        for(int i=1;i<=n+1;++i) 
        {
            t0[i]=t[i];
            h[i]=false;
        }
        r+=dfs(s1,1e18);
    }
    printf("%lld ",r);
    s1=n+1;
    road(s1,1,r0,0);
    road(1,s1,0,0);
    for(int i=1;i<=m;++i)
    {
        road(b[i][0],b[i][1],1e18,b[i][3]);
        road(b[i][1],b[i][0],0,-b[i][3]);
    }
    v=0;
    while(SPFA())
    {
        for(int i=1;i<=n+1;++i) 
        {
            t0[i]=t[i];
            h[i]=false;
        }
        r+=dfs(s1,1e18);
    }
    printf("%lld",v);
    return 0;
}