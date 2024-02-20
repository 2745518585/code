#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll P=998244353;
int n,k,q;
void exgcd(ll a,ll b,ll &x,ll &y)
{
    if(b==0) x=1,y=0;
    else exgcd(b,a%b,y,x),y-=a/b*x;
}
ll inv(ll a)
{
    ll x,y;
    exgcd((a%P+P)%P,P,x,y);
    return (x%P+P)%P;
}
template<int m,int n> struct matrix
{
    ll a[m][n];
    matrix(int x=0)
    {
        for(int i=0;i<m;++i) for(int j=0;j<n;++j) a[i][j]=(x==1&&i==j);
    }
    matrix(vector<vector<ll>> _a)
    {
        for(int i=0;i<m;++i) for(int j=0;j<n;++j) a[i][j]=_a[i][j]%P;
    }
    const ll *operator[](size_t x) const {return a[x];}
    ll *operator[](size_t x) {return a[x];}
};
template<int m,int n,int q> matrix<m,n> operator*(const matrix<m,q> &a,const matrix<q,n> &b)
{
    matrix<m,n> c;
    for(int i=0;i<m;++i) for(int j=0;j<n;++j) for(int k=0;k<q;++k) c[i][j]=(c[i][j]+a[i][k]*b[k][j]%P)%P;
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
ll qpow(ll a,ll b)
{
    ll x=1,y=a;
    while(b)
    {
        if(b&1) x=x*y%P;
        y=y*y%P;
        b>>=1;
    }
    return x;
}
struct tree
{
    int l,r,f;
}T[N<<2];
void build(int fa,int l,int r)
{
    int x=++q;
    T[x].l=l,T[x].r=r;
    T[x].f=fa;
    if(l==r) return;
    int z;
    scanf("%d",&z);
    build(x,l,z);
    build(x,z+1,r);
}
ll sum(int x)
{
    return (ll)x*(x+1)/2;
}
int main()
{
    scanf("%d%d",&n,&k);
    build(0,1,n);
    ll s=0;
    for(int i=1;i<=q;++i)
    {
        ll p1,p2,p3,p4,p5;
        if(T[i].f==0) p1=0,p2=0,p3=0,p4=1,p5=sum(n)-1;
        else p1=sum(T[T[i].f].l-1)+sum(n-T[T[i].f].r),p2=(ll)(T[T[i].f].l)*(n-T[T[i].f].r+1),p3=sum(T[i].l-T[T[i].f].l)+sum(T[T[i].f].r-T[i].r)+(ll)(T[T[i].f].l-1)*(T[i].l-T[T[i].f].l)+(ll)(n-T[T[i].f].r)*(T[T[i].f].r-T[i].r),p4=(ll)(T[i].l)*(n-T[i].r+1)-p2,p5=sum(n)-sum(T[i].l-1)-sum(n-T[i].r)-(ll)(T[i].l)*(n-T[i].r+1);
        // printf("%d %d %d %d:%lld %lld %lld %lld %lld:%lld %lld\n",T[T[i].f].l,T[T[i].f].r,T[i].l,T[i].r,p1,p2,p3,p4,p5,p1+p2+p3+p4+p5,sum(n));
        matrix<1,3> a({{1,0,0}});
        matrix<3,3> b({{p1+p3+p5,p2,p4},{p5,p1+p2,p3+p4},{p5,0,p1+p2+p3+p4}});
        a=a*qpow(b,k);
        s=(s+a[0][2])%P;
    }
    printf("%lld",(s*inv(qpow(sum(n)%P,k))%P+P)%P);
    return 0;
}