#include<cstdio>
#include<algorithm>
#include<vector>
#include<set>
using namespace std;
const int N=2000001;
int n,a[N],b[N];
struct pr
{
    int l,r;
    pr() {}
    pr(int l,int r):l(l),r(r) {}
    friend bool operator<(const pr &a,const pr &b)
    {
        return a.l<b.l;
    }
};
struct str
{
    set<pr> Set;
    int k;
    void insert(pr x)
    {
        x.l+=k,x.r-=k;
        auto p=lower_bound(Set.begin(),Set.end(),x);
        if(p!=Set.end()&&p->l==x.l)
        {
            x.r=max(x.r,p->r);
            Set.erase(p);
            p=lower_bound(Set.begin(),Set.end(),x);
        }
        if(p!=Set.begin()&&prev(p)->r>=x.r) return;
        while(p!=Set.end()&&p->r<=x.r)
        {
            ++p;
            Set.erase(prev(p));
        }
        Set.insert(x);
    }
    void add(int x)
    {
        k+=x;
    }
    void clear()
    {
        Set.clear();
        k=0;
    }
    bool empty()
    {
        return Set.empty();
    }
    int dis(const pr &p,int x)
    {
        int l=p.l-k,r=p.r+k;
        if(l>=x) return l;
        else if(r<=x) return r;
        else return x;
    }
    int pre(const pr &p,int x)
    {
        int l=p.l-k,r=p.r+k;
        if(l<=x) return min(r,x);
        else return -1e9;
    }
    int suf(const pr &p,int x)
    {
        int l=p.l-k,r=p.r+k;
        if(r>=x) return max(l,x);
        else return 1e9;
    }
    int dis(int x)
    {
        auto p=lower_bound(Set.begin(),Set.end(),pr(x,0));
        int s=1e9;
        if(p!=Set.begin()) s=min(s,abs(x-dis(*prev(p),x)));
        if(p!=Set.end()) s=min(s,abs(x-dis(*p,x)));
        return s;
    }
    int pre(int x)
    {
        auto p=lower_bound(Set.begin(),Set.end(),pr(x,0));
        int s=-1e9;
        if(p!=Set.begin()) s=max(s,pre(*prev(p),x));
        if(p!=Set.end()) s=max(s,pre(*p,x));
        return s;
    }
    int suf(int x)
    {
        auto p=lower_bound(Set.begin(),Set.end(),pr(x,0));
        int s=1e9;
        if(p!=Set.begin()) s=min(s,suf(*prev(p),x));
        if(p!=Set.end()) s=min(s,suf(*p,x));
        return s;
    }
}S,T;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d",&a[i],&b[i]);
    }
    S.insert(pr(0,0));
    T.insert(pr(0,0));
    for(int i=1;i<=n;++i)
    {
        int t=a[i]-a[i-1],x=b[i-1],y=b[i];
        vector<pr> p1,p2;
        if(S.dis(y)==0) p2.push_back(pr(x-t,x+t));
        int d=T.dis(y);
        if(d<=t) p1.push_back(pr(x,x));
        if(!S.empty()) d=min(d,abs(x-y));
        if(d<=t) p2.push_back(pr(y-(t-d),y+(t-d)));
        int d1=T.suf(y-t),d2=T.pre(y+t);
        if(!S.empty()&&abs(x-y)<=t) d1=min(d1,x),d2=max(d2,x);
        if(abs(d1-y)<=t&&abs(d2-y)<=t)
        {
            p1.push_back(pr(min(d1,y)-(t-abs(d1-y))/2,max(d2,y)+(t-abs(d2-y))/2));
        }
        if(abs(x-y)<=t);
        else S.clear();
        if(x==y) T.add(t);
        else T.clear();
        for(auto i:p1) S.insert(i);
        for(auto i:p2) T.insert(i);
    }
    if(S.empty()&&T.empty()) printf("NO");
    else printf("YES");
}