#include<cstdio>
#include<algorithm>
#include<vector>
#include<set>
using namespace std;
typedef long long ll;
const int N=2000001;
int n,m,b[N],f[16],p[16],g[8];
bool h[N];
ll s;
struct str
{
    int a,b,t;
    friend bool operator<(str a,str b)
    {
        if(a.b!=b.b) return a.b<b.b;
        return a.t<b.t;
    }
}a[N];
set<str> Set[8][2];
void add(int x)
{
    if(h[x])
    {
        for(auto j=1;j<=15;++j) if(j&g[a[x].a]) --f[j];
        s-=a[x].b;
    }
    h[x]^=1;
    if(h[x])
    {
        for(auto j=1;j<=15;++j) if(j&g[a[x].a]) ++f[j];
        s+=a[x].b;
    }
}
int sum()
{
    int s=1e9;
    for(int i=1;i<=15;++i)
    {
        s=min(s,f[i]/p[i]);
    }
    return s;
}
bool cmp(int x,int y)
{
    return a[x].b>a[y].b;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        static char z[5];
        z[0]=z[1]=z[2]=0;
        scanf("%s%d",z,&a[i].b);
        if(z[0]=='D'||z[1]=='D'||z[2]=='D') a[i].a|=1;
        if(z[0]=='S'||z[1]=='S'||z[2]=='S') a[i].a|=2;
        if(z[0]=='B'||z[1]=='B'||z[2]=='B') a[i].a|=4;
        a[i].t=i;
    }
    for(int i=1;i<=n;++i) b[i]=i;
    sort(b+1,b+n+1,cmp);
    for(int i=1;i<=7;++i)
    {
        if(i&1) g[i]|=1;
        if(i&2) g[i]|=2;
        if(i&3) g[i]|=4;
        if(i&4) g[i]|=8;
    }
    for(int i=1;i<=15;++i) p[i]=p[i^(i&-i)]+1;
    for(int i=1;i<=n;++i) add(i);
    int q=sum();
    for(int i=1;i<=n;++i)
    {
        add(b[i]);
        if(sum()<q) add(b[i]);
    }
    // printf("%d %lld\n",q,s);
    for(int i=1;i<=n;++i)
    {
        Set[a[i].a][h[i]].insert(a[i]);
    }
    scanf("%d",&m);
    for(int i=1;i<=m;++i)
    {
        int x,k;
        scanf("%d%d",&x,&k);
        Set[a[x].a][h[x]].erase(a[x]);
        if(h[x]) s-=a[x].b;
        a[x].b=k;
        Set[a[x].a][h[x]].insert(a[x]);
        if(h[x]) s+=a[x].b;
        int u=0;
        ll v=s;
        for(int i=1;i<=7;++i)
        {
            int t=0;
            if(h[x])
            {
                if(!Set[i][0].empty()) t=Set[i][0].begin()->t;
            }
            else
            {
                if(!Set[i][1].empty()) t=prev(Set[i][1].end())->t;
            }
            if(t!=0)
            {
                add(x),add(t);
                if(sum()==q&&s<v) v=s,u=t;
                add(x),add(t);
            }
        }
        if(u!=0)
        {
            Set[a[x].a][h[x]].erase(a[x]);
            Set[a[u].a][h[u]].erase(a[u]);
            add(x),add(u);
            Set[a[x].a][h[x]].insert(a[x]);
            Set[a[u].a][h[u]].insert(a[u]);
        }
        printf("%lld\n",s);
    }
    return 0;
}