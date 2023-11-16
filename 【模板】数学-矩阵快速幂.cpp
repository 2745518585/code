#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const ll P=1e9+7;
const int N=15;
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
int main()
{
    return 0;
}