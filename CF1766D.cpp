#include<cstdio>
#include<algorithm>
#include<cmath>
#include<vector>
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
const int N=2000001,M=20000001;
int n,a[N],b[N],u[N];
bool h[M];
vector<int> f[M];
int main()
{
    read(n);
    for(int i=1;i<=n;++i)
    {
        read(a[i]),read(b[i]);
        if(a[i]==1||b[i]==1) ++a[i],++b[i],++u[i];
        h[abs(b[i]-a[i])]=true;
    }
    for(int i=2;i<=1e7;++i)
    {
        for(int j=1;i*j<=1e7;++j)
        {
            if(h[i*j]!=0) f[i*j].push_back(i);
        }
    }
    for(int i=1;i<=n;++i)
    {
        int s=1e9;
        for(int j=0;j<f[abs(b[i]-a[i])].size();++j)
        {
            s=min(s,(int)ceil((double)a[i]/f[abs(b[i]-a[i])][j])*f[abs(b[i]-a[i])][j]-a[i]);
        }
        print((s==1e9?-1:s+u[i]));
        putchar('\n');
    }
    return 0;
}