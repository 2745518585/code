#include<cstdio>
#include<algorithm>
#include<vector>
#include<set>
#include<map>
using namespace std;
const int N=1000001;
typedef unsigned long long ull;
int n1,n2,rt1,rt2,d1[N],d2[N],g[N];
ull f1[N],f2[N];
bool h[N];
vector<int> a1[N],a2[N];
map<pair<int,int>,bool> Map;
struct str
{
    int x,t;
    str(){}
    str(int x,int t):x(x),t(t){}
    friend bool operator<(str a,str b)
    {
        return a.x<b.x;
    }
};
void dfs1(int x)
{
    f1[x]=10007;
    d1[x]=1;
    for(auto i:a1[x])
    {
        dfs1(i);
        d1[x]+=d1[i];
        f1[x]+=f1[i]*(f1[i]+1)+1;
    }
}
void dfs2(int x)
{
    f2[x]=10007;
    d2[x]=1;
    for(auto i:a2[x])
    {
        dfs2(i);
        d2[x]+=d2[i];
        f2[x]+=f2[i]*(f2[i]+1)+1;
    }
}
bool dfs(int x1,int x2);
bool solve(int x,vector<int> p1,vector<int> p2,int t)
{
    if(x==p2.size())
    {
        for(auto i:p2)
        {
            if(!dfs(g[i],i)) return false;
        }
        return true;
    }
    for(auto i:p1)
    {
        if(h[i]||d1[i]<=d2[p2[x]]||d1[i]-d2[p2[x]]>t) continue;
        g[p2[x]]=i;
        h[i]=true;
        if(solve(x+1,p1,p2,t)) return true;
        h[i]=false;
    }
    return false;
}
bool dfs(int x1,int x2)
{
    if(Map.count(make_pair(x1,x2))) return Map[make_pair(x1,x2)];
    multiset<str> Set;
    vector<int> p1,p2;
    for(auto i:a1[x1]) Set.insert(str(f1[i],i));
    for(auto i:a2[x2])
    {
        if(Set.count(str(f2[i],0)))
        {
            Set.erase(Set.find(str(f2[i],0)));
            continue;
        }
        p2.push_back(i);
    }
    for(auto i:Set) p1.push_back(i.t);
    for(auto i:p1) h[i]=false;
    return Map[make_pair(x1,x2)]=solve(0,p1,p2,d1[x1]-d2[x2]-p2.size()+1);
}
int main()
{
    int T;
    scanf("%*d%d%*d",&T);
    while(T--)
    {
        Map.clear();
        scanf("%d",&n1);
        for(int i=1;i<=n1;++i) a1[i].clear();
        for(int i=1;i<=n1;++i)
        {
            int x;
            scanf("%d",&x);
            if(x==-1) rt1=i;
            else a1[x].push_back(i);
        }
        scanf("%d",&n2);
        for(int i=1;i<=n2;++i) a2[i].clear();
        for(int i=1;i<=n2;++i)
        {
            int x;
            scanf("%d",&x);
            if(x==-1) rt2=i;
            else a2[x].push_back(i);
        }
        dfs1(rt1);
        dfs2(rt2);
        if(dfs(rt1,rt2)) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}