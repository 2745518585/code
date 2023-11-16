#include<cstdio>
#include<algorithm>
#include<vector>
#include<bitset>
using namespace std;
const int N=500001,M=41;
int n,f[N],g[N];
bitset<M> f1[N],f2[N],g1[N],g2[N],p1[N],p2[N];
vector<int> a[N];
void dfs1(int x,int fa)
{
    f1[x]=f2[x]=0;
    for(auto i:a[x])
    {
        if(i==fa) continue;
        dfs1(i,x);
        f1[x]|=f2[i];
        f2[x]|=f1[i];
        f1[x][f[i]]=1;
        f2[x][f[i]^1]=1;
    }
    f[x]=(~f1[x])._Find_first();
}
void dfs2(int x,int fa)
{
    p1[a[x].size()]=p2[a[x].size()]=0;
    for(int i=a[x].size()-1;i>=0;--i)
    {
        if(a[x][i]!=fa)
        {
            p1[i]=p1[i+1]|f1[a[x][i]];
            p2[i]=p2[i+1]|f2[a[x][i]];
            p1[i][f[a[x][i]]^1]=1;
            p2[i][f[a[x][i]]]=1;
        }
        else
        {
            p1[i]=p1[i+1];
            p2[i]=p2[i+1];
        }
    }
    bitset<M> w1=g1[x],w2=g2[x];
    if(x!=1) w1[g[x]^1]=1,w2[g[x]]=1;
    for(int i=0;i<=a[x].size()-1;++i)
    {
        if(a[x][i]==fa) continue;
        g1[a[x][i]]=w2|p2[i+1];
        g2[a[x][i]]=w1|p1[i+1];
        g[a[x][i]]=(~g1[a[x][i]])._Find_first();
        w1|=f1[a[x][i]];
        w2|=f2[a[x][i]];
        w1[f[a[x][i]]^1]=1;
        w2[f[a[x][i]]]=1;
    }
    for(auto i:a[x])
    {
        if(i==fa) continue;
        dfs2(i,x);
    }
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i) a[i].clear();
        for(int i=1;i<=n-1;++i)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            a[x].push_back(y);
            a[y].push_back(x);
        }
        dfs1(1,0);
        g[1]=0;
        g1[1]=g2[1]=0;
        dfs2(1,0);
        bool u=false;
        for(int i=2;i<=n;++i)
        {
            if((f[i]^g[i])==0)
            {
                u=true;
                break;
            }
        }
        if(u) printf("Play now\n");
        else printf("Restart\n");
    }
    return 0;
}