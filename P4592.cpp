#include<cstdio>
#include<algorithm>
using namespace std;
const int N=500001;
int n,m,tot,tot2,p=1,t[N],b[N],c[N],a2[N<<5][2],g[N<<5],rt1[N],rt2[N];
struct tree
{
    int f,s,d,t,z,b,bm;
}T[N];
struct road
{
    int m,q;
}a[N<<1];
void add(int x,int k,int k2,int t)
{
    for(int i=30;i>=0;--i)
    {
        int z=(x&(1<<i))!=0;
        if(k2!=0) a2[k][z^1]=a2[k2][z^1];
        a2[k][z]=++tot2;
        k=a2[k][z];
        g[k]=max(g[k],t);
        if(k2!=0&&a2[k2][z]) k2=a2[k2][z];
        else k2=0;
    }
}
int find(int x,int k,int t)
{
    if(k==0) return 0;
    int s=0;
    for(int i=30;i>=0;--i)
    {
        int z=(x&(1<<i))==0;
        if(a2[k][z]!=0&&g[a2[k][z]]>=t) k=a2[k][z],s=s*2+z;
        else k=a2[k][z^1],s=s*2+(z^1);
    }
    return s;
}
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
void dfs1(int x)
{
    T[x].s=1;
    T[x].d=T[T[x].f].d+1;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==T[x].f) continue;
        T[a[i].m].f=x;
        dfs1(a[i].m);
        T[x].s+=T[a[i].m].s;
        if(T[a[i].m].s>T[T[x].z].s) T[x].z=a[i].m;
    }
}
void dfs2(int x,int k)
{
    T[x].b=++tot;
    rt1[x]=++tot2;
    add(b[x],rt1[x],rt1[T[x].f],T[x].d);
    T[x].t=k;
    if(T[x].z!=0) dfs2(T[x].z,k);
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==T[x].f||a[i].m==T[x].z) continue;
        else dfs2(a[i].m,a[i].m);
    }
    T[x].bm=tot;
}
int LCA(int x,int y)
{
    while(T[x].t!=T[y].t)
    {
        if(T[T[x].t].d>=T[T[y].t].d) x=T[T[x].t].f;
        else y=T[T[y].t].f;
    }
    if(T[x].d<T[y].d) return x;
    else return y;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&b[i]);
    }
    for(int i=1;i<=n-1;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        road(x,y);
        road(y,x);
    }
    dfs1(1);
    dfs2(1,1);
    for(int i=1;i<=n;++i) c[T[i].b]=i;
    for(int i=1;i<=n;++i)
    {
        rt2[i]=++tot2;
        add(b[c[i]],rt2[i],rt2[i-1],i);
    }
    for(int i=1;i<=m;++i)
    {
        int z;
        scanf("%d",&z);
        if(z==1)
        {
            int x,k;
            scanf("%d%d",&x,&k);
            printf("%d\n",find(k,rt2[T[x].bm],T[x].b)^k);
        }
        else if(z==2)
        {
            int x,y,k;
            scanf("%d%d%d",&x,&y,&k);
            int z=LCA(x,y);
            printf("%d\n",max(find(k,rt1[x],T[z].d)^k,find(k,rt1[y],T[z].d)^k));
        }
    }
    return 0;
}