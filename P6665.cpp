#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=1000001;
int n,m,tot,rt[N],f[N];
bool h[N];
vector<int> a[N];
struct tree
{
    int l,r,s,k;
}T[N<<4];
void pushup(int x)
{
    T[x].s=T[T[x].l].s+T[T[x].r].s;
}
void pushdown(int x,int t)
{
    if(T[x].k==0) return;
    if(T[x].k&(1<<t)) swap(T[x].l,T[x].r);
    if(T[x].l) T[T[x].l].k^=T[x].k;
    if(T[x].r) T[T[x].r].k^=T[x].k;
    T[x].k=0;
}
void add(int &x,int t,int q)
{
    if(x==0)
    {
        x=++tot;
        T[x].l=T[x].r=T[x].s=T[x].k=0;
    }
    if(t==-1)
    {
        T[x].s=1;
        return;
    }
    pushdown(x,t);
    if((q&(1<<t))==0) add(T[x].l,t-1,q);
    else add(T[x].r,t-1,q);
    pushup(x);
}
int sum(int x,int t)
{
    if(t==-1) return 0;
    pushdown(x,t);
    if(T[T[x].l].s<(1<<t)) return sum(T[x].l,t-1);
    else return sum(T[x].r,t-1)+(1<<t);
}
int merge(int x1,int x2,int t)
{
    if(x1==0||x2==0) return x1+x2;
    if(t==-1)
    {
        T[x1].s|=T[x2].s;
        return x1;
    }
    pushdown(x1,t);
    pushdown(x2,t);
    T[x1].l=merge(T[x1].l,T[x2].l,t-1);
    T[x1].r=merge(T[x1].r,T[x2].r,t-1);
    pushup(x1);
    return x1;
}
void dfs(int x,int fa)
{
    h[x]=true;
    int u=0;
    for(auto i:a[x])
    {
        if(i==fa) continue;
        dfs(i,x);
        u^=f[i];
    }
    add(rt[x],20,u);
    for(auto i:a[x])
    {
        if(i==fa) continue;
        if(rt[i]) T[rt[i]].k^=u^f[i];
        rt[x]=merge(rt[x],rt[i],20);
    }
    f[x]=sum(rt[x],20);
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;++i) a[i].clear(),rt[i]=h[i]=0;
        for(int i=1;i<=m;++i)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            a[x].push_back(y);
            a[y].push_back(x);
        }
        tot=0;
        int s=0;
        for(int i=1;i<=n;++i)
        {
            if(!h[i])
            {
                dfs(i,0);
                s^=f[i];
            }
        }
        if(s) printf("Alice\n");
        else printf("Bob\n");
    }
    return 0;
}