#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=10000001;
int n,m,k;
bool f[N],g[N];
void dfs1(int x)
{
    f[x]=true;
    for(int i=0;i<=k-1;++i)
    {
        if((x&(1<<i))==0&&f[x^(1<<i)]==false) dfs1(x^(1<<i));
    }
}
void dfs2(int x)
{
    g[x]=true;
    for(int i=0;i<=k-1;++i)
    {
        if((x&(1<<i))&&g[x^(1<<i)]==false) dfs2(x^(1<<i));
    }
}
int solve()
{
    int x=(1<<k)-1,y=0,s=0;
    for(int i=k-1;i>=0;--i)
    {
        if(f[x^(1<<i)]&&g[y^(1<<i)])
        {
            x^=(1<<i);
            y^=(1<<i);
            s|=(1<<i);
        }
    }
    return s;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        k=0;
        while((1<<k)-1<n) ++k;
        for(int i=0;i<=(1<<k)-1;++i) f[i]=g[i]=false;
        int las=0;
        for(int i=1;i<=m;++i)
        {
            int x;
            scanf("%d",&x);
            x=(x+las)%n;
            dfs1(x),dfs2(x);
            printf("%d ",las=solve());
        }
        printf("\n");
    }
    return 0;
}