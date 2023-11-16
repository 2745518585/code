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
const int N=1100001,M=21;
int n,m,a[N],d[N];
bool h1[N],h2[N];
char b[N];
void solve()
{
    for(int i=1;i<=n;++i) b[i]=gc();
    gc();
    for(int i=1;i<=n;++i) h1[i]=h2[i]=false;
    int s=n;
    for(int i=n;i>=1;--i)
    {
        if(b[d[i]]=='1') continue;
        int w=0;
        int x=d[i];
        while(x>=1&&(b[x]=='0'||a[x]>=a[d[i]])&&!h1[x]) h1[x]=true,w+=(b[x]=='1'||a[x]>=a[d[i]]),--x;
        if(h1[x]==true) continue;
        int y=d[i];
        while(y<=n&&(b[y]=='0'||a[y]>=a[d[i]])&&!h2[y]) h2[y]=true,w+=(b[y]=='1'||a[y]>=a[d[i]]),++y;
        if(h2[y]==true) continue;
        s=min(s,w-1);
    }
    printf("%d\n",s);
}
int main()
{
    read(n);
    for(int i=1;i<=n;++i) read(a[i]);
    for(int i=1;i<=n;++i) d[a[i]]=i;
    read(m);
    for(int i=1;i<=m;++i) solve();
    return 0;
}