#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,tot,p=1,t[N],b[N],S[N],Top;
ll f[N];
bool h[N];
struct road
{
    int m,q,w;
}a[N<<1];
void road(int x,int y,int w)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].w=w;   
}
struct tree
{
    int f,s,d,z,t,b;
    ll h;
}T[N];
void dfs1(int x)
{
    T[x].s=1;
    T[x].d=T[T[x].f].d+1;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==T[x].f) continue;
        T[a[i].m].f=x;
        T[a[i].m].h=min(T[x].h,(ll)a[i].w);
        dfs1(a[i].m);
        T[x].s+=T[a[i].m].s;
        if(T[a[i].m].s>T[T[x].z].s) T[x].z=a[i].m;
    }
}
void dfs2(int x,int k)
{
    T[x].b=++tot;
    T[x].t=k;
    if(T[x].z!=0) dfs2(T[x].z,k);
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==T[x].f||a[i].m==T[x].z) continue;
        else dfs2(a[i].m,a[i].m);
    }
}
int LCA(int x,int y)
{
    if(x==0||y==0) return 0;
    while(T[x].t!=T[y].t)
    {
        if(T[T[x].t].d>=T[T[y].t].d) x=T[T[x].t].f;
        else y=T[T[y].t].f;
    }
    if(T[x].d<T[y].d) return x;
    else return y;
}
bool cmp(int x,int y)
{
    return T[x].b<T[y].b;
}
void dfs(int x)
{
    f[x]=0;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        dfs(a[i].m);
        f[x]+=f[a[i].m];
    }
    if(h[x]) f[x]=T[x].h;
    else f[x]=min(f[x],T[x].h);
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
    T[1].h=1e18;
    dfs1(1);
    dfs2(1,1);
    scanf("%d",&m);
    for(int i=1;i<=m;++i)
    {
        int k;
        scanf("%d",&k);
        for(int j=1;j<=k;++j)
        {
            scanf("%d",&b[j]);
            h[b[j]]=true;
        }
        sort(b+1,b+k+1,cmp);
        p=1;
        t[1]=0;
        S[Top=1]=1;
        for(int j=1;j<=k;++j)
        {
            int z=LCA(S[Top],b[j]);
            while(Top>=1&&T[z].d<=T[S[Top-1]].d)
            {
                road(S[Top-1],S[Top],0);
                --Top;
            }
            t[b[j]]=0;
            if(z!=S[Top])
            {
                t[z]=0;
                h[z]=false;
                road(z,S[Top],0);
                S[Top]=z;
            }
            S[++Top]=b[j];
        }
        while(Top>=2)
        {
            road(S[Top-1],S[Top],0);
            --Top;
        }
        dfs(1);
        printf("%lld\n",f[1]);
    }
    return 0;
}