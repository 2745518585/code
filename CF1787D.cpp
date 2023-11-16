#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,p=1,t[N],b[N],w;
bool g[N],h[N];
struct road
{
    int m,q;
}a[N];
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
void dfs1(int x)
{
    if(h[x]==true) return;
    h[x]=true,++w;
    for(int i=t[x];i!=0;i=a[i].q) dfs1(a[i].m);
}
void dfs2(int x)
{
    if(h[x]==false) return;
    h[x]=false,--w;
    for(int i=t[x];i!=0;i=a[i].q) dfs2(a[i].m);
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        p=1;
        for(int i=1;i<=n+1;++i) t[i]=g[i]=h[i]=0;
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&b[i]);
            if(i+b[i]>=1&&i+b[i]<=n) road(i+b[i],i);
            else road(n+1,i);
        }
        w=-1;
        dfs1(n+1);
        int x=1;
        ll s=0;
        while(x>=1&&x<=n&&g[x]==false)
        {
            g[x]=true;
            dfs2(x);
            s+=w+n+1;
            x=x+b[x];
        }
        if(x<1||x>n)
        {
            for(int i=1;i<=n;++i)
            {
                if(g[i]==false) s+=n*2+1;
            }
        }
        printf("%lld\n",s);
    }
    return 0;
}