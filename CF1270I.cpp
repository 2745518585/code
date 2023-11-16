#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1001;
int n,m,q;
struct matrix
{
    ll a[N][N];
    matrix()
    {
        for(int i=1;i<=n;++i) for(int j=1;j<=n;++j) a[i][j]=0;
        a[1][1]=0;
    }
    const ll *operator[](size_t x) const {return a[x];}
    ll *operator[](size_t x) {return a[x];}
    friend matrix operator*(const matrix &a,const matrix &b)
    {
        matrix c;
        for(int i=1;i<=n;++i)
        {
            for(int j=1;j<=n;++j) c[i][j]=0;
        }
        for(int i=1;i<=n;++i)
        {
            for(int j=1;j<=n;++j)
            {
                if(a[i][j]==0) continue;
                for(int k=1;k<=n;++k)
                {
                    for(int l=1;l<=n;++l)
                    {
                        c[(i+k-2)%n+1][(j+l-2)%n+1]^=a[i][j]*b[k][l];
                    }
                }
            }
        }
        return c;
    }
};
matrix qpow(matrix x,matrix a,ll b)
{
    matrix y=a;
    while(b)
    {
        if(b&1) x=y*x;
        y=y*y;
        b>>=1;
    }
    return x;
}
int main()
{
    scanf("%d",&q);
    n=1<<q;
    matrix a;
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            scanf("%lld",&a[i][j]);
        }
    }
    matrix b;
    scanf("%d",&m);
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        b[x][y]=1;
    }
    a=qpow(a,b,n-1);
    int s=0;
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(a[i][j]) ++s;
        }
    }
    printf("%d",s);
    return 0;
}