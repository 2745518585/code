#include<bits/stdc++.h>
using namespace std;
namespace IO {
#define iL (1 << 20)
char ibuf[iL], *iS = ibuf + iL, *iT = ibuf + iL;
#define gc() ((iS == iT) ? (iT = (iS = ibuf) + fread(ibuf, 1, iL, stdin), iS == iT ? EOF : *iS ++) : *iS ++)
template<class T> inline void read(T &x) {
  x = 0;int f = 0;char ch = gc();
  for (; !isdigit(ch); f |= ch == '-', ch = gc());
  for (; isdigit(ch); x = (x << 1) + (x << 3) + (ch ^ 48), ch = gc());
  x = (f == 1 ? ~ x + 1 : x);
}
template<class T, class... Args> inline void read(T &x, Args&... args) { read(x), read(args...); }
template<class T> inline void readch(T &x) { char ch = gc(); for (; !isalpha(ch); ch = gc()); x = ch; }
char Out[iL], *iter = Out;
#define flush() fwrite(Out, 1, iter - Out, stdout), iter = Out
template<class T> inline void write(T x, char ch = '\n') {
  T l, c[35];
  if (x < 0) *iter ++ = '-', x = ~ x + 1;
  for (l = 0; !l || x; c[l] = x % 10, l++, x /= 10);
  for (; l; -- l, *iter ++ = c[l] + '0');*iter ++ = ch;
  flush();
}
template<class T, class... Args> inline void write(T x, Args... args) { write(x, ' '), write(args...); }
} // IO
using namespace IO;
typedef long long ll;
const int N=1000001,M=1001;
const ll inf=1000000000000000000;
int n,h[N];
ll b[N],c[N],d[N],e[M][M],f[N],g[N];
vector<int> a[N];
ll gcd(ll a,ll b)
{
    if(b==0) return a;
    return gcd(b,a%b);
}
void dfs0(int x,int fa)
{
    f[x]=b[x];
    for(auto i:a[x])
    {
        if(i==fa) continue;
        dfs0(i,x);
        f[x]=gcd(f[x],f[i]);
    }
}
pair<ll,int> dfs(int x,int fa,ll w)
{
    // printf(" %d %lld %lld\n",x,f[x],w);
    pair<ll,int> s=make_pair(0,0);
    int z=0;
    for(int i=a[x].size()-1;i>=0;--i)
    {
        if(a[x][i]==fa) continue;
        g[a[x][i]]=gcd(f[z],g[z]);
        z=a[x][i];
    }
    ll p=w;
    for(auto i:a[x])
    {
        if(i==fa) continue;
        s=max(s,dfs(i,x,gcd(gcd(p,g[i]),abs(b[x]-b[i]))));
        p=gcd(p,f[i]);
    }
    if(gcd(w,p)==0) s=max(s,make_pair(b[x]+inf,x));
    else s=max(s,make_pair(gcd(w,p),x));
    return s;
}
pair<ll,pair<int,int>> solve(int x)
{
    // printf("%d %d\n",x,b[x]);
    pair<ll,pair<int,int>> s=make_pair(0,make_pair(0,0));
    int q=0;
    dfs0(x,0);
    for(auto i:a[x])
    {
        auto z=dfs(i,x,abs(b[x]-b[i]));
        c[++q]=z.first;
        h[q]=z.second;
        // printf("%d %lld\n",i,c[q]);
        d[q]=f[i];
    }
    for(int i=1;i<=q;++i)
    {
        e[i][i]=d[i];
        for(int j=i+1;j<=q;++j)
        {
            e[i][j]=gcd(e[i][j-1],d[j]);
        }
    }
    for(int i=1;i<=q;++i)
    {
        ll z=gcd(c[i],gcd(e[1][i-1],e[i+1][q]));
        if(z==0) z=b[x]+inf;
        s=max(s,make_pair(z,make_pair(x,h[i])));
        for(int j=i+1;j<=q;++j)
        {
            ll z=gcd(gcd(c[i],c[j]),gcd(e[1][i-1],gcd(e[i+1][j-1],e[j+1][q])));
            if(z==0) z=b[x]+inf;
            s=max(s,make_pair(z,make_pair(h[i],h[j])));
        }
    }
    return s;
}
pair<ll,pair<int,int>> check(ll x)
{
    for(int i=1;i<=n;++i)
    {
        if(b[i]%x!=0) return solve(i);
    }
    return make_pair(0,make_pair(0,0));
}
int main()
{
    freopen("data.in","r",stdin);
    int id;
    read(n,id);
    for(int i=1;i<=n;++i) read(b[i]);
    for(int i=1;i<=n-1;++i)
    {
        int x,y;
        read(x,y);
        a[x].push_back(y);
        a[y].push_back(x);
    }
    int p=0;
    for(int i=1;i<=n;++i)
    {
        if(b[i]!=0)
        {
            p=i;
            break;
        }
    }
    if(p==0)
    {
        write(inf);
        write(1,1,inf);
        return 0;
    }
    pair<ll,pair<int,int>> s=solve(p);
    ll z=b[p];
    for(ll i=2;i*i<=b[p];++i)
    {
        if(z%i==0)
        {
            ll t=1;
            while(z%i==0) z/=i,t*=i;
            s=max(s,check(t));
        }
    }
    if(z>0) s=max(s,check(z));
    write(s.first);
    write(s.second.first,s.second.second,(s.first-b[s.second.first]%s.first)%s.first);
    return 0;
}