#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=201,M=30000001;
const ll P=20170408;
int n,m,k;
bool h[M];
struct str
{
    ll a[N];
    str() {for(int i=0;i<=k-1;++i) a[i]=0;}
    ll &operator[](size_t x) {return a[x];}
    friend str operator*(str a,str b)
    {
        str c;
        for(int i=0;i<=k-1;++i)
        {
            for(int j=0;j<=k-1;++j) c[(i+j)%k]=(c[(i+j)%k]+a[i]*b[j]%P)%P;
        }
        return c;
    }
};
str qpow(str a,ll b)
{
    str x,y=a;
    x.a[0]=1;
    while(b)
    {
        if(b&1) x=x*y;
        y=y*y;
        b>>=1;
    }
    return x;
}
bool check(int x)
{
    if(x==1) return false;
    for(int i=2;i*i<=x;++i)
    {
        if(x%i==0) return false;
    }
    return true;
}
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    h[1]=true;
    for(int i=2;i<=m;++i)
    {
        for(int j=2;i*j<=m;++j) h[i*j]=true;
    }
    str a,b;
    for(int i=1;i<=m;++i)
    {
        ++a[i%k];
        if(h[i]) ++b[i%k];
    }
    ll s=qpow(a,n)[0]-qpow(b,n)[0];
    printf("%lld",(s%P+P)%P);
    return 0;
}