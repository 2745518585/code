#include<cstdio>
#include<algorithm>
#include<vector>
#include<stack>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,q,p=1,t[N],t2[N],tot;
int f[N],g[N],b[N],d[N];
stack<int> S;
struct road
{
    int m,q;
}a[N<<1];
struct tree
{
    int b,c;
}T[N];
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
void road2(int x,int y)
{
    a[++p].m=y;
    a[p].q=t2[x];
    t2[x]=p;
}
struct query
{
    int x,u,t;
    query(){}
    query(int x,int u,int t):x(x),u(u),t(t){}
};
vector<query> c[N];
int rt[N];
namespace Segment_tree
{
    int tot;
    struct tree
    {
        int l,r,t,s1,s2;
    }T[N<<2];
    void pushup(int x)
    {
        T[x].s1=T[T[x].l].s1+T[T[x].r].s1;
        T[x].s2=T[T[x].l].s2+T[T[x].r].s2;
    }
    void add(int &x,int ls,int rs,int q)
    {
        if(x==0)
        {
            x=++tot;
            T[x].s1=T[x].t;
            T[x].s2=T[x].t^1;
        }
        if(ls==rs)
        {
            T[x].t^=1;
            T[x].s1=T[x].t;
            T[x].s2=T[x].t^1;
            return;
        }
        int z=ls+rs>>1;
        if(q<=z) add(T[x].l,ls,z,q);
        else add(T[x].r,z+1,rs,q);
        pushup(x);
    }
    int sum1(int x,int ls,int rs,int l,int r)
    {
        if(x==0) return 0;
        if(ls>=l&&rs<=r)
        {
            return T[x].s1;
        }
        int z=ls+rs>>1,s=0;
        if(l<=z) s+=sum1(T[x].l,ls,z,l,r);
        if(r>z) s+=sum1(T[x].r,z+1,rs,l,r);
        return s;
    }
    int sum2(int x,int ls,int rs,int l,int r)
    {
        if(x==0) return 0;
        if(ls>=l&&rs<=r)
        {
            return T[x].s2;
        }
        int z=ls+rs>>1,s=0;
        if(l<=z) s+=sum2(T[x].l,ls,z,l,r);
        if(r>z) s+=sum2(T[x].r,z+1,rs,l,r);
        return s;
    }
    int merge(int x1,int x2,int ls,int rs)
    {
        if(x1==0) return x2;
        if(x2==0) return x1;
        if(ls==rs)
        {
            T[x1].t=T[x1].t^T[x2].t;
            T[x1].s1=T[x1].t;
            T[x1].s2=T[x1].t^1;
            return x1;
        }
        int z=ls+rs>>1;
        T[x1].l=merge(T[x1].l,T[x2].l,ls,z);
        T[x1].r=merge(T[x1].r,T[x2].r,z+1,rs);
        pushup(x1);
        return x1;
    }
}
void dfs(int x)
{
    T[x].b=T[x].c=++tot;
    S.push(x);
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(T[a[i].m].b==0)
        {
            dfs(a[i].m);
            T[x].c=min(T[x].c,T[a[i].m].c);
            if(T[a[i].m].c==T[x].b)
            {
                ++q;
                while(S.top()!=a[i].m)
                {
                    road2(q,S.top());
                    road2(S.top(),q);
                    S.pop();
                }
                road2(q,S.top());
                road2(S.top(),q);
                S.pop();
                road2(q,x);
                road2(x,q);
            }
        }
        T[x].c=min(T[x].c,T[a[i].m].b);
    }
}
void dfs2(int x,int fa)
{
    if(x<=n) Segment_tree::add(rt[x],1,1e6,b[x]);
    for(int i=t2[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa) continue;
        dfs2(a[i].m,x);
        rt[x]=Segment_tree::merge(rt[x],rt[a[i].m],1,1e6);
    }
    for(auto i:c[x])
    {
        if(i.u==1) d[i.t]=Segment_tree::sum1(rt[x],1,1e6,1,i.x);
        else d[i.t]=Segment_tree::sum2(rt[x],1,1e6,1,i.x);
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&b[i]);
    }
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        road(x,y);
        road(y,x);
    }
    scanf("%d",&m);
    for(int i=1;i<=m;++i)
    {
        int x,y,u;
        scanf("%d%d%d",&u,&x,&y);
        c[x].push_back(query(y,u,i));
    }
    q=n;
    dfs(1);
    dfs2(1,0);
    for(int i=1;i<=m;++i)
    {
        printf("%d\n",d[i]);
    }
    return 0;
}