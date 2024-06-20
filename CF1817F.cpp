#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll B=147258369,P=1e9+7;
int n,q,sa[N],rk[N],he[N],fa[N],g[N],h[N];
char a[N];
ll s,pw[N],ivpw[N],f[N],d1[N],d2[N];
vector<int> b[N];
struct str
{
    int x,l,r;
    str() {}
    str(int x,int l,int r):x(x),l(l),r(r) {}
    friend bool operator<(const str &a,const str &b)
    {
        return a.x<b.x;
    }
}d[N];
map<ll,vector<str>> Map;
void exgcd(ll a,ll b,ll &x,ll &y)
{
    if(b==0) x=1,y=0;
    else exgcd(b,a%b,y,x),y-=a/b*x;
}
ll inv(ll a)
{
    a=(a%P+P)%P;
    ll x,y;
    exgcd(a,P,x,y);
    x=(x%P+P)%P;
    return x;
}
int find(int x)
{
    if(fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}
namespace SA
{
    int h[N],x1[N],x2[N];
    void init(char a[])
    {
        int n=strlen(a+1),m=128;
        for(int i=1;i<=n;++i)
        {
            ++h[a[i]];
            x1[i]=a[i];
        }
        for(int i=1;i<=m;++i) h[i]+=h[i-1];
        for(int i=n;i>=1;--i) sa[h[x1[i]]--]=i;
        for(int r=1;r<=n;r<<=1)
        {
            int p=0;
            for(int i=n-r+1;i<=n;++i) x2[++p]=i;
            for(int i=1;i<=n;++i) if(sa[i]>r) x2[++p]=sa[i]-r;
            for(int i=1;i<=m;++i) h[i]=0;
            for(int i=1;i<=n;++i) ++h[x1[i]];
            for(int i=1;i<=m;++i) h[i]+=h[i-1];
            for(int i=n;i>=1;--i) sa[h[x1[x2[i]]]--]=x2[i],x2[i]=0;
            swap(x1,x2);
            p=0;
            x1[sa[1]]=++p;
            for(int i=2;i<=n;++i)
            {
                if(x2[sa[i]]==x2[sa[i-1]]&&x2[sa[i]+r]==x2[sa[i-1]+r]) x1[sa[i]]=p;
                else x1[sa[i]]=++p;
            }
            if(p==n) break;
            m=p;
        }
        for(int i=1;i<=n;++i) rk[sa[i]]=i;
        int p=0;
        for(int i=1;i<=n;++i)
        {
            if(rk[i]==1) continue;
            if(p>=1) --p;
            int j=sa[rk[i]-1];
            while(i+p<=n&&j+p<=n&&a[i+p]==a[j+p]) ++p;
            he[rk[i]]=p;
        }
    }
}
void merge(int x,int y,int t)
{
    x=find(x),y=find(y);
    f[x]=(f[x]+f[y])%P;
    g[x]=min(g[x],g[y]);
    h[x]=t;
    fa[y]=x;
}
void add(int x,int t)
{
    x=find(x);
    if(t+1<=h[x]) Map[f[x]*ivpw[g[x]]%P].push_back(str(g[x],t+1,h[x]));
}
int main()
{
    scanf("%s",a+1);
    SA::init(a);
    n=strlen(a+1);
    pw[0]=1;
    for(int i=1;i<=n;++i) pw[i]=pw[i-1]*B%P;
    ivpw[n]=inv(pw[n]);
    for(int i=n;i>=1;--i) ivpw[i-1]=ivpw[i]*B%P;
    for(int i=2;i<=n;++i) b[he[i]].push_back(i);
    for(int i=1;i<=n;++i)
    {
        fa[i]=i;
        f[i]=pw[sa[i]];
        g[i]=sa[i];
        h[i]=n-sa[i]+1;
    }
    ll s=0;
    for(int i=n;i>=0;--i)
    {
        for(auto j:b[i])
        {
            add(j-1,i);
            add(j,i);
            merge(j-1,j,i);
        }
    }
    for(auto p:Map)
    {
        q=0;
        for(auto j:p.second) d[++q]=j;
        sort(d+1,d+q+1);
        // for(int i=1;i<=q;++i) printf("(%d,%d,%d) ",d[i].x,d[i].l,d[i].r);printf("\n");
        d1[q+1]=d2[q+1]=0;
        for(int i=q;i>=1;--i)
        {
            auto sum=[&](int x)
            {
                return d1[x]-d2[x]*(d[i].x+d[i].l-1);
            };
            int p1=lower_bound(d+1,d+q+1,str(d[i].x+d[i].l,0,0))-d,p2=upper_bound(d+1,d+q+1,str(d[i].x+d[i].r,0,0))-d;
            s+=sum(p1)-sum(p2);
            d1[i]=d1[i+1]+(ll)d[i].x*(d[i].r-d[i].l+1);
            d2[i]=d2[i+1]+(d[i].r-d[i].l+1);
        }
    }
    printf("%lld",s);
    return 0;
}