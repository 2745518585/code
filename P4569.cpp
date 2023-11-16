#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef long double ld;
const int N=101,M=26;
int n,m,k,tot=1,a[N][M],f[N],h[N],l[N];
bool g[N];
struct matrix
{
    int m,n;
    ld a[N][N];
    friend matrix operator *(matrix a,matrix b)
    {
        matrix c;
        c.m=a.m,c.n=b.n;
        for(int i=1;i<=c.n;++i)
        {
            for(int j=1;j<=c.n;++j)
            {
                c.a[i][j]=0;
                for(int k=1;k<=a.n;++k)
                {
                    c.a[i][j]=(c.a[i][j]+a.a[i][k]*b.a[k][j]);
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
    void init1()
    {
        for(int i=1;i<=m;++i) for(int j=1;j<=n;++j) a[i][j]=(i==j);
    }
};
matrix qpow(matrix a,int b)
{
    matrix x=a,y=a;
    x.init1();
    while(b!=0)
    {
        if(b&1) x=x*y;
        y=y*y;
        b>>=1;
    }
    return x;
}
void build(char x[])
{
    int k=1;
    for(int i=1;x[i];++i)
    {
        if(a[k][x[i]-'a']==0) a[k][x[i]-'a']=++tot;
        k=a[k][x[i]-'a'];
    }
    g[k]=true;
}
void bfs()
{
    queue<int> Q;
    for(int i=0;i<=k-1;++i) a[0][i]=1;
    f[1]=0;
    Q.push(1);
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        for(int i=0;i<=25;++i)
        {
            if(a[k][i])
            {
                f[a[k][i]]=a[f[k]][i];
                ++l[a[f[k]][i]];
                Q.push(a[k][i]);
            }
            else a[k][i]=a[f[k]][i];
        }
    }
}
void tpsort()
{
    queue<int> Q;
    for(int i=1;i<=tot;++i)
    {
        if(l[i]==0) Q.push(i);
    }
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        h[f[k]]+=h[k];
        --l[f[k]];
        if(l[f[k]]==0) Q.push(f[k]);
    }
}
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;++i)
    {
        char x[N];
        scanf("%s",x+1);
        build(x);
    }
    bfs();
    matrix t;
    t.size(tot+1,tot+1);
    t.init0();
    t.a[tot+1][tot+1]=1;
    for(int i=1;i<=tot;++i)
    {
        for(int j=0;j<=k-1;++j)
        {
            if(g[a[i][j]]==true) 
            {
                t.a[i][tot+1]+=(ld)1/k;
                t.a[i][1]+=(ld)1/k;
            }
            else
            {
                t.a[i][a[i][j]]+=(ld)1/k;
            }
        }
    }
    t=qpow(t,m);
    printf("%.12Lf",t.a[1][tot+1]);
    return 0;
}   