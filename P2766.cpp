#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
int n,m,N,p=1,s1,s2,b[1001],g[1001],t[1001],t0[1001],f[1001];
struct str
{
    int m,q,r;
}a[10000001];
void road(int x,int y,int r)
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
    for(int i=1;i<=N;++i) f[i]=0;
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
int dfs(int x,int r)
{
    if(x==s2) return r;
    int s=0;
    for(int i=t0[x];i!=0;i=a[i].q)
    {
        t0[x]=i;
        if(f[a[i].m]==f[x]+1&&a[i].r!=0)
        {
            int z=dfs(a[i].m,min(r,a[i].r));
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
    scanf("%d",&n);
    if(n==1)
    {
        printf("1\n1\n1");
        return 0;
    }
    int s=0;
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&b[i]);
        g[i]=1;
        for(int j=1;j<=i-1;++j)
        {
            if(b[j]<=b[i])
            {
                g[i]=max(g[i],g[j]+1);
            }
        }
        s=max(s,g[i]);
    }
    printf("%d\n",s);
    N=n*2+2;
    s1=N-1;
    s2=N;
    for(int i=1;i<=n;++i)
    {
        road(i,n+i,1);
        road(n+i,i,0);
    }
    for(int i=1;i<=n;++i)
    {
        if(g[i]==1)
        {
            road(s1,i,1);
            road(i,s1,0);
        }
        if(g[i]==s)
        {
            road(n+i,s2,1);
            road(s2,n+i,0);
        }
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=i+1;j<=n;++j)
        {
            if(g[i]+1==g[j]&&b[i]<=b[j])
            {
                road(n+i,j,1);
                road(j,n+i,0);
            }
        }
    }
    int r=0;
    while(bfs())
    {
        for(int i=1;i<=N;++i) t0[i]=t[i];
        r+=dfs(s1,1e9);
    }
    printf("%d\n",r);
    p=1;
    for(int i=1;i<=N;++i) t[i]=0;
    for(int i=1;i<=n;++i)
    {
        if(i==1||i==n)
        {
            road(i,n+i,1e9);
            road(n+i,i,0);
        }
        else
        {
            road(i,n+i,1);
            road(n+i,i,0);
        }
    }
    if(g[1]==1)
    {
        road(s1,1,1e9);
        road(1,s1,0);
    }
    if(g[1]==s)
    {
        road(n+1,s2,1);
        road(s2,n+1,0);
    }
    if(g[n]==1)
    {
        road(s1,n,1);
        road(n,s1,0);
    }
    if(g[n]==s)
    {
        road(n*2,s2,1e9);
        road(s2,n*2,0);
    }
    for(int i=2;i<=n-1;++i)
    {
        if(g[i]==1)
        {
            road(s1,i,1e9);
            road(i,s1,0);
        }
        if(g[i]==s)
        {
            road(n+i,s2,1e9);
            road(s2,n+i,0);
        }
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=i+1;j<=n;++j)
        {
            if(g[i]+1==g[j]&&b[i]<=b[j])
            {
                road(n+i,j,1);
                road(j,n+i,0);
            }
        }
    }
    r=0;
    while(bfs())
    {
        for(int i=1;i<=N;++i) t0[i]=t[i];
        r+=dfs(s1,1e9);
    }
    printf("%d",r);
    return 0;
}