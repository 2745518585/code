#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=300001,M=51;
int n,m,q,p=1,t[N];
ll b[N][M],P=998244353;
struct tree
{
    int f,s,d,t,z,b,bm;
}T[N];
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
void dfs1(int x)
{
    T[x].s=1;
    T[x].d=T[T[x].f].d+1;
    ll w=1;
    for(int i=1;i<=M;++i)
    {
    	w=(w*(T[x].d-1))%P;
    	b[x][i]=(b[T[x].f][i]+w)%P;
    }
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
    T[x].b=++q;
    T[x].t=k;
    if(T[x].z!=0) dfs2(T[x].z,k);
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==T[x].f||a[i].m==T[x].z) continue;
        dfs2(a[i].m,a[i].m);
    }
    T[x].bm=q;
}
ll query(int x,int y,int k)
{
    ll s=0;
    while(T[x].t!=T[y].t)
    {
        if(T[T[x].t].d>=T[T[y].t].d)
        {
            s=(s+(b[x][k]-b[T[T[x].t].f][k])%P+P)%P;
            x=T[T[x].t].f;
        }
        else
        {
            s=(s+(b[y][k]-b[T[T[y].t].f][k])%P+P)%P;
            y=T[T[y].t].f;
        }
    }
    if(T[x].d<T[y].d) s=(s+(b[y][k]-b[T[x].f][k])%P+P)%P;
    else s=(s+(b[x][k]-b[T[y].f][k])%P+P)%P;
    return s;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n-1;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        road(x,y);
        road(y,x);
    }
    dfs1(1);
    dfs2(1,1);
    scanf("%d",&m);
    for(int i=1;i<=m;++i)
    {
        int x,y,k;
        scanf("%d%d%d",&x,&y,&k);
        printf("%lld\n",query(x,y,k)%P);
    }
    return 0;
}
