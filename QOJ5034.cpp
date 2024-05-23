#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,q,tot,c[N],rt[N],fl[N];
ll f[N];
bool h[N];
map<pair<int,int>,int> a;
map<int,int> b[N];
struct str
{
    int x;
    ll w;
    str() {}
    str(int x,ll w):x(x),w(w) {}
    friend bool operator<(str a,str b)
    {
        return a.w>b.w;
    }
};
namespace sgt
{
    int tot;
    struct tree
    {
        int l,r,t;
    }T[N<<4];
    void pushup(int &x)
    {
        if(!T[x].l&&!T[x].r) x=0;
    }
    void add(int &x,int ls,int rs,int q,int t)
    {
        T[++tot]=T[x],x=tot;
        if(ls==rs)
        {
            T[x].t=t;
            return;
        }
        int z=ls+rs>>1;
        if(q<=z) add(T[x].l,ls,z,q,t);
        else add(T[x].r,z+1,rs,q,t);
        pushup(x);
    }
    int sum(int x,int ls,int rs,int q)
    {
        if(ls==rs) return T[x].t;
        int z=ls+rs>>1;
        if(q<=z) return sum(T[x].l,ls,z,q);
        else return sum(T[x].r,z+1,rs,q);
    }
    void dfs(int &x,int ls,int rs,auto p)
    {
        if(x==0) return;
        if(ls==rs)
        {
            p(T[x].t);
            x=0;
            return;
        }
        int z=ls+rs>>1;
        dfs(T[x].l,ls,z,p);
        dfs(T[x].r,z+1,rs,p);
        pushup(x);
    }
}
int main()
{
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=m;++i)
    {
        int x,y,w;
        scanf("%d%d%d",&x,&y,&w);
        if(!a.count(make_pair(x,y))) a[make_pair(x,y)]=w;
        else a[make_pair(x,y)]=min(a[make_pair(x,y)],w);
    }
    for(int i=1;i<=n;++i)
    {
        b[0][i]=++tot;
        c[tot]=i;
    }
    for(int i=1;i<=q;++i)
    {
        int k;
        scanf("%d",&k);
        int x=0;
        for(int j=1;j<=k;++j)
        {
            int z;
            scanf("%d",&z);
            if(!b[x].count(z))
            {
                b[x][z]=++tot;
                c[tot]=z;
            }
            x=b[x][z];
        }
        h[x]=true;
    }
    {
        queue<int> Q;
        for(int i=1;i<=n;++i)
        {
            sgt::add(rt[0],1,n,i,i);
            Q.push(i);
        }
        for(auto i:a)
        {
            sgt::add(rt[i.first.first],1,n,i.first.second,i.first.second);
        }
        while(!Q.empty())
        {
            int k=Q.front();
            Q.pop();
            if(k>n) rt[k]=rt[fl[k]];
            for(auto i:b[k])
            {
                if(a.count(make_pair(c[k],i.first)))
                {
                    fl[i.second]=sgt::sum(rt[fl[k]],1,n,i.first);
                    sgt::add(rt[k],1,n,i.first,i.second);
                    Q.push(i.second);
                }
            }
        }
    }
    // for(int i=1;i<=tot;++i) printf("%d %d\n",i,fl[i]);
    // printf("%d\n",sgt::sum(rt[10],1,n,6));
    // printf("%d\n",sgt::sum(rt[14],1,n,6));
    // return 0;
    for(int i=1;i<=tot;++i) f[i]=1e18;
    f[1]=0;
    priority_queue<str> Q;
    Q.push(str(1,0));
    while(!Q.empty())
    {
        int k=Q.top().x;
        Q.pop();
        if(h[k]) continue;
        h[k]=true;
        // printf("%d %lld\n",k,f[k]);
        sgt::dfs(rt[k],1,n,[&](int x){
            // printf("%d -> %d: %d\n",k,x,a[make_pair(c[k],c[x])]);
            f[x]=min(f[x],f[k]+a[make_pair(c[k],c[x])]);
            Q.push(str(x,f[x]));
        });
    }
    printf("%lld",f[n]==1e18?-1:f[n]);
    return 0;
}