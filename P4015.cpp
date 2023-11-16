#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
int n,n1,n2,s1,s2,p=1,t[10001],f[10001],g[10001],r[10001];
bool h[10001];
struct str
{
    int x,m,q,r1,r2,w;
}a[100001];
void road(int x,int y,int r,int w)
{
    a[++p].x=x;
    a[p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].r1=r;
    a[p].r2=r;
    a[p].w=w;
}
bool SPFA()
{
    queue<int> q;
    q.push(s1);
    for(int i=1;i<=n;++i)
    {
        f[i]=1e9;
        g[i]=1e9;
        h[i]=false;
        r[i]=0;
    }
    g[s1]=0;
    h[s1]=true;
    while(!q.empty())
    {
        int k=q.front();
        q.pop();
        if(h[k]==false) continue;
        h[k]=false;
        for(int i=t[k];i!=0;i=a[i].q)
        {
            if(a[i].r1>0&&g[k]+a[i].w<g[a[i].m])
            {
                f[a[i].m]=min(f[k],a[i].r1);
                g[a[i].m]=g[k]+a[i].w;
                r[a[i].m]=i;
                q.push(a[i].m);
                h[a[i].m]=true;
            }
        }
    }
    if(f[s2]!=1e9) return true;
    return false;
}
bool SPFA2()
{
    queue<int> q;
    q.push(s1);
    for(int i=1;i<=n;++i)
    {
        f[i]=1e9;
        g[i]=-1e9;
        h[i]=false;
        r[i]=0;
    }
    g[s1]=0;
    h[s1]=true;
    while(!q.empty())
    {
        int k=q.front();
        q.pop();
        if(h[k]==false) continue;
        h[k]=false;
        for(int i=t[k];i!=0;i=a[i].q)
        {
            if(a[i].r2>0&&g[k]+a[i].w>g[a[i].m])
            {
                f[a[i].m]=min(f[k],a[i].r2);
                g[a[i].m]=g[k]+a[i].w;
                r[a[i].m]=i;
                q.push(a[i].m);
                h[a[i].m]=true;
            }
        }
    }
    if(f[s2]!=1e9) return true;
    return false;
}
int main()
{
    scanf("%d%d",&n1,&n2);
    n=n1+n2+2;
    s1=1;
    s2=n;
    for(int i=1;i<=n1;++i)
    {
        int r;
        scanf("%d",&r);
        road(1,i+1,r,0);
        road(i+1,1,0,0);
    }
    for(int i=1;i<=n2;++i)
    {
        int r;
        scanf("%d",&r);
        road(i+n1+1,n,r,0);
        road(n,i+n1+1,0,0);
    }
    for(int i=1;i<=n1;++i)
    {
        for(int j=1;j<=n2;++j)
        {
            int w;
            scanf("%d",&w);
            road(i+1,j+n1+1,1e9,w);
            road(j+n1+1,i+1,0,-w);
        }
    }
    int w1=0,w2=0;
    while(SPFA())
    {
        w1+=f[s2]*g[s2];
        int x=s2;
        while(x!=s1)
        {
            a[r[x]].r1-=f[s2];
            a[r[x]^1].r1+=f[s2];
            x=a[r[x]].x;
        }
    }
    while(SPFA2())
    {
        w2+=f[s2]*g[s2];
        int x=s2;
        while(x!=s1)
        {
            a[r[x]].r2-=f[s2];
            a[r[x]^1].r2+=f[s2];
            x=a[r[x]].x;
        }
    }
    printf("%d\n%d",w1,w2);
    return 0;
}