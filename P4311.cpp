#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
int m,n,m0,p=1,s1,s2,t1,t2,t[100001],t0[100001],f[100001],b[100001];
bool h0[1001][1001];
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
    for(int i=1;i<=m*n+m+n+4;++i) f[i]=0;
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
    scanf("%d%d%d",&m,&n,&m0);
    t1=m*n+m+n+1;
    t2=m*n+m+n+2;
    s1=m*n+m+n+3;
    s2=m*n+m+n+4;
    for(int i=1;i<=m*n;++i)
    {
        road(t1,i,1e9);
        road(i,t1,0);
    }
    for(int i=1;i<=m;++i)
    {
        int r1;
        scanf("%d",&r1);
        road(m*n+i,t2,1e9);
        road(t2,m*n+i,0);
        b[m*n+i]+=r1;
        b[t2]-=r1;
    }
    for(int i=1;i<=n;++i)
    {
        int r1;
        scanf("%d",&r1);
        road(m*n+m+i,t2,1e9);
        road(t2,m*n+m+i,0);
        b[m*n+m+i]+=r1;
        b[t2]-=r1;
    }
    for(int i=1;i<=m0;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        h0[x][y]=true;
    }
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(h0[i][j]==true) continue;
            road((i-1)*n+j,m*n+i,1e9);
            road(m*n+i,(i-1)*n+i,0);
            road((i-1)*n+j,m*n+m+j,1e9);
            road(m*n+m+j,(i-1)*n+j,0);
        }
    }
    for(int i=1;i<=m*n+m+n+2;++i)
    {
        if(b[i]<0)
        {
            road(s1,i,-b[i]);
            road(i,s1,0);
        }
        else if(b[i]>0)
        {
            road(i,s2,b[i]);
            road(s2,i,0);
        }
    }
    road(t2,t1,1e9);
    road(t1,t2,0);
    while(bfs())
    {
        for(int i=1;i<=m*n+m+n+4;++i) t0[i]=t[i];
        dfs(s1,1e9);
    }
    for(int i=t[s1];i!=0;i=a[i].q)
    {
        if(a[i].r!=0)
        {
            printf("JIONG");
            return 0;
        }
    }
    s1=t2;
    s2=t1;
    int r=0;
    for(int i=t[t2];i!=0;i=a[i].q)
    {
        if(a[i].m==t1)
        {
            r+=a[i^1].r;
            a[i].r=a[i^1].r=0;
        }
    }
    while(bfs())
    {
        for(int i=1;i<=m*n+m+n+4;++i) t0[i]=t[i];
        r-=dfs(s1,1e9);
    }
    printf("%d",r/2);
    return 0;
}
