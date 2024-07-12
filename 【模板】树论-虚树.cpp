#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,tot,b[N],S[N],t;
ll f[N];
bool h[N];
vector<pair<int,int>> a[N];
vector<int> a2[N];
struct tree
{
    int f,s,d,t,z,b;
    ll h;
}T[N];
void dfs1(int x)
{
    T[x].s=1;
    T[x].d=T[T[x].f].d+1;
    for(auto i:a[x])
    {
        if(i.first==T[x].f) continue;
        T[i.first].f=x;
        T[i.first].h=min(T[x].h,(ll)i.second);
        dfs1(i.first);
        T[x].s+=T[i.first].s;
        if(T[i.first].s>T[T[x].z].s) T[x].z=i.first;
    }
}
void dfs2(int x,int t)
{
    T[x].t=t;
    T[x].b=++tot;
    if(T[x].z) dfs2(T[x].z,t);
    for(auto i:a[x])
    {
        if(i.first==T[x].f||i.first==T[x].z) continue;
        dfs2(i.first,i.first);
    }
}
int LCA(int x,int y)
{
    while(T[x].t!=T[y].t)
    {
        if(T[T[x].t].d>T[T[y].t].d) x=T[T[x].t].f;
        else y=T[T[y].t].f;
    }
    if(T[x].d<T[y].d) return x;
    else return y;
}
void dfs(int x)
{
    f[x]=0;
    for(auto i:a2[x])
    {
        dfs(i);
        f[x]+=f[i];
    }
    if(h[x]) f[x]=T[x].h;
    else f[x]=min(f[x],T[x].h);
}
bool cmp(int x,int y)
{
    return T[x].b<T[y].b;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n-1;++i)
    {
        int x,y,w;
        scanf("%d%d%d",&x,&y,&w);
        a[x].push_back(make_pair(y,w));
        a[y].push_back(make_pair(x,w));
    }
    T[1].h=1e18;
    dfs1(1);
    dfs2(1,1);
    scanf("%d",&m);
    for(int i=1;i<=m;++i)
    {
        int k;
        scanf("%d",&k);
        for(int j=1;j<=k;++j)
        {
            scanf("%d",&b[j]);
            h[b[j]]=true;
        }
        sort(b+1,b+k+1,cmp);
        S[t=1]=1;
        a2[1].clear();
        for(int j=1;j<=k;++j)
        {
            int z=LCA(b[j],S[t]);
            while(t>1&&T[z].d<=T[S[t-1]].d)
            {
                a2[S[t-1]].push_back(S[t]);
                --t;
            }
            a2[b[j]].clear();
            if(z!=S[t])
            {
                a2[z].clear();
                h[z]=false;
                a2[z].push_back(S[t]);
                S[t]=z;
            }
            S[++t]=b[j];
        }
        while(t>1)
        {
            a2[S[t-1]].push_back(S[t]);
            --t;
        }
        dfs(1);
        printf("%lld\n",f[1]);
    }
    return 0;
}