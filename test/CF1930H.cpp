#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=1000001;
int n,m,tot1,tot2,b1[N],b2[N],c1[N],c2[N],d[N],fa[N];
vector<int> a[N];
void dfs(int x)
{
    b1[x]=++tot1;
    for(auto i:a[x])
    {
        if(i==fa[x]) continue;
        d[i]=d[x]+1;
        fa[i]=x;
        dfs(i);
    }
    b2[x]=++tot2;
}
int LCA(int x,int y,int &xx,int &yy)
{
    while(d[x]>d[y]) x=fa[x];
    while(d[y]>d[x]) y=fa[y];
    while(x!=y) xx=x,yy=y,x=fa[x],y=fa[y];
    return x;
}
int query(int z,int x,int y)
{
    if(x>y) return n;
    printf("? %d %d %d\n",z,x,y);
    fflush(stdout);
    int w;
    scanf("%d",&w);
    return w;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;++i) a[i].clear();
        tot1=tot2=0;
        for(int i=1;i<=n-1;++i)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            a[x].push_back(y);
            a[y].push_back(x);
        }
        dfs(1);
        for(int i=1;i<=n;++i) c1[b1[i]]=i,c2[b2[i]]=i;
        for(int i=1;i<=n;++i) printf("%d ",c1[i]);printf("\n");
        for(int i=1;i<=n;++i) printf("%d ",c2[i]);printf("\n");
        fflush(stdout);
        for(int i=1;i<=m;++i)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            if(b1[x]>b1[y]) swap(x,y);
            int xx=0,yy=0,z=LCA(x,y,xx,yy),s=n;
            if(z==x||z==y)
            {
                if(z==y) swap(x,y);
                s=min(s,query(1,1,b1[x]-1));
                s=min(s,query(2,1,b2[y]-1));
                s=min(s,query(1,b1[y]+1,n));
            }
            else
            {
                s=min(s,query(1,1,b1[z]-1));
                s=min(s,query(2,1,b2[x]-1));
                s=min(s,query(1,b1[x]+1,b1[yy]-1));
                s=min(s,query(2,b2[xx]+1,b2[y]-1));
                s=min(s,query(1,b1[y]+1,n));
            }
            printf("! %d\n",s);
            fflush(stdout);
            scanf("%*d");
        }
    }
    return 0;
}