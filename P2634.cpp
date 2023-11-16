#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
const int N=20001,M=3;
int n,q,t[N],p=1,r,h1[M+1],h2[M+1];
ll s=0;
bool g[N];
struct tree
{
    int s,ms,d;
}T[N];
struct road
{
    int m,q,w;
}a[N<<1];
ll gcd(ll a,ll b)
{
    if(b==0) return a;
    return gcd(b,a%b);
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
    ++h1[T[x].d%3];
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa||g[a[i].m]) continue;
        T[a[i].m].d=(T[x].d+a[i].w)%3;
        dfs2(a[i].m,x);
    }
}
void sum(int x)
{
    h2[0]=1;
    h2[1]=h2[2]=0;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(g[a[i].m]) continue;
        T[a[i].m].d=a[i].w%3;
        dfs2(a[i].m,x);
        s+=(ll)h1[0]*h2[0]+(ll)h1[1]*h2[2]+(ll)h1[2]*h2[1];
        h2[0]+=h1[0];
        h2[1]+=h1[1];
        h2[2]+=h1[2];
        h1[0]=h1[1]=h1[2]=0;
    }
}
void dfs(int x)
{
    r=0;
    q=T[x].s;
    dfs1(x,0);
    sum(r);
    g[r]=true;
    for(int i=t[r];i!=0;i=a[i].q)
    {
        if(g[a[i].m]) continue;
        dfs(a[i].m);
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n-1;++i)
    {
        int x,y,w;
        scanf("%d%d%d",&x,&y,&w);
        road(x,y,w);
        road(y,x,w);
    }
    T[1].s=n;
    T[0].ms=1e9;
    dfs(1);
    s=s*2+n;
    ll y=n*n,z=gcd(s,y);
    printf("%lld/%lld",s/z,y/z);
    return 0;
}