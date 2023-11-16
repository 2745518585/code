#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001,M=30;
int n,m,q,tot,tot1,tot2,b1[N][2],b2[N][2],c1[N][2],c2[N][2],d1[N],d2[N],fa1[N][M],fa2[N][M],ga[N],rt[N];
struct road
{
    int x,y;
}a1[N],a2[N];
struct tree
{
    int l,r,s;
}T[N<<4];
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
int sum(int x,int ls,int rs,int l,int r)
{
    if(x==0) return 0;
    if(ls>=l&&rs<=r)
    {
        return T[x].s;
    }
    int z=ls+rs>>1,s=0;
    if(l<=z) s+=sum(T[x].l,ls,z,l,r);
    if(r>z) s+=sum(T[x].r,z+1,rs,l,r);
    return s;
}
bool cmp1(road a,road b)
{
    return min(a.x,a.y)>min(b.x,b.y);
}
bool cmp2(road a,road b)
{
    return max(a.x,a.y)<max(b.x,b.y);
}
int find(int x)
{
    if(ga[x]==x) return x;
    return ga[x]=find(ga[x]);
}
void dfs1(int x)
{
    if(x<=n)
    {
        c1[x][0]=c1[x][1]=++tot1;
        d1[x]=tot1;
        return;
    }
    dfs1(b1[x][0]);
    dfs1(b1[x][1]);
    c1[x][0]=min(c1[b1[x][0]][0],c1[b1[x][1]][0]);
    c1[x][1]=max(c1[b1[x][0]][1],c1[b1[x][1]][1]);
}
void dfs2(int x)
{
    if(x<=n)
    {
        c2[x][0]=c2[x][1]=++tot2;
        d2[tot2]=x;
        return;
    }
    dfs2(b2[x][0]);
    dfs2(b2[x][1]);
    c2[x][0]=min(c2[b2[x][0]][0],c2[b2[x][1]][0]);
    c2[x][1]=max(c2[b2[x][0]][1],c2[b2[x][1]][1]);
}
int main()
{
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        a1[i].x=a2[i].x=x+1;
        a1[i].y=a2[i].y=y+1;
    }
    sort(a1+1,a1+m+1,cmp1);
    for(int i=1;i<=n+m;++i) ga[i]=i;
    for(int i=1;i<=m;++i)
    {
        if(find(a1[i].x)!=find(a1[i].y))
        {
            int x=find(a1[i].x),y=find(a1[i].y);
            ga[x]=ga[y]=n+i;
            fa1[x][0]=fa1[y][0]=n+i;
            b1[n+i][0]=x;
            b1[n+i][1]=y;
        }
    }
    for(int i=1;i<=20;++i)
    {
        for(int j=1;j<=n+m;++j)
        {
            fa1[j][i]=fa1[fa1[j][i-1]][i-1];
        }
    }
    for(int i=n+m;i>=1;--i)
    {
        if(b1[i][0]!=0)
        {
            dfs1(i);
            break;
        }
    }
    sort(a2+1,a2+m+1,cmp2);
    for(int i=1;i<=n+m;++i) ga[i]=i;
    for(int i=1;i<=m;++i)
    {
        if(find(a2[i].x)!=find(a2[i].y))
        {
            int x=find(a2[i].x),y=find(a2[i].y);
            ga[x]=ga[y]=n+i;
            fa2[x][0]=fa2[y][0]=n+i;
            b2[n+i][0]=x;
            b2[n+i][1]=y;
        }
    }
    for(int i=1;i<=20;++i)
    {
        for(int j=1;j<=n+m;++j)
        {
            fa2[j][i]=fa2[fa2[j][i-1]][i-1];
        }
    }
    for(int i=n+m;i>=1;--i)
    {
        if(b2[i][0]!=0)
        {
            dfs2(i);
            break;
        }
    }
    for(int i=1;i<=n;++i)
    {
        rt[i]=rt[i-1];
        add(rt[i],1,n,d1[d2[i]],1);
    }
    for(int i=1;i<=q;++i)
    {
        int x,y,l,r;
        scanf("%d%d%d%d",&x,&y,&l,&r);
        ++x,++y,++l,++r;
        if(x<l||y>r)
        {
            printf("0\n");
            continue;
        }
        int t=0;
        while(t>=0)
        {
            if(fa1[x][t]!=0&&min(a1[fa1[x][t]-n].x,a1[fa1[x][t]-n].y)>=l) x=fa1[x][t],++t;
            else --t;
        }
        t=0;
        while(t>=0)
        {
            if(fa2[y][t]!=0&&max(a2[fa2[y][t]-n].x,a2[fa2[y][t]-n].y)<=r) y=fa2[y][t],++t;
            else --t;
        }
        if(sum(rt[c2[y][1]],1,n,c1[x][0],c1[x][1])-sum(rt[c2[y][0]-1],1,n,c1[x][0],c1[x][1])>=1) printf("1\n");
        else printf("0\n");
    }
    return 0;
}