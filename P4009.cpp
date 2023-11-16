#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
const int N=10000001,M=10000001;
int n,m,p=1,s1,s2,t[N],t0[N];
ll v,f[N],w1,w2,w3;
bool h[N];
struct road
{
    int m,q;
    ll r,w;
}a[M];
int sum(int x,int y,int k)
{
    return ((x-1)*n+y-1)*(m+1)+k+1;
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
    scanf("%d%d%lld%lld%lld",&n,&m,&w1,&w2,&w3);
    s1=n*n*(m+1)+1,s2=n*n*(m+1)+2;
    road(s1,sum(1,1,m),1,0);
    road(sum(1,1,m),s1,0,0);
    for(int i=0;i<=m;++i)
    {
        road(sum(n,n,i),s2,1,0);
        road(s2,sum(n,n,i),0,0);
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            int x;
            scanf("%d",&x);
            if(x==0)
            {
                road(sum(i,j,0),sum(i,j,m),1e18,w1+w3);
                road(sum(i,j,m),sum(i,j,0),0,-(w1+w3));
                for(int k=1;k<=m;++k)
                {
                    if(i<n)
                    {
                        road(sum(i,j,k),sum(i+1,j,k-1),1e18,0);
                        road(sum(i+1,j,k-1),sum(i,j,k),0,0);
                    }
                    if(j<n)
                    {
                        road(sum(i,j,k),sum(i,j+1,k-1),1e18,0);
                        road(sum(i,j+1,k-1),sum(i,j,k),0,0);
                    }
                    if(i>1)
                    {
                        road(sum(i,j,k),sum(i-1,j,k-1),1e18,w2);
                        road(sum(i-1,j,k-1),sum(i,j,k),0,-w2);
                    }
                    if(j>1)
                    {
                        road(sum(i,j,k),sum(i,j-1,k-1),1e18,w2);
                        road(sum(i,j-1,k-1),sum(i,j,k),0,-w2);
                    }
                }
            }
            else
            {
                for(int k=0;k<=m-1;++k)
                {
                    road(sum(i,j,k),sum(i,j,m),1e18,w1);
                    road(sum(i,j,m),sum(i,j,k),0,-w1);
                }
                if(i<n)
                {
                    road(sum(i,j,m),sum(i+1,j,m-1),1e18,0);
                    road(sum(i+1,j,m-1),sum(i,j,m),0,0);
                }
                if(j<n)
                {
                    road(sum(i,j,m),sum(i,j+1,m-1),1e18,0);
                    road(sum(i,j+1,m-1),sum(i,j,m),0,0);
                }
                if(i>1)
                {
                    road(sum(i,j,m),sum(i-1,j,m-1),1e18,w2);
                    road(sum(i-1,j,m-1),sum(i,j,m),0,-w2);
                }
                if(j>1)
                {
                    road(sum(i,j,m),sum(i,j-1,m-1),1e18,w2);
                    road(sum(i,j-1,m-1),sum(i,j,m),0,-w2);
                }
            }
        }
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