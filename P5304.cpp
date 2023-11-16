#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,k,p=1,t[N],b[N],f2[N],g2[N];
ll f[N],g[N];
bool h[N];
struct road
{
    int m,q,w;
}a[N];
struct road2
{
    int x,y,w;
}a2[N];
void road(int x,int y,int w)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].w=w;
}
void SPFA(ll f[],int f2[])
{
    queue<int> Q;
    for(int i=1;i<=n;++i) f[i]=1e18,h[i]=false;
    for(int i=1;i<=k;++i)
    {
        f[b[i]]=0,f2[b[i]]=b[i],h[b[i]]=true;
        Q.push(b[i]);
    }
    while(!Q.empty()) 
    {
        int k=Q.front();
        Q.pop();
        if(h[k]==false) continue;
        h[k]=false;
        for(int i=t[k];i!=0;i=a[i].q)
        {
            if(f[k]+a[i].w<f[a[i].m])
            {
                f[a[i].m]=f[k]+a[i].w;
                f2[a[i].m]=f2[k];
                h[a[i].m]=true;
                Q.push(a[i].m);
            }
        }
    }
}
void abc()
{
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=m;++i)
    {
        scanf("%d%d%d",&a2[i].x,&a2[i].y,&a2[i].w);
    }
    for(int i=1;i<=k;++i)
    {
        scanf("%d",&b[i]);
    }
    p=1;
    for(int i=1;i<=n;++i) t[i]=0;
    for(int i=1;i<=m;++i) road(a2[i].x,a2[i].y,a2[i].w);
    SPFA(f,f2);
    p=1;
    for(int i=1;i<=n;++i) t[i]=0;
    for(int i=1;i<=m;++i) road(a2[i].y,a2[i].x,a2[i].w);
    SPFA(g,g2);
    ll s=1e18;
    for(int i=1;i<=m;++i)
    {
        if(f2[a2[i].x]!=g2[a2[i].y]) s=min(s,f[a2[i].x]+g[a2[i].y]+a2[i].w);
    }
    printf("%lld\n",s);
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--) abc();
    return 0;
}