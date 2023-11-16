#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N=1000001;
int n,m,q,fa[N],g[N];
ll f[N],c[N];
vector<pair<int,ll>> a[N];
vector<ll> b[N],b2[N];
map<pair<int,int>,ld> Map;
int find(int x)
{
    if(fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}
pair<int,ll> dfs1(int x,int fa)
{
    pair<int,ll> s(x,0);
    for(auto i:a[x])
    {
        if(i.first==fa) continue;
        auto z=dfs1(i.first,x);
        z.second+=i.second;
        if(z.second>s.second) s=z;
    }
    return s;
}
void dfs2(int x,int fa,ll w)
{
    f[x]=max(f[x],w);
    for(auto i:a[x])
    {
        if(i.first==fa) continue;
        dfs2(i.first,x,w+i.second);
    }
}
void dfs3(int x,int fa,vector<ll> &b)
{
    b.push_back(f[x]);
    for(auto i:a[x])
    {
        if(i.first==fa) continue;
        dfs3(i.first,x,b);
    }
}
int find(vector<ll> &a,int x,ll b)
{
    if(a[x]>b) return -1;
    int t=0;
    while(t>=0)
    {
        if(x+(1<<t)<a.size()&&a[x+(1<<t)]<=b) x+=(1<<t),++t;
        else --t;
    }
    return x;
}
int main()
{
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=n;++i) fa[i]=i;
    for(int i=1;i<=m;++i)
    {
        int x,y;
        ll w=1;
        scanf("%d%d",&x,&y);
        fa[find(x)]=find(y);
        a[x].push_back(make_pair(y,w));
        a[y].push_back(make_pair(x,w));
    }
    for(int i=1;i<=n;++i) ++g[find(i)];
    for(int i=1;i<=n;++i)
    {
        if(find(i)!=i) continue;
        int x=dfs1(i,0).first;
        int y=dfs1(x,0).first;
        dfs2(x,0,0);
        dfs2(y,0,0);
        dfs3(i,0,b[i]);
        c[i]=f[x];
        sort(b[i].begin(),b[i].end());
        b2[i].resize(b[i].size());
        b2[i][0]=b[i][0];
        for(int j=1;j<b[i].size();++j) b2[i][j]=b2[i][j-1]+b[i][j];
    }
    for(int i=1;i<=q;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        if(find(x)==find(y))
        {
            printf("-1\n");
            continue;
        }
        x=find(x),y=find(y);
        if(g[x]>g[y]||(g[x]==g[y]&&x>y)) swap(x,y);
        if(Map.count(make_pair(x,y)))
        {
            printf("%.12Lf\n",Map[make_pair(x,y)]);
            continue;
        }
        ll w=max(c[x],c[y]),s1=0,s2=0;
        int p=0;
        ld s=0;
        for(int i=b[x].size()-1;i>=0;--i)
        {
            int z=find(b[y],p,w-b[x][i]-1);
            p=max(z,0);
            s+=w*(z+1);
            s+=(b[x][i]+1)*((ll)b[y].size()-(z+1));
            if(z>=0) s+=(b2[y][b[y].size()-1]-b2[y][z]);
            else s+=(b2[y][b[y].size()-1]);
        }
        s=s/((ll)b[x].size()*b[y].size());
        printf("%.12Lf\n",s);
        Map[make_pair(x,y)]=s;
    }
    return 0;
}