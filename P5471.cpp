#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
#include<set>
using namespace std;
const int N=200001;
int n,m,tot,k1,k2,f[N];
bool h[N];
struct node
{
    int x,t;
    node(){}
    node(int x,int t):x(x),t(t){}
    friend bool operator<(node a,node b)
    {
        return a.x<b.x;
    }
};
struct squ
{
    int x1,x2,y1,y2,w;
    squ(){}
    squ(int x1,int x2,int y1,int y2,int w):x1(x1),x2(x2),y1(y1),y2(y2),w(w){}
    friend bool operator<(squ a,squ b)
    {
        return a.w>b.w;
    }
};
vector<squ> b[N];
priority_queue<squ> Q;
struct tree
{
    int l,r;
    multiset<node> s;
}T[N<<2];
void build(int x,int l,int r)
{
    T[x].l=l;
    T[x].r=r;
    if(l==r) return;
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
}
void add(int x,int q,int q2,int k)
{
    T[x].s.insert(node(q2,k));
    if(T[x].l==T[x].r) return;
    int z=T[x].l+T[x].r>>1;
    if(q<=z) add(x<<1,q,q2,k);
    else add(x<<1|1,q,q2,k);
}
void sum(int x,int l,int r,int l2,int r2,int k)
{
    if(T[x].l>=l&&T[x].r<=r)
    {
        set<node>::iterator p=lower_bound(T[x].s.begin(),T[x].s.end(),node(l2,0));
        while(p!=T[x].s.end()&&(*p).x<=r2)
        {
            if(!h[(*p).t])
            {
                f[(*p).t]=k;
                for(auto j:b[(*p).t]) j.w+=k,Q.push(j);
                h[(*p).t]=true;
            }
            ++p;
            T[x].s.erase(prev(p));
        }
        return;
    }
    int z=T[x].l+T[x].r>>1;
    if(l<=z) sum(x<<1,l,r,l2,r2,k);
    if(r>z) sum(x<<1|1,l,r,l2,r2,k);
}
int main()
{
    scanf("%d%d%d%d",&n,&m,&k1,&k2);
    tot=n;
    build(1,1,k1);
    for(int i=1;i<=n;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        add(1,x,y,i);
    }
    for(int i=1;i<=m;++i)
    {
        int k,w,x1,x2,y1,y2;
        scanf("%d%d%d%d%d%d",&k,&w,&x1,&x2,&y1,&y2);
        b[k].push_back(squ(x1,x2,y1,y2,w));
    }
    f[1]=0;
    h[1]=true;
    for(auto i:b[1]) Q.push(i);
    while(!Q.empty())
    {
        squ k=Q.top();
        Q.pop();
        sum(1,k.x1,k.x2,k.y1,k.y2,k.w);
    }
    for(int i=2;i<=n;++i)
    {
        printf("%d\n",f[i]);
    }
    return 0;
}