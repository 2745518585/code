#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001,M=10000001;
int n,m,p=1,t[N],fa[N],b[N],c[N];
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
namespace Tree
{
    int tot,rt[N],a[M][2],b[M][2],f[N];
    void add(int t,int x,int k)
    {
        int q=rt[t];
        for(int i=0;i<=20;++i)
        {
            int z=(x&(1<<i))!=0;
            if(z==1) f[t]^=(1<<i)*(b[q][z]&1);
            b[q][z]+=k;
            if(z==1) f[t]^=(1<<i)*(b[q][z]&1);
            if(a[q][z]==0) a[q][z]=++tot;
            q=a[q][z];
        }
    }
    void change(int t)
    {
        int q=rt[t];
        for(int i=0;i<=20;++i)
        {
            if(q==0) break;
            f[t]^=(1<<i)*(b[q][1]&1);
            swap(a[q][0],a[q][1]);
            swap(b[q][0],b[q][1]);
            f[t]^=(1<<i)*(b[q][1]&1);
            q=a[q][0];
        }
    }
}
void dfs(int x)
{
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa[x]) continue;
        fa[a[i].m]=x;
        dfs(a[i].m);
        Tree::add(x,b[a[i].m],1);
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n-1;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        road(x,y);
        road(y,x);
    }
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&b[i]);
    }
    for(int i=1;i<=n;++i) Tree::rt[i]=++Tree::tot;
    dfs(1);
    for(int i=1;i<=m;++i)
    {
        int z;
        scanf("%d",&z);
        if(z==1)
        {
            int x;
            scanf("%d",&x);
            ++c[x];
            Tree::change(x);
            if(fa[fa[x]]!=0) Tree::add(fa[fa[x]],b[fa[x]]+c[fa[fa[x]]],-1);
            if(fa[x]!=0) ++b[fa[x]];
            if(fa[fa[x]]!=0) Tree::add(fa[fa[x]],b[fa[x]]+c[fa[fa[x]]],1);
        }
        else if(z==2)
        {
            int x,k;
            scanf("%d%d",&x,&k);
            if(fa[x]!=0) Tree::add(fa[x],b[x]+c[fa[x]],-1);
            b[x]-=k;
            if(fa[x]!=0) Tree::add(fa[x],b[x]+c[fa[x]],1);
        }
        else if(z==3)
        {
            int x;
            scanf("%d",&x);
            printf("%d\n",Tree::f[x]^(b[fa[x]]+c[fa[fa[x]]]));
        }
    }
    return 0;
}