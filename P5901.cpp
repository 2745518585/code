#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=1000001;
int n,m,q,p=1,t[N],b[N],c[N],e[N],f[N],h1[N],h2[N];
vector<int> d1[N],d2[N];
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
    for(int i=0;i<d1[b[x]].size();++i)
    {
        e[d1[b[x]][i]]-=h1[f[d1[b[x]][i]]];
    }
    ++h1[b[x]],++h2[b[x]];
    for(int i=0;i<d2[b[x]].size();++i)
    {
        e[d2[b[x]][i]]+=h2[f[d2[b[x]][i]]];
    }
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa) continue;
        dfs(a[i].m,x);
    }
    --h2[b[x]];
    for(int i=0;i<d1[b[x]].size();++i)
    {
        e[d1[b[x]][i]]+=h1[f[d1[b[x]][i]]];
    }
}
int main()
{
    scanf("%d%d%d%d",&n,&m,&q,&b[1]);
    ++c[b[1]];
    for(int i=2;i<=n;++i)
    {
        int x;
        scanf("%d%d",&x,&b[i]);
        road(x,i);
        ++c[b[i]];
    }
    for(int i=1;i<=q;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        if(c[x]<c[y])
        {
            d1[x].push_back(i);
            f[i]=y;
        }
        else
        {
            d2[y].push_back(i);
            f[i]=x;
        }
    }
    dfs(1,0);
    for(int i=1;i<=q;++i)
    {
        printf("%d\n",e[i]);
    }
    return 0;
}