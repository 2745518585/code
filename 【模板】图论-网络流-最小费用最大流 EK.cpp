#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
const int N=10001,M=100001;
int n,m,s1,s2,p=1,t[N],f[N],g[N],r[N];
bool h[N];
struct road
{
    int m,q,r,w;
}a[M];
void road(int x,int y,int r,int w)
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
    for(int i=1;i<=n;++i)
    {
        f[i]=1e9;
        g[i]=1e9;
        h[i]=false;
        r[i]=0;
    }
    g[s1]=0;
    h[s1]=true;
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        if(h[k]==false) continue;
        h[k]=false;
        for(int i=t[k];i!=0;i=a[i].q)
        {
            if(a[i].r>0&&g[k]+a[i].w<g[a[i].m])
            {
                f[a[i].m]=min(f[k],a[i].r);
                g[a[i].m]=g[k]+a[i].w;
                r[a[i].m]=i;
                Q.push(a[i].m);
                h[a[i].m]=true;
            }
        }
    }
    if(f[s2]!=1e9) return true;
    return false;
}
int main()
{
    scanf("%d%d%d%d",&n,&m,&s1,&s2);
    for(int i=1;i<=m;++i)
    {
        int x,y,r,w;
        scanf("%d%d%d%d",&x,&y,&r,&w);
        road(x,y,r,w);
        road(y,x,0,-w);
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
            x=a[r[x]^1].m;
        }
    }
    printf("%d %d",s,w);
    return 0;
}