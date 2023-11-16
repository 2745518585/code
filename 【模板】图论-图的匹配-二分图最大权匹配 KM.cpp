#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,p=0,t[N],g1[N],g2[N],r[N];
ll f[N],f1[N],f2[N];
bool h1[N],h2[N];
struct str
{
    int m,q;
    ll w;
}a[N];
void road(int x,int y,ll w)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].w=w;
}
void check(int x,int y)
{
    while(true)
    {
        int z=g1[r[y]];
        g2[y]=r[y];
        g1[r[y]]=y;
        if(r[y]==x) break;
        y=z;
    }
}
void bfs(int x)
{
    for(int i=1;i<=n;++i) f[i]=1e18,h1[i]=h2[i]=false;
    queue<int> Q;
    Q.push(x);
    while(true)
    {
        while(!Q.empty())
        {
            int k=Q.front();
            Q.pop();
            h1[k]=true;
            for(int i=t[k];i!=0;i=a[i].q)
            {
                if(h2[a[i].m]==false&&f1[k]+f2[a[i].m]-a[i].w<f[a[i].m])
                {
                    f[a[i].m]=f1[k]+f2[a[i].m]-a[i].w;
                    r[a[i].m]=k;
                    if(f[a[i].m]==0)
                    {
                        h2[a[i].m]=true;
                        if(g2[a[i].m]==0)
                        {
                            check(x,a[i].m);
                            return;
                        }
                        else Q.push(g2[a[i].m]);
                    }
                }
            }
        }
        ll t=1e18;
        for(int i=1;i<=n;++i)
        {
            if(h2[i]==false)
            {
                t=min(t,f[i]);
            }
        }
        for(int i=1;i<=n;++i)
        {
            if(h1[i]==true) f1[i]-=t;
            if(h2[i]==true) f2[i]+=t;
            else f[i]-=t;
        }
        for(int i=1;i<=n;++i)
        {
            if(h2[i]==false&&f[i]==0)
            {
                h2[i]=true;
                if(g2[i]==0)
                {
                    check(x,i);
                    return;
                }
                else Q.push(g2[i]);
            }
        }
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i)
    {
        int x,y;
        ll w;
        scanf("%d%d%lld",&x,&y,&w);
        road(x,y,w);
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=t[i];j!=0;j=a[j].q)
        {
            f1[i]=max(f1[i],a[j].w);
        }
    }
    for(int i=1;i<=n;++i) bfs(i);
    ll s=0;
    for(int i=1;i<=n;++i)
    {
        s+=f1[i]+f2[i];
    }
    printf("%lld\n",s);
    for(int i=1;i<=n;++i)
    {
        printf("%d ",g2[i]);
    }
    return 0;
}