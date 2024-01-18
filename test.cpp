#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
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
const int N=8001;
int n,q,fa[N];
vector<pair<int,int>> a[N];
struct str
{
    int x,y;
    ll w;
    str() {}
    str(int x,int y,ll w):x(x),y(y),w(w) {}
}b[N*N/2];
int find(int x)
{
    if(fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}
void dfs(int x,int fa,int rt,ll w)
{
    if(rt<x) b[++q]=str(rt,x,abs(w));
    for(auto i:a[x])
    {
        if(i.first==fa) continue;
        dfs(i.first,x,rt,w+i.second);
    }
}
int main()
{
    read(n);
    for(int i=1;i<=n-1;++i)
    {
        int x,y,w;
        read(x,y,w);
        a[x].push_back(make_pair(y,w));
        a[y].push_back(make_pair(x,w));
    }
    for(int i=1;i<=n;++i) dfs(i,0,i,0);
    sort(b+1,b+q+1,[](const str &a,const str &b)
    {
        return a.w<b.w;
    });
    for(int i=1;i<=n;++i) fa[i]=i;
    int p=0;
    ll s=0;
    for(int i=1;i<=q;++i)
    {
        int x=find(b[i].x),y=find(b[i].y);
        if(x!=y)
        {
            fa[x]=y;
            s+=b[i].w;
            ++p;
            printf("%d %d %d\n",b[i].x,b[i].y,b[i].w);
            if(p==n-1) break;
        }
    }
    printf("%lld",s);
    return 0;
}