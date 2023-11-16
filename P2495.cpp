#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=3000001;
int n,m,tot,p=1,t[N],p2=1,t2[N],b[N],S[N],F;
ll f[N];
bool h[N];
struct tree
{
    int f,s,d,t,z,b;
    ll h;
}T[N];
struct road
{
    int m,q,w;
}a[N<<1];
struct road2
{
    int m,q;
}a2[N<<1];
bool cmp(int x,int y)
{
    return T[x].b<T[y].b;
}
void road(int x,int y,int w)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].w=w;
}
void road2(int x,int y)
{
    a2[++p2].m=y;
    a2[p2].q=t2[x];
    t2[x]=p2;
}
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
void dfs(int x)
{
    f[x]=T[x].h;
    if(h[x]==true) return;
    ll s=0;
    for(int i=t2[x];i!=0;i=a2[i].q)
    {
        dfs(a2[i].m);
        s+=f[a2[i].m];
    }
    f[x]=min(f[x],s);
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
        }
        sort(b+1,b+k+1,cmp);
        p2=1;
        t2[1]=0;
        S[F=1]=1;
        for(int j=1;j<=k;++j)
        {
            int z=LCA(b[j],S[F]);
            while(F>=1&&T[z].d<=T[S[F-1]].d)
            {
                road2(S[F-1],S[F]);
                --F;
                z=LCA(b[j],S[F]);
            }
            t2[b[j]]=0;
            h[b[j]]=true;
            if(z==S[F]) S[++F]=b[j];
            else
            {
                t2[z]=0;
                h[z]=false;
                road2(z,S[F]);
                S[F]=z;
                S[++F]=b[j];
            }
        }
        while(F>=2)
        {
            road2(S[F-1],S[F]);
            --F;
        }
        dfs(1);
        printf("%lld\n",f[1]);
    }
    return 0;
}