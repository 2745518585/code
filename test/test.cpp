#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000001,M=4;
const ll P=1000000007;
template<int m,int n> struct matrix
{
    int a[m][n];
    matrix(int x=0)
    {
        for(int i=0;i<m;++i) for(int j=0;j<n;++j) a[i][j]=(x==1&&i==j);
    }
    matrix(vector<vector<ll>> _a)
    {
        for(int i=0;i<m;++i) for(int j=0;j<n;++j) a[i][j]=_a[i][j]%P;
    }
    const int *operator[](size_t x) const {return a[x];}
    int *operator[](size_t x) {return a[x];}
};
matrix<2,2> R({{1,1},{1,0}});
template<int m,int n,int q> matrix<m,n> operator*(const matrix<m,q> &a,const matrix<q,n> &b)
{
    matrix<m,n> c;
    for(int i=0;i<m;++i) for(int j=0;j<n;++j) for(int k=0;k<q;++k) c[i][j]=(c[i][j]+(ll)a[i][k]*b[k][j]%P)%P;
    return c;
}
template<int n> matrix<n,n> qpow(matrix<n,n> a,ll b)
{
    matrix<n,n> x(1),y=a;
    while(b)
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
    matrix<1,2> s;
    matrix<2,2> k;
}T[N<<2];
void pushup(int x)
{
    T[x].s[0][0]=(T[x<<1].s[0][0]+T[x<<1|1].s[0][0])%P;
    T[x].s[0][1]=(T[x<<1].s[0][1]+T[x<<1|1].s[0][1])%P;
}
void pushdown(int x)
{
    if(T[x].k[0][0]==1&&T[x].k[0][1]==0&&T[x].k[1][0]==0&&T[x].k[1][1]==1) return;
    T[x<<1].s=T[x<<1].s*T[x].k;
    T[x<<1].k=T[x<<1].k*T[x].k;
    T[x<<1|1].s=T[x<<1|1].s*T[x].k;
    T[x<<1|1].k=T[x<<1|1].k*T[x].k;
    T[x].k=matrix<2,2>(1);
}
void build(int x,int l,int r)
{
    T[x].l=l;
    T[x].r=r;
    T[x].k=matrix<2,2>(1);
    if(l==r)
    {
        T[x].s=matrix<1,2>({{1,0}});
        T[x].s=T[x].s*qpow(R,a[l]-1);
        return;
    }
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    pushup(x);
}
void add(int x,int l,int r,matrix<2,2> k)
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
        return T[x].s[0][0];
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
