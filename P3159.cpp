#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
const int N=100001,M=1000001;
int n,m,q,p=1,s1,s2,t[N],t0[N];
ll v,f[N];
bool h[N],g[101][101];
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
    scanf("%d%d",&m,&n);
    s1=m*n*3+1,s2=m*n*3+2;
    for(int i=1;i<=m;++i)
    {
        char x[100];
        scanf("%s",x+1);
        for(int j=1;j<=n;++j)
        {
            if(x[j]=='1')
            {
                g[i][j]=true;
                ++q;
                road(s1,sum(i,j),1,0);
                road(sum(i,j),s1,0,0);
            }
        }
    }
    for(int i=1;i<=m;++i)
    {
        char x[100];
        scanf("%s",x+1);
        for(int j=1;j<=n;++j)
        {
            if(x[j]=='1')
            {
                g[i][j]=true;
                road(sum(i,j)+m*n,s2,1,0);
                road(s2,sum(i,j)+m*n,0,0);
            }
        }
    }
    for(int i=1;i<=m;++i)
    {
        char x[100];
        scanf("%s",x+1);
        for(int j=1;j<=n;++j)
        {
            road(sum(i,j),sum(i,j)+m*n,(x[j]-'0')/2+((g[i][j])?1:0),0);
            road(sum(i,j)+m*n,sum(i,j),0,0);
        }
    }
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(i>1)
            {
                road(sum(i-1,j)+m*n,sum(i,j),1e18,1);
                road(sum(i,j),sum(i-1,j)+m*n,0,-1);
                road(sum(i,j)+m*n,sum(i-1,j),1e18,1);
                road(sum(i-1,j),sum(i,j)+m*n,0,-1);
            }
            if(j>1)
            {
                road(sum(i,j-1)+m*n,sum(i,j),1e18,1);
                road(sum(i,j),sum(i,j-1)+m*n,0,-1);
                road(sum(i,j)+m*n,sum(i,j-1),1e18,1);
                road(sum(i,j-1),sum(i,j)+m*n,0,-1);
            }
            if(i>1&&j>1)
            {
                road(sum(i-1,j-1)+m*n,sum(i,j),1e18,1);
                road(sum(i,j),sum(i-1,j-1)+m*n,0,-1);
                road(sum(i,j)+m*n,sum(i-1,j-1),1e18,1);
                road(sum(i-1,j-1),sum(i,j)+m*n,0,-1);
            }
            if(i>1&&j<n)
            {
                road(sum(i-1,j+1)+m*n,sum(i,j),1e18,1);
                road(sum(i,j),sum(i-1,j+1)+m*n,0,-1);
                road(sum(i,j)+m*n,sum(i-1,j+1),1e18,1);
                road(sum(i-1,j+1),sum(i,j)+m*n,0,-1);
            }
        }
    }
    ll r=0;
    while(SPFA())
    {
        for(int i=1;i<=s2;++i) 
        {
            t0[i]=t[i];
            h[i]=false;
        }
        r+=dfs(s1,1e18);
    }
    if(q!=r) printf("-1");
    else printf("%lld",v);
    return 0;
}