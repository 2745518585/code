#include<cstdio>
#include<algorithm>
#include<bitset>
using namespace std;
inline char gc()
{
    static char buf[100000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1 = buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
template<typename T> inline
void read(T& x)
{
    T f=1,b=0;char ch=gc();
    while (ch<'0'||ch>'9')
    {
        if(ch=='-') f=-1;
        ch=gc();
    }
    while(ch >='0'&&ch<='9') b*=10,b+=ch-'0',ch=gc();
    x=f*b;return;
}
template<typename T> inline
void print(T x)
{
    if(x == 0) return putchar('0'),void();
    if(x<0) putchar('-'),x=-x;
    int st[129]={0},k=0;
    while(x) st[++k]=x%10,x/=10;
    for (int i=k;i;i--) putchar(st[i]+'0');
}
const int N=1001,M=50001;
int n,a[N];
bitset<M> f,g;
bool cmp(int a,int b)
{
    return a>b;
}
int main()
{
    read(n);
    for(int i=1;i<=n;++i) read(a[i]);
    sort(a+1,a+n+1,cmp);
    f[0]=1;
    for(int i=3;i<=n;++i)
    {
        g=f;
        for(int j=2;j<=i-1;++j) f|=(g<<(a[j]-a[i]));
    }
    for(int i=0;i<=n*50;++i)
    {
        if(f[i]) printf("%d ",i);
    }
    return 0;
}