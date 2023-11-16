#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,p=1,q,q2,tot,t[N],f[N];
bool g[N];
struct road
{
    int m,q;
}a[N<<1];
struct tree
{
    int b,c;
}T[N];
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
void dfs(int x,int fa,int r)
{
    T[x].b=T[x].c=++tot;
    int u=0;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa) continue;
        if(T[a[i].m].b==0)
        {
            dfs(a[i].m,x,r);
            T[x].c=min(T[x].c,T[a[i].m].c);
            ++u;
            if(T[a[i].m].c>=T[x].b&&x!=r) g[x]=true;
        }
        T[x].c=min(T[x].c,T[a[i].m].b);
    }
    if(x==r&&u>=2) g[x]=true;
}
void dfs2(int x,int r)
{
    ++q;
    f[x]=r;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(g[a[i].m]&&f[a[i].m]!=r)
        {
            f[a[i].m]=r;
            ++q2;
        }
        if(f[a[i].m]) continue;
        dfs2(a[i].m,r);
    }
}
int main()
{
    int z=0;
    while(scanf("%d",&m),m!=0)
    {
        ++z;
        for(int i=1;i<=n;++i) f[i]=g[i]=t[i]=T[i].b=T[i].c=0;
        p=1;
        tot=0;
        n=0;
        for(int i=1;i<=m;++i)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            road(x,y);
            road(y,x);
            n=max(n,max(x,y));
        }
        dfs(1,0,1);
        int s=0;
        ll w=1;
        for(int i=1;i<=n;++i)
        {
            if(!f[i]&&!g[i])
            {
                q=q2=0;
                dfs2(i,i);
                if(q2==1) ++s,w*=q;
                else if(q2==0) s+=2,w*=(ll)q*(q-1)/2;
            }
        }
        printf("Case %d: %d %lld\n",z,s,w);
    }
    return 0;
}