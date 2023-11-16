#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001,M=5;
int n,m,tot,p=1,t[N],b[N],c[N],f[N][2],g[N][2];
struct matrix
{
    int m,n,a[M][M];
    friend matrix operator *(matrix a,matrix b)
    {
        matrix c;
        c.m=a.m,c.n=b.n;
        for(int i=1;i<=c.n;++i)
        {
            for(int j=1;j<=c.n;++j)
            {
                c.a[i][j]=-1e9;
                for(int k=1;k<=a.n;++k)
                {
                    c.a[i][j]=max(c.a[i][j],a.a[i][k]+b.a[k][j]);
                }
            }
        }
        return c;
    }
    void size(int x,int y) {m=x,n=y;}
    void init0()
    {
        for(int i=1;i<=m;++i) for(int j=1;j<=n;++j) a[i][j]=0;
    }
    void init(int x,int y)
    {
        a[1][1]=a[2][1]=x;
        a[1][2]=y;
        a[2][2]=-1e9;
    }
    void init2(int x,int y)
    {
        a[1][1]=x,a[1][2]=y;
    }
};
struct tree
{
    int f,s,d,t,z,b,be;
}T[N];
struct tree2
{
    int l,r;
    matrix s;
}T2[N<<2];
struct road
{
    int m,q;
}a[N<<1];
void pushup(int x)
{
    T2[x].s=T2[x<<1|1].s*T2[x<<1].s;
}
void build(int x,int l,int r)
{
    T2[x].l=l;
    T2[x].r=r;
    T2[x].s.size(2,2);
    T2[x].s.init0();
    if(l==r) 
    {
        T2[x].s.init(g[b[l]][0],g[b[l]][1]);
        return;
    }
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    pushup(x);
}
void add(int x,int q,matrix k)
{
    if(T2[x].l==T2[x].r)
    {
        T2[x].s=k;
        return;
    }
    int z=T2[x].l+T2[x].r>>1;
    if(q<=z) add(x<<1,q,k);
    else add(x<<1|1,q,k);
    pushup(x);
}
matrix sum(int x,int l,int r)
{
    if(l>r)
    {
        matrix z;
        z.size(2,2);
        z.init0();
        return z;
    }
    if(T2[x].l>=l&&T2[x].r<=r)
    {
        return T2[x].s;
    }
    int z=T2[x].l+T2[x].r>>1;
    if(l<=z&&(!(r>z))) return sum(x<<1,l,r);
    if((!(l<=z))&&r>z) return sum(x<<1|1,l,r);
    return sum(x<<1|1,l,r)*sum(x<<1,l,r);
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
    T[k].be=max(T[k].be,tot);
    T[x].t=k;
    if(T[x].z!=0) dfs2(T[x].z,k);
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==T[x].f||a[i].m==T[x].z) continue;
        dfs2(a[i].m,a[i].m);
    }
}
void dfs0(int x)
{
    f[x][1]=g[x][1]=c[x];
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==T[x].f) continue;
        dfs0(a[i].m);
        f[x][0]+=max(f[a[i].m][0],f[a[i].m][1]);
        f[x][1]+=f[a[i].m][0];
        if(a[i].m!=T[x].z)
        {
            g[x][0]+=max(f[a[i].m][0],f[a[i].m][1]);
            g[x][1]+=f[a[i].m][0];
        }
    }
}
void check(int x,int k)
{
    g[x][1]+=k;
    while(x!=0)
    {
        matrix z;
        z.size(2,2);
        z.init(g[x][0],g[x][1]);
        add(1,T[x].b,z);
        matrix s=sum(1,T[T[x].t].b,T[T[x].t].be);
        x=T[x].t;
        if(T[x].f!=0)
        {
            g[T[x].f][0]+=(max(s.a[1][1],s.a[1][2])-max(f[x][0],f[x][1]));
            g[T[x].f][1]+=(s.a[1][1]-f[x][0]);
        }
        f[x][0]=s.a[1][1];
        f[x][1]=s.a[1][2];
        x=T[x].f;
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&c[i]);
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
    for(int i=1;i<=n;++i) b[T[i].b]=i;
    dfs0(1);
    build(1,1,n);
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        y-=c[x];
        check(x,y);
        printf("%d\n",max(f[1][0],f[1][1]));
        c[x]+=y;
    }
    return 0;
}