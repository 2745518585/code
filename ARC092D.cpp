#include<bits/stdc++.h>
using namespace std;
inline char gc()
{
    static char buf[100000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
template<typename T>
inline void read(T &x)
{
    T u=1,t=0;char c=gc();
    while(c<'0'||c>'9') {if(c=='-') u=-1; c=gc();}
    while(c>='0'&&c<='9') t*=10,t+=c-'0',c=gc();
    x=u*t;return;
}
const int N=1000001,M=2001;
int n,m,q,tot,p=0,t[N],r[N],b[N];
bool h[N],g[N];
struct road
{
    int m,q;
}a[N<<1];
struct tree
{
    int b,c;
}T[N];
stack<int> S;
bitset<M> f[M];
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
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
        }
        else if(h[a[i].m]==false)
        {
            T[x].c=min(T[x].c,T[a[i].m].c);
        }
    }
    if(T[x].b==T[x].c)
    {
        ++q;
        while(S.top()!=x)
        {
            h[S.top()]=true;
            r[S.top()]=q;
            S.pop();
        }
        h[x]=true;
        r[x]=q;
        S.pop();
    }
}
void check(bitset<M> &x,int p)
{
    bitset<M> y=x;
    for(int i=t[p];i!=0;i=a[i].q) x[a[i].m]=1;
    while((x^y)._Find_first()<=n)
    {
        int z=(x^y)._Find_first();
        y=x;
        x|=f[z];
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
    }
    for(int i=1;i<=n;++i)
    {
        if(T[i].b==0) dfs(i);
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=t[i];j!=0;j=a[j].q) f[i][a[j].m]=1;
    }
    for(int i=1;i<=n;++i)
    {
        int k=0;
        for(int j=t[i];j!=0;j=a[j].q) b[++k]=j;
        bitset<M> x;
        x.reset();
        x[i]=1;
        for(int j=1;j<=k;++j)
        {
            if(x[a[b[j]].m]==1) g[b[j]]=true;
            check(x,a[b[j]].m);
        }
        x.reset();
        x[i]=1;
        for(int j=k;j>=1;--j)
        {
            if(x[a[b[j]].m]==1) g[b[j]]=true;
            check(x,a[b[j]].m);
        }
    }
    printf("%d %d %d\n",g[1],g[2],g[3]);
    for(int i=1;i<=n;++i)
    {
        for(int j=t[i];j!=0;j=a[j].q)
        {
            g[j]^=(r[i]==r[a[j].m]);
        }
    }
    for(int i=1;i<=m;++i)
    {
        if(g[i]) printf("diff\n");
        else printf("same\n");
    }
    return 0;
}