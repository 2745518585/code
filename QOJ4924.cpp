#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
typedef __int128_t lll;
const int N=200001;
int n,m,q,b[N];
ll d[N],d2[N];
vector<pair<int,ll>> a[N];
vector<pair<pair<int,int>,pair<ll,int>>> c;
vector<int> e[N];
pair<ll,ll> f[N<<6];
struct pt
{
    ll x,y;
    pt() {}
    pt(ll x,ll y):x(x),y(y) {}
};
bool cmp(const pt &x,const pt &y)
{
    if(x.x!=y.x) return x.x<y.x;
    return x.y>y.y;
}
void insert(vector<pt> &s,const pt &p)
{
    while(s.size()>1)
    {
        pt p1=s.back(),p2=*prev(prev(s.end()));
        if((lll)(p1.y-p2.y)*(p.x-p2.x)<(lll)(p.y-p2.y)*(p1.x-p2.x)) s.pop_back();
        else break;
    }
    s.push_back(p);
}
void query(const vector<pt> &s,const vector<pair<int,int>> &x)
{
    if(s.empty()) return;
    auto p=s.begin();
    for(auto i:x)
    {
        while(next(p)!=s.end())
        {
            auto p2=next(p);
            if((p2->y-p->y)>f[i.first].first*(p2->x-p->x)) ++p;
            else break;
        }
        d[i.second]=min(d[i.second],p->x*f[i.first].first-p->y+f[i.first].second);
    }
}
struct sgt
{
    vector<pt> a[N];
    struct tree
    {
        int l,r;
        vector<pt> s;
        vector<pair<int,int>> q;
    }T[N<<2];
    void pushup(int x)
    {
        auto p1=T[x<<1].s.begin(),p2=T[x<<1|1].s.begin();
        while(p1!=T[x<<1].s.end()||p2!=T[x<<1|1].s.end())
        {
            if(p1!=T[x<<1].s.end()&&(p2==T[x<<1|1].s.end()||p1->x<=p2->x)) insert(T[x].s,*p1),++p1;
            else insert(T[x].s,*p2),++p2;
        }
    }
    void build(int x,int l,int r)
    {
        T[x].l=l,T[x].r=r;
        if(l==r) return;
        int z=l+r>>1;
        build(x<<1,l,z);
        build(x<<1|1,z+1,r);
    }
    void add(int x,int l,int r,int k,int t)
    {
        if(T[x].l>=l&&T[x].r<=r)
        {
            T[x].q.push_back(make_pair(k,t));
            return;
        }
        int z=T[x].l+T[x].r>>1;
        if(l<=z) add(x<<1,l,r,k,t);
        if(r>z) add(x<<1|1,l,r,k,t);
    }
    void solve(int x)
    {
        if(T[x].l==T[x].r)
        {
            sort(a[T[x].l].begin(),a[T[x].l].end(),cmp);
            for(auto i:a[T[x].l]) insert(T[x].s,pt(i.x,-i.y));
            vector<pt>().swap(a[T[x].l]);
            query(T[x].s,T[x].q);
            return;
        }
        solve(x<<1);
        solve(x<<1|1);
        pushup(x);
        query(T[x].s,T[x].q);
        vector<pt>().swap(T[x<<1].s);
        vector<pt>().swap(T[x<<1|1].s);
    }
}T1,T2,T3;
int mk(ll x,ll y)
{
    static int v=0;
    f[++v]=make_pair(x,y);
    return v;
}
namespace tc
{
    int tot;
    struct tree
    {
        int f,s,d,t,z,b,bm;
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
            T[i.first].h=T[x].h+i.second;
            dfs1(i.first);
            T[x].s+=T[i.first].s;
            if(T[i.first].s>T[T[x].z].s) T[x].z=i.first;
        }
    }
    void dfs2(int x,int t)
    {
        T[x].b=++tot;
        T[x].t=t;
        if(T[x].z) dfs2(T[x].z,t);
        for(auto i:a[x])
        {
            if(i.first==T[x].f||i.first==T[x].z) continue;
            dfs2(i.first,i.first);
        }
        T[x].bm=tot;
    }
    void solve(int x,int y,ll p,int t)
    {
        d2[t]+=T[x].h+T[y].h;
        while(T[x].t!=T[y].t)
        {
            if(T[T[x].t].d>T[T[y].t].d)
            {
                T1.add(1,T[T[x].t].b,T[x].b,mk(p,0),t);
                T3.add(1,T[x].b,T[x].bm,mk(p,-T[x].h*2),t);
                x=T[T[x].t].f;
            }
            else
            {
                T1.add(1,T[T[y].t].b,T[y].b,mk(p,0),t);
                T3.add(1,T[y].b,T[y].bm,mk(p,-T[y].h*2),t);
                y=T[T[y].t].f;
            }
        }
        if(T[x].d>T[y].d) swap(x,y);
        T1.add(1,T[x].b,T[y].b,mk(p,0),t);
        T3.add(1,T[y].b,T[y].bm,mk(p,-T[y].h*2),t);
        int z=x;
        while(x)
        {
            T2.add(1,T[T[x].t].b,T[x].b,mk(p,T[z].h*2),t);
            T3.add(1,T[x].b,T[x].bm,mk(p,(T[z].h-T[x].h)*2-T[x].h*2),t);
            x=T[T[x].t].f;
        }
        d2[t]-=T[z].h*2;
    }
    void dfs(int x)
    {
        if(T[x].z)
        {
            dfs(T[x].z);
            swap(e[x],e[T[x].z]);
        }
        for(auto i:a[x])
        {
            if(i.first==T[x].f||i.first==T[x].z) continue;
            dfs(i.first);
            for(auto j:e[i.first])
            {
                e[x].push_back(j);
                T1.a[T[x].b].push_back(pt(b[j],(T[j].h-T[x].h)*2));
                T2.a[T[x].b].push_back(pt(b[j],(T[j].h-T[x].h)*2-T[x].h*2));
            }
        }
        T1.a[T[x].b].push_back(pt(b[x],0));
        T2.a[T[x].b].push_back(pt(b[x],-T[x].h*2));
        T3.a[T[x].b].push_back(pt(b[x],T[x].h*2));
        e[x].push_back(x);
    }
}
bool cmp2(const pair<pair<int,int>,pair<ll,int>> &a,const pair<pair<int,int>,pair<ll,int>> &b)
{
    return a.second.first>b.second.first;
}
int main()
{
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&b[i]);
    }
    for(int i=1;i<=n-1;++i)
    {
        int x,y;
        ll w;
        scanf("%d%d%lld",&x,&y,&w);
        a[x].push_back(make_pair(y,w));
        a[y].push_back(make_pair(x,w));
    }
    tc::dfs1(1);
    tc::dfs2(1,1);
    tc::dfs(1);
    T1.build(1,1,n);
    T2.build(1,1,n);
    T3.build(1,1,n);
    for(int i=1;i<=q;++i)
    {
        ll x,y;
        scanf("%lld%lld",&x,&y);
        c.push_back(make_pair(make_pair((x-1)%n+1,(y-1)%n+1),make_pair(abs((x-1)/n-(y-1)/n),i)));
        d[i]=1e18;
    }
    sort(c.begin(),c.end(),cmp2);
    for(auto i:c)
    {
        tc::solve(i.first.first,i.first.second,i.second.first,i.second.second);
    }
    T1.solve(1);
    T2.solve(1);
    T3.solve(1);
    for(int i=1;i<=q;++i)
    {
        printf("%lld\n",d[i]+d2[i]);
    }
    return 0;
}