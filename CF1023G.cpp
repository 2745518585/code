#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
using namespace std;
const int N=2000001;
int n,m,h[N];
vector<pair<int,int>> a[N],b[N];
map<int,int> f1[N],f2[N];
struct str
{
    int x,y;
    str() {}
    str(int x,int y):x(x),y(y) {}
};
bool operator>(str a,str b)
{
    return a.x-a.y>b.x-b.y;
}
priority_queue<str,vector<str>,greater<str>> g[N];
void solve(int x,int t)
{
    while(!g[x].empty())
    {
        str k=g[x].top();
        if(k.x-k.y>(h[x]+t)*2) break;
        g[x].pop();
        if(!f1[x].count(k.x)||!f2[x].count(k.y)) continue;
        if(f1[x][k.x]+f2[x][k.y]>0)
        {
            f1[x][k.x]+=f2[x][k.y];
            f2[x].erase(k.y);
            auto z=f2[x].upper_bound(k.x-h[x]*2);
            if(z!=f2[x].begin()) g[x].push(str(k.x,prev(z)->first));
        }
        else if(f1[x][k.x]+f2[x][k.y]<0)
        {
            f2[x][k.y]+=f1[x][k.x];
            f1[x].erase(k.x);
            auto z=f1[x].lower_bound(k.y+h[x]*2);
            if(z!=f1[x].end()) g[x].push(str(z->first,k.y));
        }
        else
        {
            f1[x].erase(k.x);
            f2[x].erase(k.y);
        }
    }
    h[x]+=t;
}
void add(int x,int t,int k)
{
    if(k>0)
    {
        t+=h[x];
        if(f1[x].count(t))
        {
            f1[x][t]+=k;
            return;
        }
        f1[x][t]=k;
        auto z=f2[x].upper_bound(t-h[x]*2);
        if(z!=f2[x].begin()) g[x].push(str(t,prev(z)->first));
    }
    else if(k<0)
    {
        t-=h[x];
        if(f2[x].count(t))
        {
            f2[x][t]+=k;
            return;
        }
        f2[x][t]=k;
        auto z=f1[x].lower_bound(t+h[x]*2);
        if(z!=f1[x].end()) g[x].push(str(z->first,t));
    }
}
int query(int x,int t)
{
    int z=0;
    if(f1[x].count(t+h[x])) z+=f1[x][t+h[x]];
    if(f2[x].count(t-h[x])) z+=f2[x][t-h[x]];
    return z;
}
int sum(int x)
{
    int s=0,w=0;
    auto p1=f1[x].begin(),p2=f2[x].begin();
    while(p1!=f1[x].end()||p2!=f2[x].end())
    {
        if(p1!=f1[x].end()&&(p2==f2[x].end()||p1->first-h[x]<p2->first+h[x]))
        {
            w+=p1->second;
            ++p1;
        }
        else
        {
            w+=p2->second;
            ++p2;
        }
        s=max(s,w);
    }
    return s;
}
void dfs(int x,int fa)
{
    for(auto i:a[x])
    {
        if(i.first==fa) continue;
        dfs(i.first,x);
        for(auto &j:b[i.first]) j.second-=max(max(-query(i.first,j.first),query(i.first,j.first+1)),0);
        solve(i.first,1);
        // printf("%d %d %d:\n",x,i.first,h[i.first]);
        // for(auto j:f1[i.first]) printf("%d %d\n",j.first,j.second);
        // for(auto j:f2[i.first]) printf("%d %d\n",j.first,j.second);
        for(auto j:b[i.first])
        {
            if(j.second>0)
            {
                // printf(" %d %d\n",j.first,j.second);
                add(i.first,j.first,j.second);
                add(i.first,j.first+1,-j.second);
            }
        }
        // printf("%d %d %d:\n",x,i.first,h[i.first]);
        // for(auto j:f1[i.first]) printf("%d %d\n",j.first,j.second);
        // for(auto j:f2[i.first]) printf("%d %d\n",j.first,j.second);
        solve(i.first,i.second-1);
        // printf("%d %d %d:\n",x,i.first,h[i.first]);
        // for(auto j:f1[i.first]) printf("%d %d\n",j.first,j.second);
        // for(auto j:f2[i.first]) printf("%d %d\n",j.first,j.second);
        if(f1[x].size()+f2[x].size()<f1[i.first].size()+f2[i.first].size())
        {
            swap(f1[x],f1[i.first]);
            swap(f2[x],f2[i.first]);
            swap(g[x],g[i.first]);
            swap(h[x],h[i.first]);
        }
        for(auto j:f1[i.first]) add(x,j.first-h[i.first],j.second);
        for(auto j:f2[i.first]) add(x,j.first+h[i.first],j.second);
    }
    // printf("%d %d:\n",x,h[x]);
    // for(auto i:f1[x]) printf("%d %d\n",i.first,i.second);
    // for(auto i:f2[x]) printf("%d %d\n",i.first,i.second);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n-1;++i)
    {
        int x,y,w;
        scanf("%d%d%d",&x,&y,&w);
        w*=2;
        a[x].push_back(make_pair(y,w));
        a[y].push_back(make_pair(x,w));
    }
    a[0].push_back(make_pair(1,2));
    scanf("%d",&m);
    for(int i=1;i<=m;++i)
    {
        int t,k,x;
        scanf("%d%d%d",&t,&k,&x);
        t*=2;
        b[x].push_back(make_pair(t,k));
    }
    dfs(0,0);
    printf("%d",sum(0));
    return 0;
}