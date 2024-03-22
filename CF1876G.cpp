#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,a[N],fa[N],h[N],l[N];
ll f[N];
map<int,int> Map;
vector<pair<int,int>> b1[N];
vector<int> b2[N],c[N];
int find(int x)
{
    if(fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}
void add(int x,int t)
{
    h[t]=x;
    if(!Map.count(x)) Map[x]=t;
    else
    {
        int z=Map[x];
        c[z].push_back(t);
        f[t]-=f[z];
        fa[t]=z;
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    scanf("%d",&m);
    for(int i=1;i<=m;++i)
    {
        int l,r,v;
        scanf("%d%d%d",&l,&r,&v);
        b1[r].push_back(make_pair(i,v));
        b2[l].push_back(i);
    }
    for(int i=1;i<=m*2;++i) fa[i]=i;
    for(int i=n;i>=1;--i)
    {
        for(auto j:b1[i]) add(j.second,j.first);
        auto x=Map.upper_bound(a[i]);
        while(x!=Map.end())
        {
            int z=(x->first+a[i])/2;
            ll v=(ll)((x->first-a[i]+1)/2)*i;
            f[x->second]+=v;
            add(z,x->second);
            ++x;
            Map.erase(prev(x));
        }
        for(auto j:b2[i])
        {
            add(h[find(j)],m+j);
        }
    }
    queue<int> Q;
    for(int i=1;i<=m*2;++i)
    {
        for(auto j:c[i]) ++l[j];
    }
    for(int i=1;i<=m*2;++i)
    {
        if(l[i]==0) Q.push(i);
    }
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        for(auto i:c[k])
        {
            f[i]+=f[k];
            --l[i];
            if(l[i]==0) Q.push(i);
        }
    }
    for(int i=1;i<=m;++i)
    {
        printf("%lld\n",f[i]-f[m+i]);
    }
    return 0;
}