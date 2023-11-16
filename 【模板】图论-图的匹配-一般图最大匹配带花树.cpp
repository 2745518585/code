#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
const int N=1000001;
int n,m,p=1,t[N],fa[N],o,b[N],f[N],g[N],h[N];
struct road
{
    int m,q;
}a[N<<1];
queue<int> Q;
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
int find(int x)
{
    if(fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}
int LCA(int x,int y)
{
    ++o;
    while(true)
    {
        if(x!=0)
        {
            x=find(x);
            if(b[x]==o) return x;
            b[x]=o;
            x=f[g[x]];
        }
        swap(x,y);
    }
    return x;
}
void merge(int x,int y,int k)
{
    while(find(x)!=k)
    {
        f[x]=y,y=g[x];
        h[y]=1,Q.push(y);
        if(find(x)==x) fa[x]=k;
        if(find(y)==y) fa[y]=k;
        x=f[y];
    }
}
bool bfs(int x)
{
    for(int i=1;i<=n;++i) fa[i]=i,f[i]=h[i]=0;
    while(!Q.empty()) Q.pop();
    Q.push(x);
    h[x]=1;
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        for(int i=t[k];i!=0;i=a[i].q)
        {
            if(find(k)==find(a[i].m)||h[a[i].m]==2) continue;
            if(h[a[i].m]==0)
            {
                h[a[i].m]=2;
                f[a[i].m]=k;
                if(g[a[i].m]==0)
                {
                    int z=a[i].m;
                    while(z!=0)
                    {
                        int z1=f[z],z2=g[z1];
                        g[z]=z1,g[z1]=z;
                        z=z2;
                    }
                    return true;
                }
                h[g[a[i].m]]=1;
                Q.push(g[a[i].m]);
            }
            else
            {
                int z=LCA(k,a[i].m);
                merge(k,a[i].m,z);
                merge(a[i].m,k,z);
            }
        }
    }
    return false;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        road(x,y);
        road(y,x);
    }
    int s=0;
    for(int i=1;i<=n;++i)
    {
        if(g[i]==0) s+=bfs(i);
    }
    printf("%d\n",s);
    for(int i=1;i<=n;++i)
    {
        printf("%d ",g[i]);
    }
    return 0;
}