#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=200001,M=21;
int n,m,q,t[N],p=1,tot,p2,r,rt;
ll s;
bool g[N];
struct tree
{
    int s,ms,d,a[4],b[4],f;
    ll h[M],w,w2,t;
}T[N];
struct road
{
    int m,q,w;
}a[N<<1];
struct road2
{
    int x,y,w;
}a2[N];
void road(int x,int y,int w)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].w=w;
}
void rebuild(int x,int fa)
{
    int z=0;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa) continue;
        if(z==0)
        {
            a2[++p2]=(road2){x,a[i].m,a[i].w};
            z=x;
        }
        else
        {
            a2[++p2]=(road2){z,++tot,0};
            a2[++p2]=(road2){tot,a[i].m,a[i].w};
            z=tot;
        }
        rebuild(a[i].m,x);
    }
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
void dfs2(int x,int fa,ll w,int k)
{
    T[x].h[k]=w;
    T[x].s=1;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa||g[a[i].m]) continue;
        dfs2(a[i].m,x,w+a[i].w,k);
        T[x].s+=T[a[i].m].s;
    }
}
int dfs(int x,int k)
{
    r=0;
    q=T[x].s;
    dfs1(x,0);
    dfs2(r,0,0,k);
    g[r]=true;
    int z=r;
    for(int i=t[r];i!=0;i=a[i].q)
    {
        if(g[a[i].m]) continue;
        T[z].a[3]=T[z].a[2];
        T[z].a[2]=T[z].a[1];
        T[z].a[1]=dfs(a[i].m,k+1);
        T[z].b[3]=T[z].b[2];
        T[z].b[2]=T[z].b[1];
        T[z].b[1]=a[i].m;
        T[T[z].a[1]].f=z;
    }
    return z;
}
void check(int x,ll k)
{
    int z=x,t=0;
    while(z!=0) z=T[z].f,++t;
    z=x;
    while(t>=1)
    {
        T[z].w+=k;
        T[z].w2+=k;
        T[z].t+=k*T[x].h[t-1];
        // printf("%d ",z);
        z=T[z].f;
        --t;
    }
    // printf("\n");
}
void check2(int x,ll k)
{
    while(x!=0)
    {
        T[x].w2+=k;
        x=T[x].f;
    }
}
int solve(int x,int k)
{
    int z=0,t=0;
    for(int i=1;i<=3;++i)
    {
        if(T[x].a[i]==0) continue;
        if(T[T[x].a[i]].w2*2>T[x].w2)
        {
            ll u=T[x].w2-T[T[x].a[i]].w2;
            check2(T[x].b[i],u);
            t=solve(T[x].a[i],k+1);
            check2(T[x].b[i],-u);
            z=i;
            break;
        }
    }
    if(t==0) t=x;
    // printf("%d %d\n",z,t);
    for(int i=1;i<=3;++i)
    {
        if(i==z) continue;
        s+=T[T[x].a[i]].t;
        // printf("#%d %d\n",T[x].a[i],T[T[x].a[i]].t);
    }
    s+=(T[x].w-T[T[x].a[z]].w)*T[t].h[k];
    // printf("$%d %d\n",x,(T[x].w-T[T[x].a[z]].w)*T[t].h[k]);
    return t;
}
int main()
{
    scanf("%d%d",&n,&m);
    tot=n;
    for(int i=1;i<=n-1;++i)
    {
        int x,y,w;
        scanf("%d%d%d",&x,&y,&w);
        road(x,y,w);
        road(y,x,w);
    }
    rebuild(1,0);
    p=1;
    for(int i=1;i<=n;++i) t[i]=0;
    for(int i=1;i<=p2;++i)
    {
        road(a2[i].x,a2[i].y,a2[i].w);
        road(a2[i].y,a2[i].x,a2[i].w);
    }
    T[1].s=tot;
    T[0].ms=1e9;
    rt=dfs(1,1);
    for(int i=1;i<=m;++i)
    {
        int x,k;
        scanf("%d%d",&x,&k);
        check(x,k);
        s=0;
        solve(rt,1);
        // printf("%d ",solve(rt,1));
        printf("%lld\n",s);
    }
    return 0;
}