#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,k,p=1,tot,t[N],b[N],c[N],d[N];
ll f[N][2];
bool g[N],g2[N],h[N];
struct road
{
    int m,q;
}a[N<<1];
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
void dfs0(int x,int fa)
{
    b[x]=c[x]=++tot;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        g2[i/2]=true;
        if(a[i].m==fa) continue;
        if(b[a[i].m]==0)
        {
            dfs0(a[i].m,x);
            c[x]=min(c[x],c[a[i].m]);
            if(c[a[i].m]>b[x]) g[i/2]=false;
        }
        c[x]=min(c[x],b[a[i].m]);
    }
}
void dfs(int x,int fa)
{
    f[x][0]=0;
    f[x][1]=d[x];
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa||h[i/2]==true) continue;
        dfs(a[i].m,x);
        f[x][0]+=max(f[a[i].m][0],f[a[i].m][1]);
        f[x][1]+=f[a[i].m][0];
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        int x;
        scanf("%lld%d",&d[i],&x);
        road(i,x);
        road(x,i);
    }
    ll s=0;
    for(int j=1;j<=n;++j) g[j]=true;
    for(int i=1;i<=n;++i)
    {
        if(b[i]==0)
        {
            for(int j=1;j<=n;++j) g2[j]=false;
            dfs0(i,0);
            int x=0;
            for(int j=1;j<=n;++j)
            {
                if(g2[j]==true&&g[j]==true)
                {
                    x=j;
                    break;
                }
            }
            h[x]=true;
            dfs(a[x*2].m,0);
            ll w1=f[a[x*2].m][0];
            dfs(a[x*2+1].m,0);
            ll w2=f[a[x*2+1].m][0];
            s+=max(w1,w2);
            h[x]=false;
        }
    }
    printf("%lld",s);
    return 0;
}