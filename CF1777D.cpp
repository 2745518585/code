#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll P=1e9+7;
int n,p=1,t[N],f[N];
ll s;
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
    f[x]=1;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa) continue;
        dfs(a[i].m,x);
        f[x]=max(f[x],f[a[i].m]+1);
    }
    s=(s+f[x])%P;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        p=1;
        for(int i=1;i<=n;++i) t[i]=0;
        for(int i=1;i<=n-1;++i)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            road(x,y);
            road(y,x);
        }
        ll w=1;
        for(int i=1;i<=n-1;++i) w=w*2%P;
        s=0;
        dfs(1,0);
        printf("%lld\n",s*w%P);
    }
    return 0;
}