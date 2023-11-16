#include<cstdio>
#include<algorithm>
using namespace std;
inline char gc()
{
    static char buf[100000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
template<typename T>
inline void read(T &x)
{
    T u=1,t=0;char c=gc();
    while(c<'0'||c>'9') {if(c=='-') u=-1; c=gc();}
    while(c>='0'&&c<='9') t*=10,t+=c-'0',c=gc();
    x=u*t;return;
}
template<typename T>
inline void print(T x)
{
    if(x==0) return putchar('0'),void();
    if(x<0) putchar('-'),x=-x;
    int c[129]={0},k=0;
    while(x) c[++k]=x%10,x/=10;
    for(int i=k;i;--i) putchar(c[i]+'0');
}
const int N=5001;
int n,a[N][N];
int main()
{
    read(n);
    bool u=false;
    if(n%2==0) u=true,--n;
    if(n%2==1)
    {
        for(int i=1;i<=n/2+1;++i) a[i][i]=1;
        for(int i=1;i<=n/2;++i)
        {
            int u=i%2;
            for(int j=0;j<=i-1;++j)
            {
                a[i-j][i+j+1]=i*2+(u^(j&1));
                a[i+j+1][i-j]=i*2+(u^1^(j&1));
            }
            u=0;
            for(int j=i+1;j<=n/2+1;++j)
            {
                a[j-i][j+i]=i*2+u;
                a[j+i][j-i]=i*2+(u^1);
                u^=1;
            }
        }
    }
    if(u)
    {
        for(int i=1;i<=n+1;++i) a[i][n-i+2]=n+1;
    }
    for(int i=n+u;i>=1;--i)
    {
        for(int j=1;j<=n+u-i+1;++j)
        {
            print(a[i][j]);
            putchar(' ');
        }
        putchar('\n');
    }
    return 0;
}