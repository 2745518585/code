#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
using namespace std;
typedef long long ll;
const int N=51001,M=300001;
const ll P=998244353;
template<int m,int n> struct matrix
{
    int a[m][n];
    matrix(int x=0)
    {
        for(int i=0;i<m;++i) for(int j=0;j<n;++j) a[i][j]=(x==1&&i==j);
    }
    const int *operator[](size_t x) const {return a[x];}
    int *operator[](size_t x) {return a[x];}
};
template<int m,int n,int q> matrix<m,n> operator*(const matrix<m,q> &a,const matrix<q,n> &b)
{
    matrix<m,n> c;
    for(int i=0;i<m;++i) for(int j=0;j<n;++j) for(int k=0;k<q;++k) c[i][j]=(c[i][j]+(ll)a[i][k]*b[k][j]%P)%P;
    return c;
}
template<int m,int n,int q> matrix<m,n> o1(const matrix<m,q> &a,const matrix<q,n> &b)
{
    matrix<m,n> c;
    for(int i=0;i<m;++i) for(int k=0;k<q;++k)
    {
        if(a[i][k]==0) continue;
        for(int j=0;j<n;++j) c[i][j]=(c[i][j]+(ll)a[i][k]*b[k][j]%P)%P;
    }
    return c;
}
template<int m,int n,int q> matrix<m,n> o2(const matrix<m,q> &a,const matrix<q,n> &b)
{
    matrix<m,n> c;
    for(int k=0;k<q;++k) for(int j=0;j<n;++j)
    {
        if(b[k][j]==0) continue;
        for(int i=0;i<m;++i) c[i][j]=(c[i][j]+(ll)a[i][k]*b[k][j]%P)%P;
    }
    return c;
}
int n,m,a[N],c[M];
matrix<16,16> d[3],g[N];
matrix<1,16> p;
struct tree
{
    int l,r;
    vector<pair<pair<int,int>,int>> a;
}T[N<<2];
void build(int x,int l,int r)
{
    T[x].l=l,T[x].r=r;
    if(l==r) return;
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
}
void add(int x,int l,int r,pair<pair<int,int>,int> k)
{
    int z=T[x].l+T[x].r>>1;
    if(l<=z&&r>=z)
    {
        T[x].a.push_back(k);
        return;
    }
    if(l<=z) add(x<<1,l,r,k);
    else add(x<<1|1,l,r,k);
}
void solve(int x)
{
    int l=T[x].l,r=T[x].r,z=l+r>>1;
    g[z]=d[a[z]];
    for(int i=z-1;i>=l;--i) g[i]=o1(d[a[i]],g[i+1]);
    g[z+1]=d[a[z+1]];
    for(int i=z+2;i<=r;++i) g[i]=o2(g[i-1],d[a[i]]);
    for(auto i:T[x].a)
    {
        matrix<1,16> u=p*g[i.first.first];
        if(i.first.second>z) u=u*g[i.first.second];
        for(int j=0;j<8;++j)
        {
            c[i.second]=(c[i.second]+u[0][j<<1|1])%P;
        }
    }
}
int main()
{
    static char z[N];
    scanf("%d%s",&n,z+1);
    for(int i=1;i<=n;++i)
    {
        if(z[i]=='0') a[i]=0;
        else if(z[i]=='1') a[i]=1;
        else if(z[i]=='?') a[i]=2;
    }
    for(int i=0;i<16;++i)
    {
        int j=(i&1)|(i&8);
        if(i&2) j|=4;
        if(i&4) j|=2;
        if(j&2) j^=1;
        j^=2;
        d[0][i][j]=(d[0][i][j]+1)%P;
        d[2][i][j]=(d[2][i][j]+1)%P;
    }
    for(int i=0;i<16;++i)
    {
        int j=(i&1)|(i&4);
        if(i&2) j|=8;
        if(i&8) j|=2;
        if(j&2) j^=1;
        j^=2;
        d[1][i][j]=(d[1][i][j]+1)%P;
        d[2][i][j]=(d[2][i][j]+1)%P;
    }
    p[0][2]=1;
    build(1,1,n);
    scanf("%d",&m);
    for(int i=1;i<=m;++i)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        add(1,l,r,make_pair(make_pair(l,r),i));
    }
    for(int i=1;i<=n*2;++i)
    {
        if(!T[i].a.empty()) solve(i);
    }
    for(int i=1;i<=m;++i)
    {
        printf("%d\n",(c[i]%P+P)%P);
    }
    return 0;
}