#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
const int N=1000001;
int n,m,s1,s2,q,tot,b[N],d[N],f[N],l[N],fa[N];
vector<int> a[N],g[N],c,p;
vector<vector<int>> ans;
struct tree
{
    int b,c,f;
}T[N];
bool dfs(int x)
{
    T[x].b=T[x].c=++tot;
    bool u=false;
    if(x==s2) u=true;
    for(auto i:a[x])
    {
        if(T[i].b==0)
        {
            T[i].f=x;
            u|=dfs(i);
            T[x].c=min(T[x].c,T[i].c);
            ++l[x];
        }
        else T[x].c=min(T[x].c,T[i].b);
    }
    if(u) p.push_back(x);
    return u;
}
void dfs2(int x)
{
    if(d[x]) return;
    d[x]=++q;
    c.push_back(x);
    for(auto i:g[x]) dfs2(i);
}
void solve(vector<int> p)
{
    ans.push_back(p);
    for(int i=0;i+1<p.size();++i)
    {
        swap(f[p[i]],f[p[i+1]]);
    }
}
int main()
{
    scanf("%d%d%d%d",&n,&m,&s1,&s2);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&f[i]);
    }
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        a[x].push_back(y);
        a[y].push_back(x);
    }
    dfs(s1);
    for(int i=1;i<=n;++i) b[T[i].b]=i;
    queue<int> Q;
    reverse(p.begin(),p.end());
    for(auto i:p) l[i]=-1;
    for(int i=1;i<=n;++i)
    {
        if(l[i]==0) Q.push(i);
    }
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        g[b[T[k].c]].push_back(k);
        g[T[k].f].push_back(k);
        --l[T[k].f];
        if(l[T[k].f]==0) Q.push(T[k].f);
    }
    for(auto i:p) dfs2(i);
    for(int i=1;i<=n;++i)
    {
        bool u1=false,u2=false;
        for(auto j:a[i])
        {
            if(d[j]<d[i]) u1=true;
            if(d[j]>d[i]) u2=true;
        }
        if(((i!=s1)^u1)||((i!=s2)^u2))
        {
            printf("-1");
            return 0;
        }
    }
    // for(int i=1;i<=n;++i) printf("%d ",d[i]);printf("\n");
    for(int i=1;i<=n;++i)
    {
        for(auto j:a[i])
        {
            if(d[j]<d[i])
            {
                fa[i]=j;
                break;
            }
        }
    }
    reverse(c.begin(),c.end());
    for(auto i:c)
    {
        if(i==s2) continue;
        vector<int> p;
        int x=i;
        while(x) p.push_back(x),x=fa[x];
        reverse(p.begin(),p.end());
        x=i;
        while(x!=s2)
        {
            int z=0;
            for(auto j:a[x])
            {
                if(d[j]>d[x]&&(f[j]<f[z]||z==0)) z=j;
            }
            x=z;
            if(f[x]>f[s1]) break;
            p.push_back(x);
        }
        solve(p);
    }
    printf("%d\n",ans.size());
    for(auto i:ans)
    {
        printf("%d ",i.size());
        for(auto j:i) printf("%d ",j);
        printf("\n");
    }
    return 0;
}