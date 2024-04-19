#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000001,M=26;
int n,m,tot=1,b[N][M],d[N],e[N],f[N],g[N],l[N],sa[N],rk[N],he[N];
char *a[N],a0[N];
vector<int> c[N],c2[N];
namespace SA
{
    int h[N],x1[N],x2[N];
    void init(char *a)
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
namespace ST
{
    int b[N][M],lg[N];
    void init()
    {
        for(int i=1;i<=m;++i) b[i][0]=he[i];
        for(int i=1;i<=20;++i)
        {
            for(int j=(1<<i);j<=min((1<<(i+1))-1,m);++j) lg[j]=i;
        }
        for(int i=1;i<=20;++i)
        {
            for(int j=1;j<=m;++j)
            {
                if(j+(1<<i)-1<=m) b[j][i]=min(b[j][i-1],b[j+(1<<(i-1))][i-1]);
            }
        }
    }
    int sum(int x,int y)
    {
        if(x==y) return m+1;
        x=rk[x],y=rk[y];
        if(x>y) swap(x,y);
        ++x;
        return min(b[x][lg[y-x]],b[y-(1<<lg[y-x])+1][lg[y-x]]);
    }
}
namespace sgt
{
    int T[N];
    void add(int x,int k)
    {
        while(x<=n) T[x]+=k,x+=x&-x;
    }
    int sum(int x)
    {
        int s=0;
        while(x>=1) s+=T[x],x-=x&-x;
        return s;
    }
}
void add(char *x,int t)
{
    int q=1;
    for(int i=1;x[i];++i)
    {
        if(b[q][x[i]-'a']==0) b[q][x[i]-'a']=++tot;
        q=b[q][x[i]-'a'];
        c2[q].push_back(t);
    }
    c[q].push_back(t);
}
void dfs(int x,int t)
{
    if(x==0) return;
    for(auto i:c[x]) sgt::add(i,1);
    for(auto i:c2[x])
    {
        e[d[i]+t+1]=sgt::sum(i-1)-(sgt::sum(n)-sgt::sum(i));
    }
    for(auto i:c[x]) sgt::add(i,-1);
    for(int i=0;i<26;++i)
    {
        dfs(b[x][i],t+1);
    }
}
ll lcp(int x,int y)
{
    if(l[x]<l[y]) swap(x,y);
    int p=ST::sum(x,y);
    if(p<l[y]) return p;
    p=ST::sum(x+l[y],x);
    if(p<l[x]-l[y]) return l[y]+p;
    p=ST::sum(y,x+(l[x]-l[y]));
    if(p<l[y]) return l[x]+p;
    return 1e18;
}
bool cmp(int x,int y)
{
    int z=lcp(x,y);
    return a0[x+z%l[x]]<a0[y+z%l[y]];
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        static char z[N];
        scanf("%s",z+1);
        int l=strlen(z+1);
        a[i]=new char[l+10];
        for(int j=1;j<=l+1;++j) a[i][j]=z[j];
        add(a[i],i);
    }
    for(int i=1;i<=n;++i)
    {
        int p=strlen(a[i]+1);
        d[i]=m;
        f[m+1]=i;
        for(int j=1;j<=p;++j)
        {
            a0[++m]=a[i][j];
            l[m]=p-j+1;
        }
        a0[++m]='a'-1;
        l[m]=1;
    }
    a0[++m]='z';
    l[m]=1;
    dfs(1,0);
    SA::init(a0);
    ST::init();
    for(int i=1;i<=m;++i) g[i]=i;
    sort(g+1,g+m+1,cmp);
    ll s=0,w=0;
    for(int i=1;i<=m-1;++i)
    {
        if(a0[g[i]]=='a'-1) continue;
        w+=e[g[i]];
        s=min(s,w+lcp(g[i],g[i+1])+1);
    }
    for(int i=1;i<=n;++i) sgt::T[i]=0;
    for(int i=1;i<=m;++i)
    {
        if(f[sa[i]]==0) continue;
        int j=i;
        while(j+1<=m&&l[sa[i]]==l[sa[j+1]]&&lcp(sa[i],sa[j+1])>=l[sa[i]]) ++j;
        for(int k=i;k<=j;++k)
        {
            if(f[sa[k]]) s+=sgt::sum(n)-sgt::sum(f[sa[k]]);
        }
        for(int k=i;k<=j;++k)
        {
            if(f[sa[k]]) sgt::add(f[sa[k]],1);
        }
        i=j;
    }
    printf("%lld",s);
    return 0;
}