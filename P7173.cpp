#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
int n,m,s1,s2,p=1,t[10001],f[10001],g[10001],r[10001],d[10001];
bool h[10001];
struct str
{
    int m,q,r,w;
}a[100001];
void road(int x,int y,int r,int w)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].r=r;
    a[p].w=w;
}
bool SPFA(int t1,int t2)
{
    queue<int> q;
    q.push(t1);
    for(int i=1;i<=n+2;++i)
    {
        f[i]=1e9;
        g[i]=1e9;
        h[i]=false;
        r[i]=0;
    }
    g[t1]=0;
    h[t1]=true;
    while(!q.empty())
    {
        int k=q.front();
        q.pop();
        if(h[k]==false) continue;
        h[k]=false;
        for(int i=t[k];i!=0;i=a[i].q)
        {
            if(a[i].r>0&&g[k]+a[i].w<g[a[i].m])
            {
                f[a[i].m]=min(f[k],a[i].r);
                g[a[i].m]=g[k]+a[i].w;
                r[a[i].m]=i;
                q.push(a[i].m);
                h[a[i].m]=true;
            }
        }
    }
    if(f[t2]!=1e9) return true;
    return false;
}
int main()
{
    scanf("%d%d%d%d",&n,&m,&s1,&s2);
    int k=0;
    for(int i=1;i<=m;++i)
    {
        int x,y,r,w;
        scanf("%d%d%d%d",&x,&y,&r,&w);
        if(w>=0)
        {
            road(x,y,r,w);
            road(y,x,0,-w);
        }
        else
        {
            road(y,x,r,-w);
            road(x,y,0,w);
            d[x]-=r;
            d[y]+=r;
            k+=r*w;
        }
    }
    for(int i=1;i<=n;++i)
    {
        if(d[i]==0) continue;
        if(d[i]>0)
        {
            road(n+1,i,d[i],0);
            road(i,n+1,0,0);
        }
        else
        {
            road(i,n+2,-d[i],0);
            road(n+2,i,0,0);
        }
    }
    int s=0,w=k;
    while(SPFA(n+1,n+2))
    {
        w+=f[n+2]*g[n+2];
        int x=n+2;
        while(x!=n+1)
        {
            a[r[x]].r-=f[n+2];
            a[r[x]^1].r+=f[n+2];
            x=a[r[x]^1].m;
        }
    }
    while(SPFA(s1,s2))
    {
        s+=f[s2];
        w+=f[s2]*g[s2];
        int x=s2;
        while(x!=s1)
        {
            a[r[x]].r-=f[s2];
            a[r[x]^1].r+=f[s2];
            x=a[r[x]^1].m;
        }
    }
    printf("%d %d",s,w);
    return 0;
}