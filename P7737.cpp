#include<cstdio>
#include<algorithm>
#include<vector>
#include<stack>
#include<queue>
using namespace std;
const int N=1000001;
int n,m,q,k,rt,r[N],f[N];
vector<int> a[N];
namespace build
{
    int w,l[N],tot;
    bool h[N];
    struct tree
    {
        int b,c;
    }T[N];
    vector<int> a2[N];
    stack<int> S;
    void dfs(int x)
    {
        T[x].b=T[x].c=++tot;
        S.push(x);
        for(auto i:a[x])
        {
            if(T[i].b==0)
            {
                dfs(i);
                T[x].c=min(T[x].c,T[i].c);
            }
            if(h[i]==false) T[x].c=min(T[x].c,T[i].c);
        }
        if(T[x].b==T[x].c)
        {
            ++w;
            while(true)
            {
                ++f[w];
                r[S.top()]=w;
                h[S.top()]=true;
                if(S.top()==x)
                {
                    S.pop();
                    break;
                }
                S.pop();
            }
        }
    }
    void tpsort()
    {
        for(int i=1;i<=n;++i)
        {
            for(auto j:a[i])
            {
                if(r[i]!=r[j])
                {
                    a2[r[i]].push_back(r[j]);
                    ++l[r[j]];
                }
            }
        }
        for(int i=1;i<=n;++i) a[i].clear();
        queue<int> Q;
        for(int i=1;i<=w;++i)
        {
            if(l[i]==0) Q.push(i),rt=i;
        }
        while(!Q.empty())
        {
            int k=Q.front();
            Q.pop();
            for(auto i:a2[k])
            {
                --l[i];
                if(l[i]==0)
                {
                    a[k].push_back(i);
                    Q.push(i);
                }
            }
        }
    }
}
struct tree
{
    int f,s,d,t,z;
}T[N];
void dfs1(int x)
{
    T[x].s=1;
    T[x].d=T[T[x].f].d+1;
    f[x]+=f[T[x].f];
    for(auto i:a[x])
    {
        T[i].f=x;
        dfs1(i);
        T[x].s+=T[i].s;
        if(T[i].s>T[T[x].z].s) T[x].z=i;
    }
}
void dfs2(int x,int k)
{
    T[x].t=k;
    if(T[x].z) dfs2(T[x].z,k);
    for(auto i:a[x])
    {
        if(i==T[x].z) continue;
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
int dmin(int x,int y)
{
    return T[x].d<T[y].d?x:y;
}
int main()
{
    scanf("%d%d%d%d",&n,&m,&q,&k);
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        a[x].push_back(y);
    }
    for(int i=1;i<=n;++i)
    {
        if(build::T[i].b==0) build::dfs(i);
    }
    build::tpsort();
    n=build::w;
    dfs1(rt);
    dfs2(rt,rt);
    for(int i=1;i<=q;++i)
    {
        int x[3],y[3],t[3]={0,0,0};
        bool hx[3]={1,0,0},hy[3]={1,0,0};
        scanf("%d%d",&x[0],&y[0]);
        x[0]=r[x[0]],y[0]=r[y[0]],t[0]=y[0];
        if(k>=1)
        {
            scanf("%d%d",&y[1],&x[1]);
            x[1]=r[x[1]],y[1]=r[y[1]],t[1]=y[1];
            if(LCA(x[0],y[1])==x[0]) hx[1]=true;
            if(LCA(y[0],x[1])==x[1]) hy[1]=true;
        }
        if(k>=2)
        {
            scanf("%d%d",&y[2],&x[2]);
            x[2]=r[x[2]],y[2]=r[y[2]],t[2]=y[2];
            if(LCA(x[0],y[2])==x[0]) hx[2]=true;
            if(LCA(y[0],x[2])==x[2]) hy[2]=true;
            if(hx[1]&&!hx[2]&&LCA(x[1],y[2])==x[1]) hx[2]=true;
            if(hx[2]&&!hx[1]&&LCA(x[2],y[1])==x[2]) hx[1]=true;
            if(hy[1]&&!hy[2]&&LCA(x[2],y[1])==x[2]) hy[2]=true;
            if(hy[2]&&!hy[1]&&LCA(x[1],y[2])==x[1]) hy[1]=true;
        }
        for(int i=0;i<=2;++i)
        {
            for(int j=0;j<=2;++j)
            {
                if(hx[i]&&hy[j]&&LCA(x[i],y[j])==x[i]) t[j]=dmin(t[j],T[x[i]].f);
            }
        }
        for(int i=0;i<=2;++i)
        {
            for(int j=i+1;j<=2;++j)
            {
                if(!hy[i]||!hy[j]) continue;
                int z=LCA(y[i],y[j]);
                if(T[z].d>max(T[t[i]].d,T[t[j]].d)) t[i]=z;
            }
        }
        int s=0;
        for(int i=0;i<=2;++i)
        {
            if(hy[i]) s+=f[y[i]]-f[t[i]];
        }
        printf("%d\n",s);
    }
    return 0;
}