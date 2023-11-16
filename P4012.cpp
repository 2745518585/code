#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
const int N=100001,M=1000001;
int n,m,p=1,t1,t2,s1,s2,t[N],t0[N];
ll v,f[N];
bool h[N];
struct road
{
    int m,q;
    ll r,w;
}a[M];
int sum(int x,int y)
{
    return (x-1)*n+y;
}
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
    for(int i=1;i<=s2;++i)
    {
        f[i]=-1e18;
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
            if(a[i].r>0&&f[k]+a[i].w>f[a[i].m])
            {
                f[a[i].m]=f[k]+a[i].w;
                Q.push(a[i].m);
                h[a[i].m]=true;
            }
        }
    }
    if(f[s2]!=-1e18) return true;
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
    scanf("%d%d%d%d",&t1,&t2,&m,&n);
    ++m,++n;
    s1=m*n+1,s2=m*n+2;
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n-1;++j)
        {
            ll w;
            scanf("%lld",&w);
            road(sum(i,j),sum(i,j+1),1,w);
            road(sum(i,j+1),sum(i,j),0,-w);
            road(sum(i,j),sum(i,j+1),1e18,0);
            road(sum(i,j+1),sum(i,j),0,0);
        }
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=m-1;++j)
        {
            ll w;
            scanf("%lld",&w);
            road(sum(j,i),sum(j+1,i),1,w);
            road(sum(j+1,i),sum(j,i),0,-w);
            road(sum(j,i),sum(j+1,i),1e18,0);
            road(sum(j+1,i),sum(j,i),0,0);
        }
    }
    for(int i=1;i<=t1;++i)
    {
        int x,y;
        ll r;
        scanf("%lld%d%d",&r,&x,&y);
        road(s1,sum(x+1,y+1),r,0);
        road(sum(x+1,y+1),s1,0,0);
    }
    for(int i=1;i<=t2;++i)
    {
        int x,y;
        ll r;
        scanf("%lld%d%d",&r,&x,&y);
        road(sum(x+1,y+1),s2,r,0);
        road(s2,sum(x+1,y+1),0,0);
    }
    while(SPFA())
    {
        for(int i=1;i<=s2;++i) 
        {
            t0[i]=t[i];
            h[i]=false;
        }
        dfs(s1,1e18);
    }
    printf("%lld",v);
    return 0;
}