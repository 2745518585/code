#include<cstdio>
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}
const int N=200001,M=31;
int n,m,q,u,t[N],b[N],p=1,r,tot,z1[N],z2[N];
bool g[N];
struct tree
{
    int s,ms,k,f[M],d[M];
}T[N];
struct Queue
{
    priority_queue<int> Q1,Q2;
}Q,Q1[N],Q2[N];
struct road
{
    int m,q,w;
}a[N<<1];
void add(Queue &Q,int x,int k)
{
    if(k==1) Q.Q1.push(x);
    else Q.Q2.push(x);
    while(Q.Q2.size()>1&&Q.Q1.top()==Q.Q2.top()) Q.Q1.pop(),Q.Q2.pop();
}
int sum(Queue &Q)
{
    while(Q.Q2.size()>1&&Q.Q1.top()==Q.Q2.top()) Q.Q1.pop(),Q.Q2.pop();
    return Q.Q1.top();
}
int sum2(Queue &Q)
{
    while(Q.Q2.size()>1&&Q.Q1.top()==Q.Q2.top()) Q.Q1.pop(),Q.Q2.pop();
    int x=Q.Q1.top();
    Q.Q1.pop();
    while(Q.Q2.size()>1&&Q.Q1.top()==Q.Q2.top()) Q.Q1.pop(),Q.Q2.pop();
    int z=Q.Q1.top();
    Q.Q1.push(x);
    return x+z;
}
void road(int x,int y,int w)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].w=w;
}
void dfs1(int x,int fa)
{
    ++T[x].k;
    T[x].s=1;
    T[x].ms=0;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa||g[a[i].m]) continue;
        dfs1(a[i].m,x);
        T[x].s+=T[a[i].m].s;
        T[x].ms=max(T[x].ms,T[a[i].m].s);
    }
    T[x].ms=max(T[x].ms,q-T[x].s);
    if(T[x].ms<T[r].ms) r=x;
}
void dfs2(int x,int fa)
{
    if(T[x].k>1) add(Q2[r],T[x].d[T[x].k-1],1);
    T[x].f[T[x].k]=r;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa||g[a[i].m]) continue;
        T[a[i].m].d[T[x].k]=T[x].d[T[x].k]+a[i].w;
        dfs2(a[i].m,x);
    }
}
void dfs(int x)
{
    r=0;
    q=T[x].s;
    dfs1(x,0);
    T[r].d[T[r].k]=0;
    dfs2(r,0);
    g[r]=true;
    for(int i=t[r];i!=0;i=a[i].q)
    {
        if(g[a[i].m]) continue;
        dfs(a[i].m);
    }
}
void check(int x)
{
    if(b[x]==0)
    {
        for(int i=1;i<=T[x].k;++i)
        {
            z1[i]=sum2(Q1[T[x].f[i]]);
            if(i<T[x].k) z2[i]=sum(Q2[T[x].f[i+1]]);
            else add(Q1[T[x].f[i]],0,-1);
            if(i>1) add(Q2[T[x].f[i]],T[x].d[i-1],-1);
        }
        for(int i=1;i<=T[x].k;++i)
        {
            if(i<T[x].k&&sum(Q2[T[x].f[i+1]])!=z2[i])
            {
                add(Q1[T[x].f[i]],z2[i],-1);
                add(Q1[T[x].f[i]],sum(Q2[T[x].f[i+1]]),1);
            }
            if(sum2(Q1[T[x].f[i]])!=z1[i])
            {
                add(Q,z1[i],-1);
                add(Q,sum2(Q1[T[x].f[i]]),1);
            }
        }
        b[x]=1;
        --u;
    }
    else if(b[x]==1)
    {
        for(int i=T[x].k;i>=1;--i)
        {
            z1[i]=sum2(Q1[T[x].f[i]]);
            if(i<T[x].k) z2[i]=sum(Q2[T[x].f[i+1]]);
        }
        for(int i=T[x].k;i>=1;--i)
        {
            if(i>1) add(Q2[T[x].f[i]],T[x].d[i-1],1);
            if(i<T[x].k) 
            {
                if(sum(Q2[T[x].f[i+1]])!=z2[i])
                {
                    add(Q1[T[x].f[i]],z2[i],-1);
                    add(Q1[T[x].f[i]],sum(Q2[T[x].f[i+1]]),1);
                }
            }
            else add(Q1[T[x].f[i]],0,1);
            if(sum2(Q1[T[x].f[i]])!=z1[i])
            {
                add(Q,z1[i],-1);
                add(Q,sum2(Q1[T[x].f[i]]),1);
            }
        }
        b[x]=0;
        ++u;
    }
}
int main()
{
    u=n=read();
    for(int i=1;i<=n;++i) add(Q1[i],-1e9,1),add(Q1[i],-1e9,-1),add(Q2[i],-1e9,1),add(Q2[i],-1e9,-1);
    add(Q,-1e9,1),add(Q,-1e9,-1);
    for(int i=1;i<=n-1;++i)
    {
        int x=read(),y=read(),w=read();
        road(x,y,w);
        road(y,x,w);
    }
    T[1].s=n;
    T[0].ms=1e9;
    dfs(1);
    for(int i=1;i<=n;++i)
    {
        add(Q1[i],0,1);
        if(T[i].k>1) add(Q1[T[i].f[T[i].k-1]],sum(Q2[i]),1);
    }
    for(int i=1;i<=n;++i) add(Q,sum2(Q1[i]),1);
    m=read();
    for(int i=1;i<=m;++i)
    {
        char z[10];
        scanf("%s",z);
        if(z[0]=='A')
        {
            if(u==0) printf("They have disappeared.\n");
            else printf("%d\n",max(sum(Q),0));
        }
        else if(z[0]=='C') check(read());
    }
    return 0;
}