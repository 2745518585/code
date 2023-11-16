#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
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
const int N=2000001;
int n,m,q,a[N],b[N],c[N],d2[N];
vector<int> d1[N];
struct tree
{
    int l,r,k,s;
}T[N<<2];
void pushup(int x)
{
    T[x].s=min(T[x<<1].s,T[x<<1|1].s);
}
void pushdown(int x)
{
    if(T[x].k==0) return;
    T[x<<1].s+=T[x].k;
    T[x<<1].k+=T[x].k;
    T[x<<1|1].s+=T[x].k;
    T[x<<1|1].k+=T[x].k;
    T[x].k=0;
}
void build(int x,int l,int r)
{
    T[x].l=l;
    T[x].r=r;
    T[x].s=T[x].k=0;
    if(l==r) return;
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    pushup(x);
}
void add(int x,int l,int r,int k)
{
    if(l>r) return;
    if(T[x].l>=l&&T[x].r<=r)
    {
        T[x].s+=k;
        T[x].k+=k;
        return;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    if(l<=z) add(x<<1,l,r,k);
    if(r>z) add(x<<1|1,l,r,k);
    pushup(x);
}
int sum(int x,int l,int r)
{
    if(T[x].l>=l&&T[x].r<=r)
    {
        return T[x].s;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1,s=1e9;
    if(l<=z) s=min(s,sum(x<<1,l,r));
    if(r>z) s=min(s,sum(x<<1|1,l,r));
    return s;
}
int main()
{
    int TOT;
    read(TOT);
    while(TOT--)
    {
        read(n),read(m);
        q=0;
        for(int i=1;i<=n;++i)
        {
            read(a[i]);
            c[++q]=a[i];
        }
        for(int i=1;i<=m;++i)
        {
            read(b[i]);
            c[++q]=b[i];
        }
        sort(c+1,c+q+1);
        q=unique(c+1,c+q+1)-c-1;
        for(int i=0;i<=q+1;++i) d1[i].clear(),d2[i]=0;
        for(int i=1;i<=n;++i)
        {
            a[i]=lower_bound(c+1,c+q+1,a[i])-c;
            d1[a[i]].push_back(i);
        }
        for(int i=1;i<=m;++i)
        {
            b[i]=lower_bound(c+1,c+q+1,b[i])-c;
            ++d2[b[i]];
        }
        build(1,1,n+1);
        for(int i=1;i<=n;++i) add(1,i+1,n+1,1);
        ll s=0;
        for(int i=1;i<=q;++i)
        {
            for(auto j:d1[i-1]) add(1,1,j,1);
            for(auto j:d1[i]) add(1,j+1,n+1,-1);
            s+=(ll)d2[i]*T[1].s*2;
            for(auto j:d1[i]) s+=sum(1,j,j);
        }
        printf("%lld\n",s/2);
    }
    return 0;
}