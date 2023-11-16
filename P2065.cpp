#include<cstdio>
#include<algorithm>
#include<queue>
#include<cmath>
using namespace std;
int N,n1,n2,q=0,p=1,s1,s2,t[10001],t0[10001],f[10001],g[10001],d[10000001];
bool u=true;
struct str
{
    int m,q,r;
}a[1000001];
int gcd(int a,int b)
{
    if(b==0) return a;
    return gcd(b,a%b);
}
void road(int x,int y,int r)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].r=r;
}
void bfs()
{
    queue<int> Q;
    Q.push(s2);
    f[s2]=1;
    g[1]=1;
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        for(int i=t[k];i!=0;i=a[i].q)
        {
            if(f[a[i].m]==0)
            {
                f[a[i].m]=f[k]+1;
                ++g[f[a[i].m]];
                Q.push(a[i].m);
            }
        }
    }
}
int dfs(int x,int r)
{
    if(x==s2) return r;
    int s=0;
    for(int i=t0[x];i!=0;i=a[i].q)
    {
        t0[x]=i;
        if(f[x]==f[a[i].m]+1&&a[i].r!=0)
        {
            int z=dfs(a[i].m,min(r,a[i].r));
            if(z!=0)
            {
                a[i].r-=z;
                a[i^1].r+=z;
                r-=z;
                s+=z;
            }
            if(r==0) return s;
        }
    }
    --g[f[x]];
    if(g[f[x]]==0) u=false;
    ++f[x];
    ++g[f[x]];
    return s;
}
void ss1(int k,int x)
{
    for(int i=2;i<=sqrt(x)&&x!=1;++i)
    {
        if(x%i==0)
        {
            if(d[i]==0) d[i]=++q;
            road(k,n1+n2+d[i],1);
            road(n1+n2+d[i],k,0);
        }
        while(x%i==0) x/=i;
    }
    if(x>1)
    {
        if(d[x]==0) d[x]=++q;
        road(k,n1+n2+d[x],1);
        road(n1+n2+d[x],k,0);
    }
}
void ss2(int k,int x)
{
    for(int i=2;i<=sqrt(x)&&x!=1;++i)
    {
        if(x%i==0)
        {
            if(d[i]==0) d[i]=++q;
            road(n1+n2+d[i],k,1);
            road(k,n1+n2+d[i],0);
        }
        while(x%i==0) x/=i;
    }
    if(x>1)
    {
        if(d[x]==0) d[x]=++q;
        road(n1+n2+d[x],k,1);
        road(k,n1+n2+d[x],0);
    }
}
void abc()
{
    scanf("%d%d",&n1,&n2);
    p=1;
    for(int i=1;i<=N;++i) f[i]=g[i]=t[i]=0;
    u=true;
    for(int i=1;i<=n1;++i)
    {
        int x;
        scanf("%d",&x);
        ss1(i,x);
    }
    for(int i=1;i<=n2;++i)
    {
        int x;
        scanf("%d",&x);
        ss2(n1+i,x);
    }
    N=n1+n2+q+2;
    s1=N-1;
    s2=N;
    for(int i=1;i<=n1;++i)
    {
        road(s1,i,1);
        road(i,s1,0);
    }
    for(int i=1;i<=n2;++i)
    {
        road(n1+i,s2,1);
        road(s2,n1+i,0);
    }
    bfs();
    int r=0;
    while(u==true)
    {
        for(int i=1;i<=N;++i) t0[i]=t[i];
        r+=dfs(s1,1e18);
    }
    printf("%d\n",r);
    return;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--) abc();
    return 0;
}
