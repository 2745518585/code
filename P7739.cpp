#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll P=998244353;
int n,m,tot,rt;
struct matrix
{
    int m,n;
    ll a[2][2];
    matrix(){}
    matrix(int _m,int _n,int x)
    {
        m=_m,n=_n;
        if(x==0) for(int i=0;i<m;++i) for(int j=0;j<n;++j) a[i][j]=0;
        if(x==1) for(int i=0;i<m;++i) for(int j=0;j<n;++j) a[i][j]=i==j;
    }
    matrix(initializer_list<initializer_list<ll>> _a)
    {
        m=0;
        for(auto i:_a) {n=0;for(auto j:i) a[m][n++]=j; ++m;}
    }
    friend matrix operator*(matrix a,matrix b)
    {
        matrix c(a.m,b.n,0);
        for(int i=0;i<c.m;++i)
        {
            for(int j=0;j<c.n;++j)
            {
                for(int k=0;k<a.n;++k)
                {
                    c.a[i][j]=(c.a[i][j]+a.a[i][k]*b.a[k][j]%P)%P;
                }
            }
        }
        return c;
    }
    void print()
    {
        for(int i=0;i<m;++i)
        {
            for(int j=0;j<n;++j)
            {
                printf("%d ",a[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }
}r[2];
struct tree
{
    int l,r,s,t,k1,k2,h;
    matrix w[2][2];
}T[N];
void pushup(int x)
{
    T[x].s=T[T[x].l].s+T[T[x].r].s+1;
    T[x].w[0][0]=T[T[x].l].w[0][0]*r[T[x].t]*T[T[x].r].w[0][0];
    T[x].w[1][0]=T[T[x].l].w[1][0]*r[T[x].t^1]*T[T[x].r].w[1][0];
    T[x].w[0][1]=T[T[x].r].w[0][1]*r[T[x].t]*T[T[x].l].w[0][1];
    T[x].w[1][1]=T[T[x].r].w[1][1]*r[T[x].t^1]*T[T[x].l].w[1][1];
}
void maketag1(int x)
{
    if(x==0) return;
    T[x].k1^=1;
    T[x].t^=1;
    swap(T[x].w[0][0],T[x].w[1][0]);
    swap(T[x].w[0][1],T[x].w[1][1]);
}
void maketag2(int x)
{
    if(x==0) return;
    T[x].k2^=1;
    swap(T[x].l,T[x].r);
    swap(T[x].w[0][0],T[x].w[0][1]);
    swap(T[x].w[1][0],T[x].w[1][1]);
}
void pushdown(int x)
{
    if(T[x].k1)
    {
        maketag1(T[x].l);
        maketag1(T[x].r);
        T[x].k1=0;
    }
    if(T[x].k2)
    {
        maketag2(T[x].l);
        maketag2(T[x].r);
        T[x].k2=0;
    }
}
void split(int x,int k,int &x1,int &x2)
{
    if(x==0)
    {
        x1=x2=0;
        return;
    }
    pushdown(x);
    if(T[T[x].l].s+1<=k)
    {
        x1=x;
        split(T[x1].r,k-T[T[x].l].s-1,T[x1].r,x2);
    }
    else
    {
        x2=x;
        split(T[x2].l,k,x1,T[x2].l);
    }
    pushup(x);
}
int merge(int x1,int x2)
{
    if(x1==0||x2==0) return x1+x2;
    pushdown(x1);
    pushdown(x2);
    if(T[x1].h<T[x2].h)
    {
        T[x1].r=merge(T[x1].r,x2);
        pushup(x1);
        return x1;
    }
    else
    {
        T[x2].l=merge(x1,T[x2].l);
        pushup(x2);
        return x2;
    }
}
void add(int t)
{
    T[++tot].t=t;
    T[tot].l=T[tot].r=T[tot].k1=T[tot].k2=0;
    T[tot].s=1;
    T[tot].h=rand();
    pushup(tot);
    rt=merge(rt,tot);
}
int main()
{
    scanf("%d%d",&n,&m);
    srand(n*m);
    r[0]=matrix({{1,1},{0,1}});
    r[1]=matrix({{0,-1},{1,2}});
    T[0].w[0][0]=T[0].w[1][0]=T[0].w[0][1]=T[0].w[1][1]=matrix(2,2,1);
    char z[N];
    scanf("%s",z+1);
    for(int i=1;i<=n;++i)
    {
        if(z[i]=='W') add(0);
        else if(z[i]=='E') add(1);
    }
    matrix p=r[0]*T[rt].w[0][0];
    printf("%lld %lld\n",(p.a[1][1]+P)%P,(p.a[0][1]+P)%P);
    for(int i=1;i<=m;++i)
    {
        char z[10];
        scanf("%s",z);
        if(z[0]=='A')
        {
            scanf("%s",z);
            if(z[0]=='W') add(0);
            else if(z[0]=='E') add(1);
        }
        else if(z[0]=='F')
        {
            int x,y;
            scanf("%d%d",&x,&y);
            int x1,x2,x3;
            split(rt,y,x1,x3);
            split(x1,x-1,x1,x2);
            maketag1(x2);
            rt=merge(merge(x1,x2),x3);
        }
        else if(z[0]=='R')
        {
            int x,y;
            scanf("%d%d",&x,&y);
            int x1,x2,x3;
            split(rt,y,x1,x3);
            split(x1,x-1,x1,x2);
            maketag2(x2);
            rt=merge(merge(x1,x2),x3);
        }
        matrix p=r[0]*T[rt].w[0][0];
        printf("%lld %lld\n",(p.a[1][1]+P)%P,(p.a[0][1]+P)%P);
    }
    return 0;
}