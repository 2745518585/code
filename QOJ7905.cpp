#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=100001;
int n,m,fa[N],ga[N],p[N];
ll f[N],g[N],h[N],d[N];
vector<pair<int,int>> b[N];
int find(int x)
{
    if(fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}
void merge(int x,int y)
{
    x=find(x),y=find(y);
    if(ga[x]<ga[y]) fa[x]=y,ga[y]+=ga[x];
    else fa[y]=x,ga[x]+=ga[y];
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;++i) b[i].clear();
        for(int i=1;i<=m;++i)
        {
            int x,y,w;
            scanf("%d%d%d",&x,&y,&w);
            ++x;
            b[y].push_back(make_pair(x,w));
        }
        for(int i=0;i<=n;++i) f[i]=g[i]=h[i]=-1e9;
        f[0]=0;
        for(int i=0;i<=n-1;++i)
        {
            for(int j=0;j<=n;++j) g[j]=f[j],f[j]=-1e9,h[j]=0;
            for(int j=0;j<=n;++j) fa[j]=j,ga[j]=1,p[j]=0;
            h[i]=0;
            for(int j=i+1;j<=n;++j)
            {
                h[j]=g[j-1];
                if(h[j]<=h[find(j-1)])
                {
                    h[j]=h[find(j-1)];
                    merge(j-1,j);
                    p[find(j)]=0;
                }
                else
                {
                    h[find(j-1)]=h[find(j-1)]-h[j];
                    p[find(j-1)]=j;
                }
                for(auto k:b[j])
                {
                    int x=find(k.first-1);
                    h[x]+=k.second;
                    while(p[x]&&h[x]>=0)
                    {
                        p[x]=find(p[x]);
                        h[p[x]]+=h[x];
                        h[x]=h[p[x]];
                        merge(x,p[x]);
                        p[x]=p[p[x]];
                        x=find(x);
                    }
                }
                f[j]=h[find(j)];
            }
            d[n-i]=f[n];
        }
        for(int i=1;i<=n;++i)
        {
            printf("%lld ",d[i]);
        }
        printf("\n");
    }
    return 0;
}