#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
const int N=1000001,M=1000001;
int n,m,p=1,s1,s2,t[N],t0[N],f[N];
ll q;
struct road
{
    int m,q;
    ll r;
}a[M];
int sum(int x,int y)
{
    return (x-1)*n+y;
}
void road(int x,int y,ll r)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].r=r;
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
    scanf("%d%d",&m,&n);
    s1=m*n*3+1,s2=m*n*3+2;
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            ll r;
            scanf("%lld",&r);
            q+=r;
            road(s1,sum(i,j),r);
            road(sum(i,j),s1,0);
        }
    }
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            ll r;
            scanf("%lld",&r);
            q+=r;
            road(sum(i,j),s2,r);
            road(s2,sum(i,j),0);
        }
    }
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            ll r;
            scanf("%lld",&r);
            q+=r;
            road(s1,m*n+sum(i,j),r);
            road(m*n+sum(i,j),s1,0);
        }
    }
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            ll r;
            scanf("%lld",&r);
            q+=r;
            road(m*n*2+sum(i,j),s2,r);
            road(s2,m*n*2+sum(i,j),0);
        }
    }
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            road(n*m+sum(i,j),sum(i,j),1e18);
            road(sum(i,j),m*n+sum(i,j),0);
            road(sum(i,j),m*n*2+sum(i,j),1e18);
            road(m*n*2+sum(i,j),sum(i,j),0);
            if(i>1)
            {
                road(n*m+sum(i,j),sum(i-1,j),1e18);
                road(sum(i-1,j),m*n+sum(i,j),0);
                road(sum(i-1,j),m*n*2+sum(i,j),1e18);
                road(m*n*2+sum(i,j),sum(i-1,j),0);
            }
            if(j>1)
            {
                road(n*m+sum(i,j),sum(i,j-1),1e18);
                road(sum(i,j-1),m*n+sum(i,j),0);
                road(sum(i,j-1),m*n*2+sum(i,j),1e18);
                road(m*n*2+sum(i,j),sum(i,j-1),0);
            }
            if(i<m)
            {
                road(n*m+sum(i,j),sum(i+1,j),1e18);
                road(sum(i+1,j),m*n+sum(i,j),0);
                road(sum(i+1,j),m*n*2+sum(i,j),1e18);
                road(m*n*2+sum(i,j),sum(i+1,j),0);
            }
            if(j<n)
            {
                road(n*m+sum(i,j),sum(i,j+1),1e18);
                road(sum(i,j+1),m*n+sum(i,j),0);
                road(sum(i,j+1),m*n*2+sum(i,j),1e18);
                road(m*n*2+sum(i,j),sum(i,j+1),0);
            }
        }
    }
    ll r=0;
    while(bfs())
    {
        for(int i=1;i<=s2;++i) t0[i]=t[i];
        r+=dfs(s1,1e18);
    }
    printf("%lld",q-r);
    return 0;
}