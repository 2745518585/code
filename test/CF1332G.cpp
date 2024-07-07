#include<cstdio>
#include<algorithm>
#include<vector>
#include<set>
using namespace std;
const int N=1000001;
int n,m,q,a[N],b[N],h[N],S1[N],T1,S2[N],T2;
set<int> Set;
struct str
{
    int l,r=1e9,x1,x2;
    str() {}
    str(int l,int r,int x1,int x2=0):l(l),r(r),x1(x1),x2(x2) {}
    friend bool operator<(const str &a,const str &b)
    {
        return a.r<b.r;
    }
}e[N];
vector<str> d[N];
vector<pair<pair<int,int>,int>> c[N];
namespace sgt
{
    struct tree
    {
        int l,r;
        str s;
    }T[N<<2];
    void pushup(int x)
    {
        T[x].s=min(T[x<<1].s,T[x<<1|1].s);
    }
    void build(int x,int l,int r)
    {
        T[x].l=l,T[x].r=r;
        T[x].s=str();
        if(l==r) return;
        int z=l+r>>1;
        build(x<<1,l,z);
        build(x<<1|1,z+1,r);
        pushup(x);
    }
    void add(int x,int q,str k)
    {
        if(T[x].l==T[x].r)
        {
            T[x].s=min(T[x].s,k);
            return;
        }
        int z=T[x].l+T[x].r>>1;
        if(q<=z) add(x<<1,q,k);
        else add(x<<1|1,q,k);
        pushup(x);
    }
    str sum(int x,int l,int r)
    {
        if(T[x].l>=l&&T[x].r<=r) return T[x].s;
        int z=T[x].l+T[x].r>>1;
        str s;
        if(l<=z) s=min(s,sum(x<<1,l,r));
        if(r>z) s=min(s,sum(x<<1|1,l,r));
        return s;
    }
};
int find1(int *S,int T,int x)
{
    int l=0,r=T;
    while(l<r)
    {
        int z=l+r+1>>1;
        if(a[S[z]]!=x) l=z;
        else r=z-1;
    }
    return S[l];
}
int find2(int *S,int T,int x)
{
    int l=0,r=T;
    while(l<r)
    {
        int z=l+r>>1;
        if(S[z]<x) r=z;
        else l=z+1;
    }
    return S[l];
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        b[++q]=a[i];
    }
    sort(b+1,b+q+1);
    q=unique(b+1,b+q+1)-b-1;
    for(int i=1;i<=n;++i)
    {
        a[i]=lower_bound(b+1,b+q+1,a[i])-b;
    }
    for(int i=1;i<=m;++i)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        c[r].push_back(make_pair(make_pair(l,r),i));
    }
    {
        S1[T1=0]=n+1,Set.clear();
        Set.insert(n+2);
        for(int i=n;i>=1;--i)
        {
            while(T1>0&&a[S1[T1]]<a[i]) Set.insert(S1[T1--]);
            S1[++T1]=i;
            int x=*Set.upper_bound(find1(S1,T1,a[i]));
            d[x].push_back(str(i,x,find2(S1,T1,x)));
        }
    }
    {
        S1[T1=0]=n+1,Set.clear();
        Set.insert(n+2);
        for(int i=n;i>=1;--i)
        {
            while(T1>0&&a[S1[T1]]>a[i]) Set.insert(S1[T1--]);
            S1[++T1]=i;
            int x=*Set.upper_bound(find1(S1,T1,a[i]));
            d[x].push_back(str(i,x,find2(S1,T1,x)));
        }
    }
    sgt::build(1,1,n);
    for(int i=1;i<=n;++i)
    {
        for(auto j:d[i]) sgt::add(1,j.l,j);
        for(auto j:c[i]) e[j.second]=min(e[j.second],sgt::sum(1,j.first.first,j.first.second));
    }
    for(int i=1;i<=n;++i) d[i].clear();
    {
        S1[T1=0]=n+1,S2[T2=0]=n+1,Set.clear();
        Set.insert(n+2);
        auto add=[&](int x)
        {
            ++h[x];
            if(h[x]==2) Set.insert(x);
        };
        for(int i=n;i>=1;--i)
        {
            while(T1>0&&a[S1[T1]]<a[i]) add(S1[T1--]);
            while(T2>0&&a[S2[T2]]>a[i]) add(S2[T2--]);
            S1[++T1]=i;
            S2[++T2]=i;
            int x=*Set.upper_bound(max(find1(S1,T1,a[i]),find1(S2,T2,a[i])));
            d[x].push_back(str(i,x,find2(S1,T1,x),find2(S2,T2,x)));
        }
    }
    sgt::build(1,1,n);
    for(int i=1;i<=n;++i)
    {
        for(auto j:d[i]) sgt::add(1,j.l,j);
        for(auto j:c[i])
        {
            auto z=sgt::sum(1,j.first.first,j.first.second);
            if(z.r<=n) e[j.second]=z;
        }
    }
    for(int i=1;i<=m;++i)
    {
        if(e[i].r>n) printf("0\n");
        else if(e[i].x2!=0) printf("4\n%d %d %d %d\n",e[i].l,min(e[i].x1,e[i].x2),max(e[i].x1,e[i].x2),e[i].r);
        else printf("3\n%d %d %d\n",e[i].l,e[i].x1,e[i].r);
    }
    return 0;
}