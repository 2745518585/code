#include<cstdio>
#include<algorithm>
#include<vector>
#include<set>
using namespace std;
typedef long long ll;
typedef __int128_t lll;
inline char gc()
{
    static char buf[100000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
template<typename T> inline void read(T &x)
{
    T u=1,t=0;char c=gc();
    while(c<'0'||c>'9') {if(c=='-') u=-1; c=gc();}
    while(c>='0'&&c<='9') t*=10,t+=c-'0',c=gc();
    x=u*t;return;
}
template<typename T,typename ...O> inline void read(T &x,O &...o) {read(x),read(o...);}
template<typename T> inline void print(T x)
{
    if(x==0) return putchar('0'),void();
    if(x<0) putchar('-'),x=-x;
    int c[129]={0},k=0;
    while(x) c[++k]=x%10,x/=10;
    for(int i=k;i;--i) putchar(c[i]+'0');
}
template<typename T,typename ...O> inline void print(T x,O ...o) {print(x),putchar(' '),print(o...);}
const int N=2000001;
int n,m,b[N],g[N],v;
ll k,f[N][2];
bool h[N];
vector<int> a[N];
set<int> Set;
void dfs(int x,int fa)
{
    f[x][0]=f[x][1]=1;
    for(auto i:a[x])
    {
        if(i==fa) continue;
        dfs(i,x);
        f[x][0]=min((lll)f[x][0]*(f[i][0]+f[i][1]),(lll)k+1);
        f[x][1]=min((lll)f[x][1]*f[i][0],(lll)k+1);
    }
    if(h[x]) f[x][0]=0;
    else if(x<=v) f[x][1]=0;
}
void insert1(int x)
{
    if(g[x]==0) Set.erase(x);
    ++g[x];
    for(auto i:a[x])
    {
        if(g[i]==0) Set.erase(i);
        ++g[i];
    }
}
void remove1(int x)
{
    --g[x];
    if(g[x]==0) Set.insert(x);
    for(auto i:a[x])
    {
        --g[i];
        if(g[i]==0) Set.insert(i);
    }
}
void insert2(int x)
{
    if(g[x]==0) Set.erase(x);
    ++g[x];
}
int main()
{
    read(n,k);
    {
        static int z[N];
        for(int i=1;i<=n-1;++i) read(z[i]);
        for(int i=1;i<=n-1;++i)
        {
            int x;
            read(x);
            a[z[i]+1].push_back(x+1);
            a[x+1].push_back(z[i]+1);
        }
    }
    read(m);
    for(int i=1;i<=m;++i)
    {
        read(b[i]);
        ++b[i];
    }
    sort(b+1,b+m+1);
    for(int i=1;i<=m;++i) h[b[i]]=true;
    v=b[m];
    dfs(1,0);
    if(f[1][0]+f[1][1]-1<k)
    {
        k-=(f[1][0]+f[1][1]-1);
        while(m>0)
        {
            h[b[m]]=false;
            v=b[m];
            dfs(1,0);
            if(f[1][0]+f[1][1]-1>=k) break;
            k-=(f[1][0]+f[1][1]-1);
            --m;
        }
        if(m==0) return 0;
        while(true)
        {
            ++b[m];
            h[b[m]]=true;
            v=b[m];
            dfs(1,0);
            if(f[1][0]+f[1][1]>=k) break;
            k-=(f[1][0]+f[1][1]);
            h[b[m]]=false;
        }
    }
    else ++k;
    for(int i=1;i<=n;++i) Set.insert(i);
    for(int i=1;i<=m;++i) insert1(b[i]);
    for(int i=1;i<=b[m];++i) insert2(i);
    while(k>1)
    {
        --k,++m;
        while(true)
        {
            b[m]=*Set.begin();
            h[b[m]]=true;
            insert1(b[m]);
            if(Set.size()>60||(1ll<<(Set.size()/2))>=k) break;
            v=b[m];
            dfs(1,0);
            if(f[1][0]+f[1][1]>=k) break;
            k-=(f[1][0]+f[1][1]);
            h[b[m]]=false;
            remove1(b[m]);
            insert2(b[m]);
        }
    }
    for(int i=1;i<=m;++i)
    {
        print(b[i]-1);
        putchar(' ');
    }
    return 0;
}