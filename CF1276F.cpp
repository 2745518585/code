#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
#include<set>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,las=1,tot=1,sa[N],rk[N],he[N];
char b[N];
ll f[N],f2[N];
vector<int> c[N];
set<int> g[N];
struct tree
{
    int s[26],l,f;
}a[N<<1];
void add(int c)
{
    int x=las,nx=las=++tot;
    a[nx].l=a[x].l+1;
    while(x!=0&&a[x].s[c]==0)
    {
        a[x].s[c]=nx;
        x=a[x].f;
    }
    if(x==0) a[nx].f=1;
    else
    {
        int y=a[x].s[c];
        if(a[x].l+1==a[y].l) a[nx].f=y;
        else
        {
            int ny=++tot;
            a[ny]=a[y];
            a[ny].l=a[x].l+1;
            a[y].f=a[nx].f=ny;
            while(x!=0&&a[x].s[c]==y)
            {
                a[x].s[c]=ny;
                x=a[x].f;
            }
        }
    }
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
namespace ST
{
    int b[N][30],lg[N];
    void init()
    {
        for(int i=1;i<=n;++i) b[i][0]=he[i];
        for(int i=1;i<=20;++i)
        {
            for(int j=(1<<i);j<=min((1<<(i+1))-1,n);++j) lg[j]=i;
        }
        for(int i=1;i<=20;++i)
        {
            for(int j=1;j<=n;++j)
            {
                if(j+(1<<i)-1<=n) b[j][i]=min(b[j][i-1],b[j+(1<<(i-1))][i-1]);
            }
        }
    }
    int sum(int x,int y)
    {
        if(x>y) swap(x,y);
        ++x;
        return min(b[x][lg[y-x]],b[y-(1<<lg[y-x])+1][lg[y-x]]);
    }
}
void dfs(int x)
{
    for(auto i:c[x])
    {
        dfs(i);
        if(g[i].size()>g[x].size()) swap(g[x],g[i]),swap(f[x],f[i]);
        for(auto j:g[i])
        {
            if(g[x].count(j)) continue;
            g[x].insert(j);
            f[x]+=n-sa[j]+1;
            // printf("%d %d %d\n",j,sa[j],f[x]);
            auto p=g[x].find(j);
            if(p!=g[x].begin()) f[x]-=ST::sum(*prev(p),j);
            if(next(p)!=g[x].end()) f[x]-=ST::sum(*next(p),j);
            if(p!=g[x].begin()&&next(p)!=g[x].end()) f[x]+=ST::sum(*prev(p),*next(p));
        }
    }
    // printf("%d %d\n",x,f[x]);
    f2[x]=f[x];
}
int main()
{
    scanf("%s",b+1);
    n=strlen(b+1);
    for(int i=1;i<=n;++i) add(b[i]-'a');
    SA::init(b);
    ST::init();
    for(int i=1;i<=tot;++i) c[a[i].f].push_back(i);
    int x=1;
    f[1]=n-1;
    g[1].insert(rk[2]);
    for(int i=1;i<=n-2;++i)
    {
        x=a[x].s[b[i]-'a'];
        f[x]=n-i-1;
        g[x].insert(rk[i+2]);
        // printf("%d %d %d\n",i,i+2,rk[i+2]);
    }
    dfs(1);
    ll s=0;
    for(int i=1;i<=tot;++i)
    {
        s+=f2[i]*(a[i].l-a[a[i].f].l);
    }
    // printf("%lld\n",s);
    // return 0;
    for(int i=1;i<=tot;++i)
    {
        s+=a[i].l-a[a[i].f].l;
    }
    for(int i=1;i<=tot;++i)
    {
        if(a[i].l!=n) s+=a[i].l-a[a[i].f].l;
    }
    s+=f2[1];
    // printf("%lld\n",f2[1]);
    s+=2;
    printf("%lld",s);
    return 0;
}