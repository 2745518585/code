#include<cstdio>
#include<algorithm>
#include<vector>
#include<stack>
using namespace std;
const int N=1000001;
int n,m,q,tot;
bool g[N],h[N];
vector<pair<int,int>> a[N];
vector<int> b[N],p;
stack<int> S;
struct tree
{
    int b,c;
}T[N];
void dfs(int x,int fa)
{
    T[x].b=T[x].c=++tot;
    S.push(x);
    for(auto i:a[x])
    {
        if(i.first==fa) continue;
        if(T[i.first].b==0)
        {
            dfs(i.first,x);
            T[x].c=min(T[x].c,T[i.first].c);
            if(T[i.first].c>=T[x].b)
            {
                ++q;
                while(S.top()!=i.first)
                {
                    b[q].push_back(S.top());
                    S.pop();
                }
                b[q].push_back(S.top());
                S.pop();
                b[q].push_back(x);
            }
        }
        T[x].c=min(T[x].c,T[i.first].b);
    }
}
void dfs2(int x)
{
    g[x]=false;
    for(auto i:a[x])
    {
        if(!h[i.first]) continue;
        p.push_back(i.second);
        if(g[i.first]) dfs2(i.first);
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        a[x].push_back(make_pair(y,i));
        a[y].push_back(make_pair(x,i));
    }
    for(int i=1;i<=n;++i)
    {
        if(T[i].b==0) dfs(i,0);
    }
    vector<int> w;
    for(int i=1;i<=q;++i)
    {
        // for(auto j:b[i]) printf("%d ",j);printf("\n");
        for(auto j:b[i]) g[j]=h[j]=true;
        p.clear();
        dfs2(b[i].front());
        sort(p.begin(),p.end());
        p.resize(distance(p.begin(),unique(p.begin(),p.end())));
        if(p.size()==b[i].size())
        {
            for(auto j:p) w.push_back(j);
        }
        for(auto j:b[i]) g[j]=h[j]=false;
    }
    sort(w.begin(),w.end());
    w.resize(distance(w.begin(),unique(w.begin(),w.end())));
    printf("%d\n",w.size());
    for(auto i:w) printf("%d ",i);
    return 0;
}