#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=500001;
int n,m,p=1,t[N];
ll f[N][3],g[3],q,d;
struct road
{
    int m,q,w;
}a[N<<1];
void road(int x,int y,int w)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].w=w;
}
void dfs(int x,int fa)
{
    f[x][0]=0;
    f[x][1]=-1e9,f[x][2]=-1e9;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa) continue;
        dfs(a[i].m,x);
        for(int i=0;i<=2;++i) g[i]=f[x][i],f[x][i]=-1e9;
        for(int i=0;i<=2;++i)
        {
            for(int j=0;j<=2;++j)
            {
                f[x][i]=max(f[x][i],g[i]+f[a[i].m][j]);
                if(i>=1&&j>=1) f[x][i]=max(f[x][i],g[i-1]+f[a[i].m][j-1]+a[i].w+(j==1)*d);
            }
        }
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        int x,y,w;
        scanf("%d%d%d",&x,&y,&w);
        q+=abs(w);
        road(x,y,w);
        road(y,x,w);
    }
    ll l=-q,r=q;
    while(l<r)
    {
        ll z=l+r>>1;
        d=z;
        dfs(1,0);
    }
}