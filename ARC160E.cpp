#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,b[N],l[N],f[N],fa[N];
bool g[N],h[N];
vector<int> a[N],c[N];
vector<pair<int,int>> ans;
void dfs0(int x)
{
    if(l[x]==1) f[x]=1;
    else f[x]=0;
    for(auto i:a[x])
    {
        if(i==fa[x]||g[i]) continue;
        fa[i]=x;
        dfs0(i);
        f[x]+=f[i];
    }
}
void dfs1(int x,vector<int> &c)
{
    if(l[x]==1) c.push_back(x);
    for(auto i:a[x])
    {
        if(i==fa[x]||g[i]) continue;
        dfs1(i,c);
    }
}
void dfs2(int x,int fa)
{
    h[x]=true;
    if(l[x]>=3) return;
    for(auto i:a[x])
    {
        if(i==fa) continue;
        dfs2(i,x);
    }
}
void dfs3(int x,int fa)
{
    if(l[x]>=3) return;
    g[x]=true;
    for(auto i:a[x])
    {
        if(i==fa) continue;
        dfs3(i,x);
    }
}
struct cmp
{
    bool operator()(int x,int y)
    {
        return c[x].size()<c[y].size();
    }
};
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i) a[i].clear(),c[i].clear(),l[i]=f[i]=fa[i]=h[i]=g[i]=0;
        ans.clear();
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&b[i]);
        }
        for(int i=1;i<=n-1;++i)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            a[x].push_back(y);
            a[y].push_back(x);
            ++l[x],++l[y];
        }
        m=0;
        for(int i=1;i<=n;++i)
        {
            if(l[i]==1) ++m;
        }
        if(m%2==1)
        {
            int u=0;
            for(int i=1;i<=n;++i)
            {
                if(l[i]>=3) ++u;
            }
            int o=0;
            if(u==1)
            {
                for(int i=1;i<=n;++i)
                {
                    if(l[i]<3&&(b[i]<b[o]||o==0)) o=i;
                }
            }
            else
            {
                for(int i=1;i<=n;++i)
                {
                    if(b[i]<b[o]||o==0) o=i;
                }
            }
            h[o]=true;
            for(auto i:a[o]) dfs2(i,o);
            int z=0;
            for(int i=1;i<=n;++i)
            {
                if(l[i]==1&&h[i]==false)
                {
                    z=i;
                    break;
                }
            }
            dfs3(z,0);
            ans.push_back(make_pair(o,z));
        }
        for(int i=1;i<=n;++i)
        {
            if(g[i]) continue;
            l[i]=0;
            for(auto j:a[i])
            {
                if(!g[j]) ++l[i];
            }
        }
        m=0;
        for(int i=1;i<=n;++i)
        {
            if(g[i]) continue;
            if(l[i]==1) ++m;
        }
        for(int i=1;i<=n;++i)
        {
            if(!g[i])
            {
                dfs0(i);
                break;
            }
        }
        int q=0;
        for(int i=1;i<=n;++i)
        {
            if(g[i]) continue;
            int w=0;
            for(auto j:a[i])
            {
                if(j!=fa[i]&&!g[j]) w=max(w,f[j]);
            }
            w=max(w,m-f[i]);
            if(w<=m/2) q=i;
        }
        fa[q]=0;
        dfs0(q);
        priority_queue<int,vector<int>,cmp> Q;
        for(auto i:a[q])
        {
            if(g[i]) continue;
            dfs1(i,c[i]);
            Q.push(i);
        }
        if(l[q]==1)
        {
            c[q].push_back(q);
            Q.push(q);
        }
        while(!Q.empty())
        {
            int k1=Q.top();
            Q.pop();
            int k2=Q.top();
            Q.pop();
            if(c[k1].size()==0) break;
            ans.push_back(make_pair(c[k1].back(),c[k2].back()));
            c[k1].pop_back(),c[k2].pop_back();
            Q.push(k1),Q.push(k2);
        }
        printf("%d\n",ans.size());
        for(auto i:ans)
        {
            printf("%d %d\n",i.first,i.second);
        }
    }
    return 0;
}