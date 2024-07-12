#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
#include<set>
using namespace std;
typedef long long ll;
const int N=2000001;
int n,m,las=1,tot=1,l[N],e[N];
char b[N];
set<int> f[N];
vector<pair<int,int>> c1[N],c2[N],d[N];
struct tree
{
    int s[26],l,f;
}a[N];
int add(int c)
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
    return nx;
}
namespace sgt1
{
    int T[N];
    void add(int x,int k)
    {
        while(x>=1) T[x]=max(T[x],k),x-=x&-x;
    }
    int sum(int x)
    {
        int s=0;
        while(x<=n) s=max(s,T[x]),x+=x&-x;
        return s;
    }
}
namespace sgt2
{
    int T[N];
    void add(int x,int k)
    {
        while(x<=n) T[x]=max(T[x],k),x+=x&-x;
    }
    int sum(int x)
    {
        int s=0;
        while(x>=1) s=max(s,T[x]),x-=x&-x;
        return s;
    }
}
void merge(int x,int y)
{
    if(f[x].size()<f[y].size()) swap(f[x],f[y]);
    auto add=[&](int x,int y,int k)
    {
        if(x>y) swap(x,y);
        c1[y].push_back(make_pair(x-k+1,k));
        c2[y].push_back(make_pair(x-k+2,x));
    };
    for(auto i:f[y])
    {
        f[x].insert(i);
        auto p=f[x].find(i);
        if(p!=f[x].begin()) add(*prev(p),*p,a[x].l);
        if(next(p)!=f[x].end()) add(*p,*next(p),a[x].l);
    }
}
int main()
{
    scanf("%d%d%s",&n,&m,b+1);
    for(int i=1;i<=n;++i)
    {
        f[add(b[i]-'a')].insert(i);
    }
    for(int i=2;i<=tot;++i) ++l[a[i].f];
    queue<int> Q;
    for(int i=1;i<=tot;++i)
    {
        if(l[i]==0) Q.push(i);
    }
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        merge(a[k].f,k);
        --l[a[k].f];
        if(l[a[k].f]==0) Q.push(a[k].f);
    }
    for(int i=1;i<=m;++i)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        d[r].push_back(make_pair(l,i));
    }
    for(int i=1;i<=n;++i)
    {
        for(auto j:c1[i])
        {
            sgt1::add(j.first,j.second);
        }
        for(auto j:c2[i])
        {
            sgt2::add(j.first,j.second);
        }
        for(auto j:d[i])
        {
            e[j.second]=(i-j.first+1)-max(sgt1::sum(j.first),sgt2::sum(j.first)-j.first+1);
        }
    }
    for(int i=1;i<=m;++i)
    {
        printf("%d\n",e[i]);
    }
    return 0;
}