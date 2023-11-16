#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
int n,m,s1,s2,p=1,t[10001],f[10001],g[10001],r[10001];
bool h[10001];
struct str
{
    int x,m,q,r,w;
}a[1000001];
void road(int x,int y,int r,int w)
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
    queue<int> q;
    q.push(s1);
    for(int i=1;i<=n*2;++i)
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
    if(f[s2]!=1e9) return true;
    return false;
}
int main()
{
    scanf("%d%d",&n,&m);
    s1=1;
    s2=n*2;
    for(int i=1;i<=m;++i)
    {
        int x,y,w;
        scanf("%d%d%d",&x,&y,&w);
        road(x,y+n,1,w);
        road(y+n,x,0,-w);
    }
    for(int i=2;i<=n-1;++i)
    {
        road(i+n,i,1,0);
        road(i,i+n,0,0);
    }
    int s=0,w=0;
    while(SPFA())
    {
        s+=f[s2];
        w+=f[s2]*g[s2];
        int x=s2;
        while(x!=s1)
        {
            a[r[x]].r-=f[s2];
            a[r[x]^1].r+=f[s2];
            x=a[r[x]].x;
        }
    }
    printf("%d %d",s,w);
    return 0;
}