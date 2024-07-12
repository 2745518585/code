#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,las=1,tot=1,c[N],f[N],g[N],rt[N];
char b[N];
vector<int> d[N];
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
namespace sgt
{
    int tot;
    struct tree
    {
        int l,r,s;
    }T[N<<4];
    void pushup(int x)
    {
        T[x].s=T[T[x].l].s+T[T[x].r].s;
    }
    void add(int &x,int ls,int rs,int q,int k)
    {
        T[++tot]=T[x],x=tot;
        if(ls==rs)
        {
            T[x].s+=k;
            return;
        }
        int z=ls+rs>>1;
        if(q<=z) add(T[x].l,ls,z,q,k);
        else add(T[x].r,z+1,rs,q,k);
        pushup(x);
    }
    int sum(int x,int ls,int rs,int l,int r)
    {
        if(x==0) return 0;
        if(ls>=l&&rs<=r) return T[x].s;
        int z=ls+rs>>1,s=0;
        if(l<=z) s+=sum(T[x].l,ls,z,l,r);
        if(r>z) s+=sum(T[x].r,z+1,rs,l,r);
        return s;
    }
    int merge(int x1,int x2,int ls,int rs)
    {
        if(x1==0||x2==0) return x1|x2;
        if(ls==rs)
        {
            ++tot;
            T[tot].s=T[x1].s+T[x2].s;
            return tot;
        }
        int z=ls+rs>>1;
        int p=++tot;
        T[p].l=merge(T[x1].l,T[x2].l,ls,z);
        T[p].r=merge(T[x1].r,T[x2].r,z+1,rs);
        pushup(p);
        return p;
    }
}
void dfs0(int x)
{
    for(auto i:d[x])
    {
        dfs0(i);
        c[x]=max(c[x],c[i]);
        rt[x]=sgt::merge(rt[x],rt[i],1,n);
    }
}
void dfs(int x)
{
    for(auto i:d[x])
    {
        if(sgt::sum(rt[g[x]],1,n,c[i]-a[i].l+a[g[x]].l,c[i]-1))
        {
            f[i]=f[x]+1;
            g[i]=i;
        }
        else
        {
            if(f[x]>=f[i]) f[i]=f[x],g[i]=g[x];
        }
        dfs(i);
    }
}
int main()
{
    scanf("%d%s",&n,b+1);
    for(int i=1;i<=n;++i)
    {
        int x=add(b[i]-'a');
        c[x]=i;
        sgt::add(rt[x],1,n,i,1);
    }
    for(int i=2;i<=tot;++i) d[a[i].f].push_back(i);
    dfs0(1);
    f[1]=0,g[1]=1;
    for(int i=2;i<=tot;++i) f[i]=1,g[i]=i;
    dfs(1);
    int s=0;
    for(int i=1;i<=tot;++i) s=max(s,f[i]);
    printf("%d",s);
    return 0;
}