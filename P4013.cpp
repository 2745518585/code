#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
const int N=10001,M=100001;
int n,m,p=1,v,s1,s2,t[N],t0[N];
ll f[N],b[N];
bool h[N];
struct str
{
    int m,q;
    ll r,w;
}a[M];
int sum(int x,int y)
{
    return (x+m-1)*(x+m-2)/2-m*(m-1)/2+y;
}
int sum2(int x,int y)
{
    return (x+m-1)*(x+m-2)/2-m*(m-1)+y+(m+n-1)*(m+n)/2;
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
    queue<int> q;
    q.push(s1);
    for(int i=1;i<=s2;++i)
    {
        f[i]=-1e18;
        h[i]=false;
    }
    f[s1]=0;
    h[s1]=true;
    while(!q.empty())
    {
        int k=q.front();
        q.pop();
        if(h[k]==false) continue;
        h[k]=false;
        for(int i=t[k];i!=0;i=a[i].q)
        {
            if(a[i].r>0&&f[k]+a[i].w>f[a[i].m])
            {
                f[a[i].m]=f[k]+a[i].w;
                q.push(a[i].m);
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
    scanf("%d%d",&m,&n);
    s1=(m+n-1)*(m+n)-m*(m-1)+1;
    s2=(m+n-1)*(m+n)-m*(m-1)+2;
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=m+i-1;++j)
        {
            ll w;
            scanf("%lld",&w);
            b[sum(i,j)]=w;
            road(sum(i,j),sum2(i,j),1,w);
            road(sum2(i,j),sum(i,j),0,-w);
            if(i!=n)
            {
                road(sum2(i,j),sum(i+1,j),1,0);
                road(sum(i+1,j),sum2(i,j),0,0);
                road(sum2(i,j),sum(i+1,j+1),1,0);
                road(sum(i+1,j+1),sum2(i,j),0,0);
            }
        }
    }
    for(int i=1;i<=m;++i)
    {
        road(s1,sum(1,i),1,0);
        road(sum(1,i),s1,0,0);
    }
    for(int i=1;i<=m+n-1;++i)
    {
        road(sum2(n,i),s2,1,0);
        road(s2,sum2(n,i),0,0);
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
    printf("%lld\n",v);
    p=1;
    for(int i=1;i<=s2;++i) t[i]=0;
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=m+i-1;++j)
        {
            ll w=b[sum(i,j)];
            road(sum(i,j),sum2(i,j),1e18,w);
            road(sum2(i,j),sum(i,j),0,-w);
            if(i!=n)
            {
                road(sum2(i,j),sum(i+1,j),1,0);
                road(sum(i+1,j),sum2(i,j),0,0);
                road(sum2(i,j),sum(i+1,j+1),1,0);
                road(sum(i+1,j+1),sum2(i,j),0,0);
            }
        }
    }
    for(int i=1;i<=m;++i)
    {
        road(s1,sum(1,i),1,0);
        road(sum(1,i),s1,0,0);
    }
    for(int i=1;i<=m+n-1;++i)
    {
        road(sum2(n,i),s2,1e18,0);
        road(s2,sum2(n,i),0,0);
    }
    v=0;
    while(SPFA())
    {
        for(int i=1;i<=s2;++i) 
        {
            t0[i]=t[i];
            h[i]=false;
        }
        dfs(s1,1e18);
    }
    printf("%lld\n",v);
    p=1;
    for(int i=1;i<=s2;++i) t[i]=0;
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=m+i-1;++j)
        {
            ll w=b[sum(i,j)];
            road(sum(i,j),sum2(i,j),1e18,w);
            road(sum2(i,j),sum(i,j),0,-w);
            if(i!=n)
            {
                road(sum2(i,j),sum(i+1,j),1e18,0);
                road(sum(i+1,j),sum2(i,j),0,0);
                road(sum2(i,j),sum(i+1,j+1),1e18,0);
                road(sum(i+1,j+1),sum2(i,j),0,0);
            }
        }
    }
    for(int i=1;i<=m;++i)
    {
        road(s1,sum(1,i),1,0);
        road(sum(1,i),s1,0,0);
    }
    for(int i=1;i<=m+n-1;++i)
    {
        road(sum2(n,i),s2,1e18,0);
        road(s2,sum2(n,i),0,0);
    }
    v=0;
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