#include<cstdio>  ///
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000001,M=31;
int n,m,k,q,o,tot,d[N],e[N],g[N][M],rt[N];
vector<int> a[N],a2[N],c[N],f1[N],f2[N],h[N],h2[N];
ll s;
struct str
{
    int x,y,z;
}b[N];
struct tree
{
    int f,s,d,t,z,b,bm;
}T[N];
namespace TC
{
    void dfs1(int x)
    {
        T[x].s=1;
        T[x].d=T[T[x].f].d+1;
        for(auto i:a[x])
        {
            if(i==T[x].f) continue;
            T[i].f=x;
            dfs1(i);
            T[x].s+=T[i].s;
            if(T[i].s>T[T[x].z].s) T[x].z=i;
        }
    }
    void dfs2(int x,int k)
    {
        T[x].b=++tot;
        T[x].t=k;
        if(T[x].z) dfs2(T[x].z,k);
        for(auto i:a[x])
        {
            if(i==T[x].f||i==T[x].z) continue;
            dfs2(i,i);
        }
        T[x].bm=tot;
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
int find(int x,int k)
{
    int t=0,p=T[x].d-k;
    while(t>=0)
    {
        if(T[g[x][t]].d>=p) x=g[x][t],++t;
        else --t;
    }
    return x;
}
namespace sgt1
{
    ll T[N];
    void add(int x,ll k)
    {
        while(x<=n) T[x]+=k,x+=x&-x;
    }
    ll sum(int x)
    {
        ll s=0;
        while(x>=1) s+=T[x],x-=x&-x;
        return s;
    }
}
void dfs1(int x)
{
    for(auto i:f1[x])
    {
        sgt1::add(T[b[i].z].d,1);
    }
    for(auto i:f2[x])
    {
        s+=sgt1::sum(n)-sgt1::sum(T[b[i].z].d);
    }
    for(auto i:a[x])
    {
        if(i==T[x].f) continue;
        dfs1(i);
    }
    for(auto i:f1[x])
    {
        sgt1::add(T[b[i].z].d,-1);
    }
}
bool cmp(int x,int y)
{
    return T[x].b<T[y].b;
}
namespace sgt
{
    int tot;
    struct tree
    {
        int l,r,s;
    }T[N<<4];
    void pushup(int x)
    {
        T[x].s=T[T[x].l].s+T[T[x].r].s;
    }
    void add(int &x,int ls,int rs,int q,int k)
    {
        if(x==0) x=++tot;
        if(ls==rs)
        {
            T[x].s+=k;
            return;
        }
        int z=ls+rs>>1;
        if(q<=z) add(T[x].l,ls,z,q,k);
        else add(T[x].r,z+1,rs,q,k);
        pushup(x);
    }
    int sum(int x,int ls,int rs,int l,int r)
    {
        if(ls>=l&&rs<=r) return T[x].s;
        int z=ls+rs>>1,s=0;
        if(l<=z) s+=sum(T[x].l,ls,z,l,r);
        if(r>z) s+=sum(T[x].r,z+1,rs,l,r);
        return s;
    }
}
void dfs2(int x)
{
    e[x]=1;
    h[x].clear();
    h2[x].clear();
    rt[x]=0;
    for(auto i:a2[x])
    {
        dfs2(i);
        e[x]+=e[i];
    }
}
void dfs3(int x)
{
    int z=0;
    for(auto i:a2[x])
    {
        if(e[i]>e[z]) z=i;
    }
    if(z)
    {
        dfs3(z);
        rt[x]=rt[z];
        swap(h[x],h[z]);
    }
    for(auto i:h2[x])
    {
        if(x==o) continue;
        int p=0;
        if(T[x].d-T[o].d>=k) p=o;
        else if(T[i].d+T[x].d-T[o].d*2>=k) p=find(i,(T[i].d+T[x].d-T[o].d*2)-k);
        else continue;
        s+=sgt::sum(rt[x],1,n,T[p].b,T[p].bm);
        h[x].push_back(i);
        sgt::add(rt[x],1,n,T[i].b,1);
    }
    for(auto i:a2[x])
    {
        if(i==z) continue;
        dfs3(i);
        for(auto j:h[i])
        {
            int p=o;
            if(T[x].d-T[o].d>=k) p=o;
            else if(T[j].d+T[x].d-T[o].d*2>=k) p=find(j,(T[j].d+T[x].d-T[o].d*2)-k);
            else continue;
            s+=sgt::sum(rt[x],1,n,T[p].b,T[p].bm);
        }
        for(auto j:h[i])
        {
            h[x].push_back(j);
            sgt::add(rt[x],1,n,T[j].b,1);
        }
    }
}
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n-1;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        a[x].push_back(y);
        a[y].push_back(x);
    }
    TC::dfs1(1);
    TC::dfs2(1,1);
    for(int i=1;i<=m;++i)
    {
        scanf("%d%d",&b[i].x,&b[i].y);
        b[i].z=LCA(b[i].x,b[i].y);
        c[b[i].z].push_back(i);
    }
    for(int i=1;i<=n;++i) g[i][0]=T[i].f;
    for(int i=1;i<=20;++i)
    {
        for(int j=1;j<=n;++j)
        {
            g[j][i]=g[g[j][i-1]][i-1];
        }
    }
    for(int i=1;i<=m;++i)
    {
        if(T[b[i].x].d>=T[b[i].z].d+k)
        {
            int z=find(b[i].x,T[b[i].x].d-T[b[i].z].d-k);
            f1[z].push_back(i);
            f2[b[i].x].push_back(i);
        }
        if(T[b[i].y].d>=T[b[i].z].d+k)
        {
            int z=find(b[i].y,T[b[i].y].d-T[b[i].z].d-k);
            f1[z].push_back(i);
            f2[b[i].y].push_back(i);
        }
    }
    dfs1(1);
    ll w=s;
    s=0;
    for(int i=1;i<=n;++i)
    {
        d[q=1]=i;
        rt[0]=0;
        for(auto j:c[i])
        {
            if(b[j].x==i||b[j].y==i)
            {
                int z=b[j].x+b[j].y-i;
                if(T[z].d-T[i].d>=k)
                {
                    int p=find(z,(T[z].d-T[i].d)-k);
                    w+=sgt::sum(rt[0],1,n,T[p].b,T[p].bm);
                    sgt::add(rt[0],1,n,T[p].b,1);
                }
            }
        }
        for(auto j:c[i])
        {
            if(b[j].x==i||b[j].y==i) continue;
            if(T[b[j].x].d-T[i].d>=k)
            {
                int p=find(b[j].x,(T[b[j].x].d-T[i].d)-k);
                w+=sgt::sum(rt[0],1,n,T[p].b,T[p].bm);
            }
            if(T[b[j].y].d-T[i].d>=k)
            {
                int p=find(b[j].y,(T[b[j].y].d-T[i].d)-k);
                w+=sgt::sum(rt[0],1,n,T[p].b,T[p].bm);
            }
            d[++q]=b[j].x;
            d[++q]=b[j].y;
        }
        sort(d+1,d+q+1,cmp);
        q=unique(d+1,d+q+1)-d-1;
        static int S[N],Top;
        S[Top=1]=i;
        a2[i].clear();
        for(int j=2;j<=q;++j)
        {
            int z=LCA(d[j],S[Top]);
            while(Top>=1&&T[z].d<=T[S[Top-1]].d)
            {
                a2[S[Top-1]].push_back(S[Top]);
                --Top;
                z=LCA(d[j],S[Top]);
            }
            a2[d[j]].clear();
            if(z!=S[Top])
            {
                a2[z].clear();
                a2[z].push_back(S[Top]);
                S[Top]=z;
            }
            S[++Top]=d[j];
        }
        while(Top>=2)
        {
            a2[S[Top-1]].push_back(S[Top]);
            --Top;
        }
        o=i;
        dfs2(i);
        for(auto j:c[i])
        {
            if(b[j].x==i||b[j].y==i) continue;
            h2[b[j].x].push_back(b[j].y);
            h2[b[j].y].push_back(b[j].x);
        }
        dfs3(i);
    }
    printf("%lld\n",w+s/2);
    return 0;
}