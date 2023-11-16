#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1000001,M=1001;
int p=1,s1,s2,t[N],t0[N],f[N];
int m,n,b[M][M];
struct road
{
    int m,q;
    ll r;
}a[N];
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
int sum(int x,int y)
{
    return (x-1)*n+y;
}
int main()
{
    scanf("%d%d",&m,&n);
    s1=m*n*2+1,s2=m*n*2+2;
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            scanf("%d",&b[i][j]);
            road(sum(i,j),m*n+sum(i,j),1e18);
            road(m*n+sum(i,j),sum(i,j),0);
        }
    }
    ll s=0;
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(b[i][j]==-1)
            {
                road(s1,sum(i,j),1e18);
                road(sum(i,j),s1,0);
                int w=0;
                for(int k=i-1;k>=1;--k) w=max(w,b[k][j]);
                s+=w;
                int q=0;
                for(int k=i-1;k>=1;--k)
                {
                    road(sum(k+1,j),sum(k,j),w-q);
                    road(sum(k,j),sum(k+1,j),0);
                    q=max(q,b[k][j]);
                }
            }
            else if(b[i][j]==-2)
            {
                road(s1,sum(i,j),1e18);
                road(sum(i,j),s1,0);
                int w=0;
                for(int k=i+1;k<=m;++k) w=max(w,b[k][j]);
                s+=w;
                int q=0;
                for(int k=i+1;k<=m;++k)
                {
                    road(sum(k-1,j),sum(k,j),w-q);
                    road(sum(k,j),sum(k-1,j),0);
                    q=max(q,b[k][j]);
                }
            }
            else if(b[i][j]==-3)
            {
                road(m*n+sum(i,j),s2,1e18);
                road(s2,m*n+sum(i,j),0);
                int w=0;
                for(int k=j-1;k>=1;--k) w=max(w,b[i][k]);
                s+=w;
                int q=0;
                for(int k=j-1;k>=1;--k)
                {
                    road(m*n+sum(i,k),m*n+sum(i,k+1),w-q);
                    road(m*n+sum(i,k+1),m*n+sum(i,k),0);
                    q=max(q,b[i][k]);
                }
            }
            else if(b[i][j]==-4)
            {
                road(m*n+sum(i,j),s2,1e18);
                road(s2,m*n+sum(i,j),0);
                int w=0;
                for(int k=j+1;k<=n;++k) w=max(w,b[i][k]);
                s+=w;
                int q=0;
                for(int k=j+1;k<=n;++k)
                {
                    road(m*n+sum(i,k),m*n+sum(i,k-1),w-q);
                    road(m*n+sum(i,k-1),m*n+sum(i,k),0);
                    q=max(q,b[i][k]);
                }
            }
        }
    }
    ll r=0;
    while(bfs())
    {
        for(int i=1;i<=s2;++i) t0[i]=t[i];
        r+=dfs(s1,1e18);
    }
    printf("%lld",s-r);
    return 0;
}