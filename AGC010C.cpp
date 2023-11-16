#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,p=1,t[N];
ll b[N],f[N];
bool u=true;
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
void dfs(int x,int fa)
{
    ll s=0,q=0;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa) continue;
        dfs(a[i].m,x);
        s+=f[a[i].m];
        q=max(q,f[a[i].m]);
    }
    if(a[t[x]].q==0) f[x]=b[x]-s;
    else f[x]=b[x]*2-s;
    if(q>b[x]||f[x]<0||f[x]>b[x]) u=false;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&b[i]);
    }
    for(int i=1;i<=n-1;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        road(x,y);
        road(y,x);
    }
    dfs(1,0);
    if(f[1]!=0) u=false;
    if(u) printf("YES\n");
    else printf("NO\n");
    return 0;
}