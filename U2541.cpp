#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1000001,M=5;
const ll P=1000000007;
struct matrix
{
    int m,n;
    ll a[M][M];
    friend matrix operator + (matrix a,matrix b)
    {
        for(int i=1;i<=a.m;++i)
        {
            for(int j=1;j<=a.n;++j)
            {
                a.a[i][j]=(a.a[i][j]+b.a[i][j])%P;
            }
        }
        return a;
    }
    friend matrix operator * (matrix a,matrix b)
    {
        matrix c;
        c.m=a.m,c.n=b.n;
        for(int i=1;i<=c.m;++i)
        {
            for(int j=1;j<=c.n;++j)
            {
                c.a[i][j]=0;
                for(int k=1;k<=a.n;++k)
                {
                    c.a[i][j]=(c.a[i][j]+a.a[i][k]*b.a[k][j]%P)%P;
                }
            }
        }
        return c;
    }
}R,D;
matrix qpow(matrix a,ll b)
{
    matrix x=D,y=a;
    while(b!=0)
    {
        if(b&1) x=x*y;
        y=y*y;
        b>>=1;
    }
    return x;
}
int n,m;
ll a[N];
struct tree
{
    int l,r;
    matrix s,k;
}T[N<<2];
void pushup(int x)
{
    T[x].s=T[x<<1].s+T[x<<1|1].s;
}
void pushdown(int x)
{
    if(T[x].k.a[1][1]==1&&T[x].k.a[1][2]==0&&T[x].k.a[2][1]==0&&T[x].k.a[2][2]==1) return;
    T[x<<1].s=T[x<<1].s*T[x].k;
    T[x<<1].k=T[x<<1].k*T[x].k;
    T[x<<1|1].s=T[x<<1|1].s*T[x].k;
    T[x<<1|1].k=T[x<<1|1].k*T[x].k;
    T[x].k=D;
}
void build(int x,int l,int r)
{
    T[x].l=l;
    T[x].r=r;
    T[x].s.m=2,T[x].s.n=1;
    T[x].k=D;
    if(l==r)
    {
        T[x].s.m=2,T[x].s.n=1;
        T[x].s.a[1][1]=1,T[x].s.a[1][2]=0;
        T[x].s=T[x].s*qpow(R,a[l]-1);
        return;
    }
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    pushup(x);
}
void add(int x,int l,int r,matrix k)
{
    if(T[x].l>=l&&T[x].r<=r)
    {
        T[x].s=T[x].s*k;
        T[x].k=T[x].k*k;
        return;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    if(l<=z) add(x<<1,l,r,k);
    if(r>z) add(x<<1|1,l,r,k);
    pushup(x);
}
ll sum(int x,int l,int r)
{
    if(T[x].l>=l&&T[x].r<=r)
    {
        return T[x].s.a[1][1];
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    ll s=0;
    if(l<=z) s=(s+sum(x<<1,l,r))%P;
    if(r>z) s=(s+sum(x<<1|1,l,r))%P;
    return s;
}
int main()
{
    R.m=R.n=2;
    R.a[1][1]=R.a[1][2]=R.a[2][1]=1,R.a[2][2]=0;
    D.m=D.n=2;
    D.a[1][1]=D.a[2][2]=1,D.a[1][2]=D.a[2][1]=0;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&a[i]);
    }
    build(1,1,n);
    for(int i=1;i<=m;++i)
    {
        int z;
        scanf("%d",&z);
        if(z==1)
        {
            int x,y;
            ll k;
            scanf("%d%d%lld",&x,&y,&k);
            add(1,x,y,qpow(R,k));
        }
        else if(z==2)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            printf("%lld\n",sum(1,x,y)%P);
        }
    }
    return 0;
}