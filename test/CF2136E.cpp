#include<cstdio>
#include<algorithm>
#include<vector>
#include<stack>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll P=998244353;
int n,m,q,tot,h[N],r[N];
ll k,b[N];
bool g[N];
vector<pair<int,int>> a[N];
vector<int> d[N];
stack<int> S;
struct tree
{
    int b,c;
}T[N];
void dfs(int x,int fa)
{
    T[x].b=T[x].c=++tot;
    for(auto i:a[x])
    {
        if(i.first==fa) continue;
        if(T[i.first].b==0)
        {
            dfs(i.first,x);
            T[x].c=min(T[x].c,T[i.first].c);
            if(T[i.first].c>T[x].b) g[i.second]=true;
        }
        T[x].c=min(T[x].c,T[i.first].b);
    }
}
void dfs2(int x)
{
    for(auto i:a[x])
    {
        if(r[i.first]!=0||g[i.second]) continue;
        r[i.first]=r[x];
        dfs2(i.first);
    }
}
bool dfs3(int x)
{
    for(auto i:a[x])
    {
        if(g[i.second]) continue;
        if(h[i.first]==0) 
        {
            h[i.first]=-h[x];
            if(dfs3(i.first)) return true;
        }
        if(h[i.first]!=-h[x]) return true;
    }
    return false;
}
int main()
{
    int TOT;
    scanf("%d",&TOT);
    while(TOT--)
    {
        scanf("%d%d%lld",&n,&m,&k);
        tot=q=0;
        for(int i=1;i<=n;++i) T[i].b=T[i].c=h[i]=r[i]=0,a[i].clear(),d[i].clear();
        for(int i=1;i<=m;++i) g[i]=false;
        for(int i=1;i<=n;++i)
        {
            scanf("%lld",&b[i]);
        }
        for(int i=1;i<=m;++i)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            a[x].push_back(make_pair(y,i));
            a[y].push_back(make_pair(x,i));
        }
        dfs(1,0);
        for(int i=1;i<=n;++i)
        {
            if(r[i]==0)
            {
                r[i]=++q;
                dfs2(i);
            }
        }
        for(int i=1;i<=n;++i) d[r[i]].push_back(i);
        ll s=1;
        for(int i=1;i<=q;++i)
        {
            // for(auto j:d[i]) printf("%d ",j);printf("\n");
            h[d[i][0]]=1;
            if(dfs3(d[i][0]))
            {
                for(auto j:d[i])
                {
                    if(b[j]!=-1&&b[j]!=0) s=0;
                }
            }
            else
            {
                ll u=-1;
                for(auto j:d[i])
                {
                    if(b[j]!=-1)
                    {
                        if(b[j]!=u&&u!=-1) s=0;
                        u=b[j];
                    }
                }
                if(u==-1) s=s*k%P;
            }
        }
        printf("%lld\n",s);
    }
    return 0;
}