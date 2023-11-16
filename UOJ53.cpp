#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
const int N=500001;
int n,m,a[N];
int dmin(int x,int y)
{
    return a[x]<a[y]?x:y;
}
namespace sgt
{
    int *b;
    struct tree
    {
        int s;
    }T[N<<2];
    void pushup(int x)
    {
        T[x].s=dmin(T[x<<1].s,T[x<<1|1].s);
    }
    void build(int x,int l,int r)
    {
        if(l==r)
        {
            T[x].s=b[l];
            return;
        }
        int z=l+r>>1;
        build(x<<1,l,z);
        build(x<<1|1,z+1,r);
        pushup(x);
    }
    int sum(int x,int ls,int rs,int l,int r)
    {
        if(ls>=l&&rs<=r)
        {
            return T[x].s;
        }
        int z=ls+rs>>1,s=0;
        if(l<=z) s=dmin(s,sum(x<<1,ls,z,l,r));
        if(r>z) s=dmin(s,sum(x<<1|1,z+1,rs,l,r));
        return s;
    }
}
namespace tc
{
    int tot,*s;
    vector<int> b[N];
    struct tree
    {
        int f,d,t,z,b,w;
    }T[N];
    void dfs1(int x)
    {
        s[x]=1;
        T[x].d=T[T[x].f].d+1;
        for(auto i:b[x])
        {
            if(i==T[x].f) continue;
            T[i].f=x;
            dfs1(i);
            s[x]+=s[i];
            if(s[i]>s[T[x].z]) T[x].z=i;
        }
    }
    void dfs2(int x,int t)
    {
        T[x].t=t;
        T[x].b=++tot;
        if(T[x].t!=x) T[x].w=dmin(x,T[T[x].f].w);
        else T[x].w=x;
        if(T[x].z) dfs2(T[x].z,t);
        for(auto i:b[x])
        {
            if(i==T[x].f||i==T[x].z) continue;
            dfs2(i,i);
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
    int find(int x,int y)
    {
        if(x==y) return 0;
        while(T[x].d<=T[y].d&&T[x].t!=T[y].t)
        {
            if(T[T[y].t].f==x) return T[y].t;
            y=T[T[y].t].f;
        }
        if(T[x].d<=T[y].d) return T[x].z;
        else return 0;
    }
    int sum(int x,int y)
    {
        int s=0;
        while(T[x].t!=T[y].t)
        {
            if(T[T[x].t].d>T[T[y].t].d)
            {
                s=dmin(s,T[x].w);
                x=T[T[x].t].f;
            }
            else
            {
                s=dmin(s,T[y].w);
                y=T[T[y].t].f;
            }
        }
        s=dmin(s,sgt::sum(1,1,n,min(T[x].b,T[y].b),max(T[x].b,T[y].b)));
        return s;
    }
}
struct line
{
    int x,y;
    line(){}
    line(int x,int y):x(x),y(y){}
}b[N][2];
struct str
{
    line k;
    int w;
    str(){}
    str(line k,int w):k(k),w(w){}
    friend bool operator<(str a,str b)
    {
        return a.w>b.w;
    }
};
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    a[0]=1e9;
    for(int i=2;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        tc::b[x].push_back(i);
    }
    tc::s=new int[n+10];
    tc::dfs1(1);
    tc::dfs2(1,1);
    delete[] tc::s;
    sgt::b=new int[n+10];
    for(int i=1;i<=n;++i) sgt::b[tc::T[i].b]=i;
    sgt::build(1,1,n);
    delete[] sgt::b;
    for(int i=1;i<=n;++i) vector<int>().swap(tc::b[i]);
    for(int i=1;i<=n;++i)
    {
        int x1,x2,x3;
        scanf("%d%d%d",&x1,&x2,&x3);
        int z=tc::LCA(tc::LCA(x1,x2),x3);
        if(tc::LCA(x1,x3)!=z) swap(x2,x3);
        if(tc::LCA(x2,x3)!=z) swap(x1,x3);
        int z2=tc::LCA(x1,x2),p2=tc::find(z2,x2);
        b[i][0]=line(x1,x3);
        if(p2) b[i][1]=line(p2,x2);
        else b[i][1]=line(0,0);
    }
    priority_queue<str> Q;
    auto add=[&](int x,int w)
    {
        if(b[x][0].x)
        {
            int z=tc::sum(b[x][0].x,b[x][0].y);
            Q.push(str(b[x][0],w+a[z]));
        }
        if(b[x][1].x)
        {
            int z=tc::sum(b[x][1].x,b[x][1].y);
            Q.push(str(b[x][1],w+a[z]));
        }
    };
    for(int i=1;i<=n;++i) Q.push(str(line(i,i),a[i]));
    int p=m;
    while(true)
    {
        str k=Q.top();
        Q.pop();
        printf("%d\n",k.w);
        --p;
        if(p==0) return 0;
        int x=tc::sum(k.k.x,k.k.y);
        // printf("%d %d %d\n",k.k.x,k.k.y,x);
        if(x!=k.k.x)
        {
            int p=tc::find(x,k.k.x);
            if(p==0) p=tc::T[x].f;
            int z=tc::sum(k.k.x,p);
            Q.push(str(line(k.k.x,p),k.w-a[x]+a[z]));
        }
        if(x!=k.k.y)
        {
            // printf("%d %d\n",x,k.k.y);
            int p=tc::find(x,k.k.y);
            if(p==0) p=tc::T[x].f;
            int z=tc::sum(p,k.k.y);
            Q.push(str(line(p,k.k.y),k.w-a[x]+a[z]));
        }
        add(x,k.w);
        if(Q.size()>p*3)
        {
            queue<str> Q2;
            while(!Q.empty()) Q2.push(Q.top()),Q.pop();
            for(int i=1;i<=p;++i) Q.push(Q2.front()),Q2.pop();
        }
    }
    return 0;
}