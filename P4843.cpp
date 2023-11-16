#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
int n,p=1,s1,s2,t1,t2,t[10001],t0[10001],f[10001],b[10001];
struct str
{
    int m,q,r;
}a[1000001];
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
    for(int i=1;i<=n;++i) f[i]=0;
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
    t1=n+1;
    t2=n+2;
    s1=n+3;
    s2=n+4;
    for(int i=1;i<=n;++i)
    {
        int q;
        scanf("%d",&q);
        for(int j=1;j<=q;++j)
        {
            int x;
            scanf("%d",&x);
            road(i,x,1e9);
            road(x,i,0);
            ++b[i];
            --b[x];
        }
    }
    for(int i=1;i<=n;++i)
    {
        road(t1,i,1e9);
        road(i,t1,0);
        road(i,t2,1e9);
        road(t2,i,0);
    }
    for(int i=1;i<=n;++i)
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
    n+=4;
    while(bfs())
    {
        for(int i=1;i<=n;++i) t0[i]=t[i];
        dfs(s1,1e9);
    }
    n-=2;
    s1=t2;
    s2=t1;
    int r=0;
    for(int i=t[s2];i!=0;i=a[i].q)
    {
        if(a[i].m==s1)
        {
            r+=a[i].r;
            a[i].r=a[i^1].r=0;
        }
    }
    while(bfs())
    {
        for(int i=1;i<=n;++i) t0[i]=t[i];
        r-=dfs(s1,1e9);
    }
    printf("%d",r);
    return 0;
}