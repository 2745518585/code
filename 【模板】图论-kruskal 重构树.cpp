#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
const int N=1000001,M=21;
int n,m,q,d,p=1,t[N],f[N],f2[N],fa[N],ga[N],g[N][M];
bool h[N];
struct road
{
    int m,q,w;
}a[N<<1];
struct road2
{
    int x,y,w;
}b[N];
bool cmp(road2 a,road2 b)
{
    return a.w>b.w;
}
void road(int x,int y,int w)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].w=w;
}
int find(int x)
{
    if(ga[x]==x) return x;
    return ga[x]=find(ga[x]);
}
namespace Dijkstra
{
    struct str
    {
        int x,s;
        str(){}
        str(int x,int s):x(x),s(s){}
        friend bool operator <(str a,str b)
        {
            return a.s>b.s;
        }
    };
    void main()
    {
        priority_queue<str> Q;
        Q.push(str(1,0));
        for(int i=1;i<=n;++i) f[i]=1e9,h[i]=false;
        f[1]=0;
        while(!Q.empty())
        {
            int k=Q.top().x;
            Q.pop();
            if(h[k]==true) continue;
            h[k]=true;
            for(int i=t[k];i!=0;i=a[i].q)
            {
                if(h[a[i].m]==false&&f[k]+a[i].w<f[a[i].m])
                {
                    f[a[i].m]=f[k]+a[i].w;
                    Q.push(str(a[i].m,f[a[i].m]));
                }
            }
        }
    }
}
void abc()
{
    scanf("%d%d",&n,&m);
    p=1;
    for(int i=1;i<=n;++i) t[i]=0;
    for(int i=1;i<=m;++i)
    {
        int x,y,w,w2;
        scanf("%d%d%d%d",&x,&y,&w,&w2);
        road(x,y,w);
        road(y,x,w);
        b[i]=(road2){x,y,w2};
    }
    Dijkstra::main();
    sort(b+1,b+m+1,cmp);
    for(int i=1;i<=n+m;++i) fa[i]=ga[i]=i;
    for(int i=1;i<=n;++i) f2[i]=f[i];
    for(int i=1;i<=m;++i)
    {
        if(find(b[i].x)!=find(b[i].y))
        {
            int x=find(b[i].x),y=find(b[i].y);
            f2[n+i]=min(f2[x],f2[y]);
            ga[x]=fa[x]=n+i;
            ga[y]=fa[y]=n+i;
        }
    }
    for(int i=1;i<=n+m;++i) g[i][0]=fa[i];
    for(int i=1;i<=20;++i)
    {
        for(int j=1;j<=n+m;++j)
        {
            g[j][i]=g[g[j][i-1]][i-1];
        }
    }
    int z,las=0;
    scanf("%d%d%d",&q,&z,&d);
    for(int i=1;i<=q;++i)
    {
        int x,k;
        scanf("%d%d",&x,&k);
        x=(x+z*las-1)%n+1,k=(k+z*las)%(d+1);
        if(b[fa[x]-n].w<=k)
        {
            printf("%d\n",las=f[x]);
            continue;
        }
        x=fa[x];
        int u=0;
        while(x!=g[x][u]&&u!=-1)
        {
            if(b[g[x][u]-n].w>k) x=g[x][u],++u;
            else --u;
        }
        printf("%d\n",las=f2[x]);
    }
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--) abc();
    return 0;
}