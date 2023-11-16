#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
const int N=1000001,M=10000001;
int n,s1,s2,p=1,t[N],t0[N],r[N];
ll f[N],g[N],v,w0,w1,w2,t1,t2;
bool h[N];
struct str
{
    int x,m,q;
    ll r,w;
}a[M];
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
    for(int i=1;i<=s2;++i)
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
    scanf("%d%lld%lld%lld%lld%lld",&n,&t1,&t2,&w1,&w2,&w0);
    s1=n*2+1;
    s2=n*2+2;
    for(int i=1;i<=n;++i)
    {
        ll r;
        scanf("%lld",&r);
        road(i,s2,r,0);
        road(s2,i,0,0);
        road(s1,n+i,r,0);
        road(n+i,s1,0,0);
    }
    for(int i=1;i<=n-1;++i)
    {
        road(n+i,n+i+1,1e18,0);
        road(n+i+1,n+i,0,0);
    }
    for(int i=1;i<=n;++i)
    {
        road(s1,i,1e18,w0);
        road(i,s1,0,-w0);
    }
    for(int i=1;i<=n-t1;++i)
    {
        road(n+i,i+t1,1e18,w1);
        road(i+t1,n+i,0,-w1);
    }
    for(int i=1;i<=n-t2;++i)
    {
        road(n+i,i+t2,1e18,w2);
        road(i+t2,n+i,0,-w2);
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