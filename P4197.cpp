#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001,M=21;
int n,m,q,tot,tot2,b[N][2],c[N][2],d[N],f[N],fa[N][M],ga[N],rt[N];
struct road
{
    int x,y,w;
}a[N];
struct tree
{
    int l,r,s;
}T[N<<2];
void pushup(int x)
{
    T[x].s=T[T[x].l].s+T[T[x].r].s;
}
void add(int &x,int ls,int rs,int q,int k)
{
    T[++tot]=T[x];
    x=tot;
    if(ls==rs)
    {
        T[x].s+=k;
        return;
    }
    int z=ls+rs>>1;
    if(q<=z) add(T[x].l,ls,z,q,k);
    else add(T[x].r,z+1,rs,q,k);
    pushup(x);
}
int sum(int x1,int x2,int ls,int rs,int k)
{
    if(ls==rs) return ls;
    int z=ls+rs>>1;
    if(T[T[x2].r].s-T[T[x1].r].s>=k) return sum(T[x1].r,T[x2].r,z+1,rs,k);
    return sum(T[x1].l,T[x2].l,ls,z,k-(T[T[x2].r].s-T[T[x1].r].s));
}
bool cmp(road a,road b)
{
    return a.w<b.w;
}
int find(int x)
{
    if(ga[x]==x) return x;
    return ga[x]=find(ga[x]);
}
void dfs(int x)
{
    if(x<=n)
    {
        c[x][0]=c[x][1]=++tot2;
        rt[tot2]=rt[tot2-1];
        add(rt[tot2],1,1e9,d[x],1);
        return;
    }
    dfs(b[x][0]);
    dfs(b[x][1]);
    c[x][0]=min(c[b[x][0]][0],c[b[x][1]][0]);
    c[x][1]=max(c[b[x][0]][1],c[b[x][1]][1]);
}
int main()
{
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&d[i]);
    }
    for(int i=1;i<=m;++i)
    {
        scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].w);
    }
    sort(a+1,a+m+1,cmp);
    for(int i=1;i<=n+m;++i) ga[i]=i;
    for(int i=1;i<=m;++i)
    {
        if(find(a[i].x)!=find(a[i].y))
        {
            int x=find(a[i].x),y=find(a[i].y);
            ga[x]=ga[y]=n+i;
            fa[x][0]=fa[y][0]=n+i;
            b[n+i][0]=x,b[n+i][1]=y;
        }
    }
    for(int i=1;i<=20;++i)
    {
        for(int j=1;j<=n+m;++j)
        {
            fa[j][i]=fa[fa[j][i-1]][i-1];
        }
    }
    for(int i=n+m;i>=1;--i)
    {
        if(b[i][0]!=0)
        {
            dfs(i);
            break;
        }
    }
    for(int i=1;i<=q;++i)
    {
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        int t=0;
        while(t>=0)
        {
            if(fa[x][t]!=0&&a[fa[x][t]-n].w<=y) x=fa[x][t],++t;
            else --t;
        }
        if(T[rt[c[x][1]]].s-T[rt[c[x][0]-1]].s<z) printf("-1\n");
        else printf("%d\n",sum(rt[c[x][0]-1],rt[c[x][1]],1,1e9,z));
    }
    return 0;
}