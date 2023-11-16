#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=2000001;
int n,m,p=1,t[N],f[N],fx[N],g[N],fa[N],ga[N];
bool h1[N],h2[N];
vector<int> c[N];
struct road
{
    int m,q;
}a[N<<1];
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
void check(int x,int y)
{
    while(y!=x)
    {
        h2[ga[y]]=h2[ga[y]^1]=true;
        y=fa[y];
    }
}
void solve1(int x,int y,int p)
{
    int n=0;
    static int b[N];
    b[++n]=x;
    c[x].push_back(x);
    while(y!=x)
    {
        b[++n]=y;
        c[x].push_back(y);
        y=fa[y];
    }
    for(int i=2;i<=n;++i)
    {
        fx[p]=max(fx[p],f[b[i]]+min(i-1,n-i+1));
    }
    fx[p^1]=fx[p];
    f[x]=max(f[x],fx[p]);
}
void dfs1(int x)
{
    h1[x]=true;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa[x]) continue;
        if(h1[a[i].m])
        {
            if(h2[i]==false)
            {
                h2[i]=h2[i^1]=true;
                check(a[i].m,x);
            }
            else solve1(x,a[i].m,i);
            continue;
        }
        fa[a[i].m]=x;
        ga[a[i].m]=i;
        dfs1(a[i].m);
        if(h2[i]==false) f[x]=max(f[x],f[a[i].m]+1);
    }
}
void solve2(int x)
{
    static int b[N],Q[N],f2[N];
    int n=c[x].size();
    for(int i=1;i<=n;++i) b[i]=b[n+i]=c[x][i-1],f2[i]=f2[n+i]=f[b[i]];
    f2[1]=g[x];
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(h1[a[i].m]) continue;
        if(h2[i]==false) f2[1]=max(f2[1],f[a[i].m]+1);
    }
    f2[n+1]=f2[1];
    int T=1,R=0;
    for(int i=1;i<=n*2;++i)
    {
        while(T<=R&&i-Q[T]>n/2) ++T;
        if(b[i]!=x) g[b[i]]=max(g[b[i]],f2[Q[T]]+i-Q[T]);
        while(T<=R&&f2[Q[R]]-Q[R]<=f2[i]-i) --R;
        Q[++R]=i;
    }
    T=1,R=0;
    for(int i=n*2;i>=1;--i)
    {
        while(T<=R&&Q[T]-i>n/2) ++T;
        if(b[i]!=x) g[b[i]]=max(g[b[i]],f2[Q[T]]+Q[T]-i);
        while(T<=R&&f2[Q[R]]+Q[R]<=f2[i]+i) --R;
        Q[++R]=i;
    }
}
void dfs2(int x)
{
    h1[x]=true;
    if(c[x].size()!=0) solve2(x);
    int s1=g[x],s2=0;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(h1[a[i].m]) continue;
        if(h2[i]==false)
        {
            if(f[a[i].m]+1>s1) s2=s1,s1=f[a[i].m]+1;
            else s2=max(s2,f[a[i].m]+1);
        }
        else
        {
            if(fx[i]>s1) s2=s1,s1=fx[i];
            else s2=max(s2,fx[i]);
        }
    }
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(h1[a[i].m]) continue;
        if(h2[i]==false)
        {
            if(f[a[i].m]+1==s1) g[a[i].m]=s2+1;
            else g[a[i].m]=s1+1;
        }
        dfs2(a[i].m);
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        road(x,y);
        road(y,x);
    }
    dfs1(1);
    for(int i=1;i<=n;++i) h1[i]=false;
    dfs2(1);
    for(int i=1;i<=n;++i)
    {
        printf("%d ",max(f[i],g[i]));
    }
    return 0;
}